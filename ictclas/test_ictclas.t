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
    $segmenter->SetSource("长长的RAMBLA大街???????????????");
    $segmenter->Run();

    #$segmenter->OpenFile('test/test.txt');
    print $segmenter->GetResult(), "\n";
}

