#!/bin/perl
$count=0; $passed=0;
open(MULTI,">multi.run.log");
$executable_name = $ARGV[0];
while(<STDIN>){
	$test_case = $_; chomp($test_case);
	$cmd_str = "./$executable_name $test_case";
	print "$cmd_str\n";
	$execute = `$cmd_str`;
	print "$cmd_str\n";
	print MULTI "====\n";
	print MULTI "$cmd_str\n";
	print MULTI "$execute\n";
	print MULTI "====\n";
	if($execute =~ /SUCCESS/){
		print "$test_case :: PASSED\n";
		$passed++;
	}else{
		print "$test_case :: FAILED\n";
	}
		$count++;
}

print "TOTAL: $count\n";
print "PASSED: $passed\n";
