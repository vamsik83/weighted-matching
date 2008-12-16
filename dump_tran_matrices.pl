#!/bin/perl
#
# This simple script runs nexxim and dumps tran matrices in .test file
#
# USAGE: find /home/vamsik/altra/test -name "*.sp" -exec dump_tran_matrices.pl
#
$file_name = $ARGV[0];
system("sim -config_file=/home/kundeti/release/model_libraries/cirsim.cfg $file_name");
#extract the base_name
$file_name =~ /\/([^\/]+)$/;
$file_name = $1;
print "$file_name\n";
if(-e $file_name.".tran.val"){
	$out_file = $file_name.".tran.test";
	$rowptr = $file_name.".tran.rowptr";
	$colind = $file_name.".tran.colind";
	$values = $file_name.".tran.val";
	system("cat $rowptr $colind $values > $out_file");
}else{
	print "Unable to dump tran matrix for: $file_name \n";
}



