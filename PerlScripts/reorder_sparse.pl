#!/bin/perl
use POSIX;
#
# Reorders the matrix with the simple algorithm which is O(n^2log(n)) if
# the matrix is sparse
#
# May 08, 2008.	Vamsi Kundeti
# Each testcase should start with 'n' followed by 'n' lines
# May 19, 2008 updated to read the sparse file format (compressed column)
#

$line = <STDIN>;
chomp($line);
@colptr = split(' ',$line);
$line = <STDIN>;
chomp($line);
@rowind = split(' ',$line);
$line = <STDIN>;
@nnz = split(' ',$line);

$nnz_count = 0;
$n = $#colptr;
print "n is $n\n";
print "nnz is $#nnz \n";
print "row is $#rowind \n";
%A;
%col_entries; %row_entries;
%single_row; %single_col;
foreach($j=0;$j<$#colptr;$j++){
	$len = $colptr[$j+1] - $colptr[$j];
	for($l=0; $l<$len;$l++){
		$i = $rowind[($colptr[$j]-1)+$l]-1;
		$value = $nnz[$nnz_count];
		chomp($value);
		$str = "$i $j";
		if(!exists $col_entries{$j}){
			$col_entries{$j} = 1;
			$single_col{$j} = $i;
		}else{
			$col_entries{$j} = $col_entries{$j}+1;
		}

		if(!exists $row_entries{$i}){
			$row_entries{$i} = 1;
			$single_row{$i} = $j;
		}else{
			$row_entries{$i} = $row_entries{$i}+1;
		}
		$nnz_count++;
		$A{$str} = fabs($value);
	}
}
#
# Sort based on the values in the matrix 
#
@sorted_keys = reverse sort {$A{$a} <=> $A{$b}} keys %A;

%fix_cols; %fix_rows;
foreach $m (keys %col_entries){
	if($col_entries{$m}==1){
		$fix_cols{$m} = $single_col{$m};
	}
}

foreach $m (keys %row_entries){
	if($row_entries{$m}==1){
		$fix_rows{$m} = $single_row{$m};
	}
}

=for
print "Sorted Order\n";
foreach $k (@sorted_keys){
	$value = $A{$k};
	print "$k [$value]\n";
}
=cut

$current_max = -1;
%row_hash; %col_hash;
@max_match = ();
$match_value;
$match_size = 0;
%irow_hash; %icol_hash;
@icurrent_match;
#
# Fix the rows or columns which have only 1 entry.
#
foreach $m (keys %fix_cols){
	$rv = $fix_cols{$m};
	$icol_hash{$m}=$rv;
	$irow_hash{$rv}=$m;
}

foreach $m (keys %fix_rows){
	$cv = $fix_rows{$m};
	$irow_hash{$m} = $cv;
	$icol_hash{$cv} = $m;
}
$imatch_size = 0;
foreach $m (keys %icol_hash){
	$str = "[$row_i $col_i]";
	push(@icurrent_match,$str);
	$imatch_size++;
}


for($i=0;$i<=$#sorted_keys;$i++){
	%row_hash = %irow_hash; %col_hash = %icol_hash;
	$match_value = $A{$sorted_keys[$i]};
	$sorted_keys[$i] =~ /([\d]+) ([\d]+)/;
	$row_i = $1; $col_i = $2;
	@current_match = @icurrent_match;
	$match_size = $imatch_size;

	if(!exists $row_hash{$row_i} && !exists $col_hash{$col_i}){
		$row_hash{$row_i}=$col_i; $col_hash{$col_i}=$row_i;
		$match_size = $match_size+1;
	}else{
		next;
	}

	for($j=$i+1;$j<=$#sorted_keys;$j++){
		$sorted_keys[$j] =~ /([\d]+) ([\d]+)/;
		$row_j = $1; $col_j = $2;
		if(!exists($row_hash{$row_j}) && !exists($col_hash{$col_j})){
			$str = "[$row_j $col_j]";
			push(@current_match,$str);
			$match_value = fabs($match_value * ($A{$sorted_keys[$j]}));
			$row_hash{$row_j} = 1; $col_hash{$col_j} = 1;
			$match_size++;
		}
	}
	if($match_value > $current_max && $match_size == $n){
		$current_max = $match_value;
		@max_match = @current_match;
	}
}

print "Optimal value found with $current_max \n";
print "Printing the match [row col]\n";
foreach $k (@max_match){
	print "$k\n";
}
