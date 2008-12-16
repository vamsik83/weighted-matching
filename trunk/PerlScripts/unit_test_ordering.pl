#!/bin/perl
#
# This compares our implementation of MC64 with MKL implementation
# by running on the nexxim suite of test cases.
# it reads the file with list of test cases
#
# May 30, 2008 
# perl unit_test_ordering.pl <file>
#
$altra_test_root = "/home/kundeti/altra/test/";
$config_file = "/home/kundeti/release/model_libraries/cirsim.cfg";
$test_file_name = $ARGV[0]; 

print "Reading Test File $test_file_name \n";

open(TFILE,$test_file_name) or die("FAILED:$!\n");
while(<TFILE>){
	$test_case = $_; chomp($test_case);
	$spice_file = $altra_test_root.$test_case;
	$cmd_str = "sim -config_file=$config_file $spice_file";
	print "Extracing Matrix:\n $cmd_str\n";
	$execute = `$cmd_str >& /dev/null `;
#extract base_name.
	if($test_case =~ /([^\/\.]+\.sp)/){
		$base_name = $1;
		if(-e $base_name.".rowptr" && -e $base_name.".colind" && -e $base_name.".val"){
			print "Extracted matrix successfully for test: $base_name\n";
			$cmd_str = "cat $base_name.rowptr $base_name.colind $base_name.val > $base_name.test";
			$execute = `$cmd_str`;
			print "Removing the temp files\n";
			$cmd_str = "rm -rf $base_name.rowptr $base_name.colind $base_name.val";
			$execute = `$cmd_str`;
			$cmd_str = "/home/kundeti/work/ReorderMatrix/src/bipartite $base_name.test";
			$execute = `$cmd_str`;
			if($execute =~ /SUCCESS/){
				print "....TEST...PASSED....\n";
			}else{
				print "******FAILED*****\n";
				open(log_file,">$base_name.log");
				print log_file "$execute \n";
				close(log_file);
			}
		}else{
			print ".....Unable to extract matrix from the test: $base_name .. skipping..\n";
		}
	}
}
