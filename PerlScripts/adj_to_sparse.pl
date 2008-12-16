#!/bin/perl
#
# Converts an adjacency matrix to sparse row format
#
$n = <STDIN>;
chomp($n);
@rowptr;
@colind;
@val;
$rowptr[0] = 1;
$rindex = 1;
$cindex = 0;
$vindex = 0;
while(<STDIN>){
	$line = $_;
	chomp($line);
	$col_count=0;
	while($line =~ /([\d\.]+)/g){
		$val = $1;
		$col_count++;
		if($val != 0){
			$colind[$cindex] = $col_count;
			$cindex++;
			$val[$vindex] = $val;
			$vindex++;
		}
	}
	$rowptr[$rindex]=$cindex+1;
	$rindex++;
}

#print the rowptr 
foreach $i (@rowptr){
	print "$i ";
}
print "\n";
#print the colind
foreach $j (@colind){
	print "$j ";
}
print "\n";
#print the nnz
foreach $k (@val){
	print "$k ";
}
print "\n";
