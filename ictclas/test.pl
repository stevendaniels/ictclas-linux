#! /usr/bin/perl
use DBI;
use Encode;
use Benchmark;
use ictclas;

my $dbh = DBI->connect("DBI:mysql:database=bs_index;host=192.168.1.57",
    "root","33770880", { PrintError => 0, RaiseError => 1 });
$dbh->do(qq{set names UTF8});
my $sth = $dbh->prepare( qq{
    SELECT sentence 
    FROM parse_result
    LIMIT ?,?
    });
my $segment = new ictclas::ICTCLAS();
&main();
$segment->DESTROY();

sub main()
{
    my $sth_temp = $dbh->prepare(qq{
        SELECT count(*) 
        FROM parse_result
        });
    $sth_temp->execute();
    # my($total) = $sth_temp->fetchrow_array();
    my $total = 20000;

    print "Total:      $total\n";
    $sth_temp->finish();
    my @parse_sentence;
    for($i = 0; $i < $total; $i += 10000)
    {
        print "Current Step:     $i\n";
        $sth->bind_param(1,$i);
        $sth->bind_param(2,10000);
        $sth->execute();
        while (($sentence) =  $sth->fetchrow_array())
        {
            push @parse_sentence,$sentence;
        }
        $sth->finish();
    }
    print "load ok\n";
    my $t0 = new Benchmark;
    my $count = 0;
    # open UTF8, ">utf8.txt";
    open SEG_RESULT, ">seg_result.txt";
    # open GB2312, ">gb2312.txt";
    foreach(@parse_sentence)
    {
        # print "[$count]\n" unless ($count % 1000);
        print "[$count]\n";
        $count++;
        # print UTF8 "<$count>'$_'\n"; 

        $_ = pre_process($_);
        unless ($_) {
            next;
        }

        eval {
            $segment->Run($_);
        };
        if ($@) {
            print "ERROR: ($@)\n";
            return;
        }
        # print GB2312 "<$count>'$_'\n";
        print SEG_RESULT "<$count>", $segment->GetResult(), "\n";
    }
    my $t1 = new Benchmark;
    my $td = timediff($t1, $t0);
    print "Took: ", timestr($td), "\n";
}

sub check_chinese {
    $_ = shift;
    return 0 unless $_;
    s/^\s*//g;
    s/\s*$//g;
    return 0 unless $_;

    my $chinese= q{
    [\xC2-\xDF][\x80-\xBF]
    | \xE0[\xA0-\xBF][\x80-\xBF]
    | [\xE1-\xEC\xEE\xEF][\x80-\xBF]{2} 
    | \xED[\x80-\x9F][\x80-\xBF] 
    | \xF0[\x90-\xBF][\x80-\xBF]{2} 
    | [\xF1-\xF3][\x80-\xBF]{3} 
    | \xF4[\x80-\x8F][\x80-\xBF]{2}
};
return 0 unless (/^(?:$chinese)*$/xo);
return 1;
}

sub check_chinese_0 {
    $_ = shift;
    return 0 unless $_;
    s/^\s*//g;
    s/\s*$//g;
    return 0 unless $_;

    if (/^[\x{4e00}-\x{9fa5}]*$/ or /^[\x{e7c7}-\x{e7e3}]*$/) {
        return 1;
    }
    return 0;
}

sub pre_process {
    my $origin_str = shift;
    $_ = $origin_str;
    $_ = remove_repeating_chars($_);
    $_ = remove_space($_);
    $_ = remove_special_chars($_);

    Encode::from_to($_,'utf8','gb2312', Encode::FB_DEFAULT); 
    if (/\?/) {
        open INVALID, ">>", "invalid.txt" or die "Cannot open invalid.txt!\n";
        open INVALID_GB, ">>", "invalid_gb.txt" or die "Cannot open invalid_gb.txt!\n";
        print INVALID "<?>'$origin_str'\n";
        print INVALID_GB "<?> '$_'\n";
        return "";
    }

#     unless (&check_chinese($_)) {
#         print INVALID "$origin_str\n";
#         return "";
#     }

    return $_;
}

sub remove_repeating_chars {
    $_ = shift;
    s/\.//g;
    s/-//g;
    s/\*//g;
    s/=//g;
    s/\?//g;
    return $_;
}

sub remove_space {
    $_ = shift;
    s/\xc2\xa0//g;
    s/\xe3\x80\x80//g;
    s/\xee\x97\xa5//g;
    return $_;
}

sub remove_special_chars {
    $_ = shift;
    s/\'//g;
    s/\xe2\x80\x94//g;  # ——
    s/\xe2\x80\xa2//g;  # •
    s/\xc2\xb7//g;      # ·
    s/\xef\xb9\xaa/%/g; # ﹪ to %
    s/\xef\xbf\xbd//g;  # �
    return $_;
}

