#!/bin/perl
#
#mm2rc: Converts the matrix market format to 
#row compressed format.
#
#Output File: the first line is the rowstarts, second line is
#the column indices and third line is the non-zero 
#values. Generates a .rcf file (row compressed format file).
#
#Usage: perl mm2rc.pl <matrix market file> 
#
#10/15/2008 vamsik@engr
#
#11/27/2008 vamsik@engr Fixed the path issue with '/'
#
$#ARGV == 0 or die("USAGE: perl mm2rc.pl <matrix market file>\n");
$in_file = $ARGV[0];
if($in_file =~ /(.*)\.tar\.gz/){
	@file_list = split('\n',`tar -xvzf $in_file`);
	$in_file = $file_list[0]; 
}

if(!(-e $in_file)){
	die("ERROR: Input Matrix market file does not exist\n");
}
#
# Extract file prefix
#
$in_file =~ /([^\.]+)\./;
$file_prefix = $1;
$sorted_suffix = $file_prefix.".sorted";
$sorted_suffix =~ tr/\//_/;
$sorted_mm_file_name = "/tmp/".$sorted_suffix;

$cmd_str = "sort -t ' ' -n --key=1 --key=2 ";
$cmd_str = $cmd_str.$in_file." > ".$sorted_mm_file_name;
print "......Sorting the Matrix Market File.....\n";
print "$cmd_str\n";
system($cmd_str);
if(!(-e $sorted_mm_file_name)){
	print "FAILED to sort\n";
}else{
	print ".....Done...\n";
}

open(MMFILE,$sorted_mm_file_name) or die("ERROR: $!");
#
# write simultaneously into three files and merge them. 
#
$row_file = $sorted_mm_file_name.".row";
$col_file = $sorted_mm_file_name.".col";
$val_file = $sorted_mm_file_name.".val";
open(ROWFILE,">$row_file") or die("$!");
open(COLFILE,">$col_file") or die("$!");
open(VALFILE,">$val_file") or die("$!");
$row_start = 0;
$current_row = 0;
while(<MMFILE>){
	$line = $_;
	if($line =~/([\d]+) ([\d]+) ([\d\-\.]+)/){
		$i = $1; $j = $2 ; $v = $3;
		$row_start++;
		if($i != $current_row){
			$current_row = $i;
			print ROWFILE " $row_start";
		}
		print COLFILE " $j";
		print VALFILE " $v";
	}
}
#after sorting the last line is the
#dimension description in the MM format
print ROWFILE " $row_start\n";
print COLFILE "\n";
print VALFILE "\n";
#
# merge all the files into a 
# single file
#

$cmd_str = "cat $row_file $col_file $val_file > $file_prefix.rcf";
print ".....Merging Files....\n";
print "$cmd_str\n";
system($cmd_str);
if(-e $file_prefix.".rcf"){
	print "SUCCESSFUL in generating .rcf file \n";
}else{
	print "FAILED to generate .rcf file\n";
}
print ".....Cleaning Up....\n";
$cmd_str = "rm -rf $row_file $col_file $val_file $sorted_mm_file_name ";
system($cmd_str);
close(ROWFILE);
close(COLFILE);
close(VALFILE);
close(MMFILE);
