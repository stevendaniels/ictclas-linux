use Benchmark qw(:all);
use ictclas;
use Encode;

my $segmenter = new ictclas::ICTCLAS();
# $t = timeit(1000, ' &main(); ');
# print timestr($t), "\n";

for ($i=0; $i<10; $i++) {
    print "[$i]\n";
    &main();
}
 
$segmenter->DESTROY();

sub main {
    $segmenter->Run("������RAMBLA���???????????????");

    print $segmenter->GetResult(), "\n";
}

