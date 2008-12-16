#!/bin/perl
#
# Reorders the matrix with the simple algorithm which is O(n^4)
# if the matrix is dense
#
# May 08, 2008.	Vamsi Kundeti
# Each testcase should start with 'n' followed by 'n' lines
#
#

$n = <STDIN>;
chomp($n); 
%A;
$rowno = 0;
print "n is $n\n";
while(<STDIN>){
	$line = $_;
	@row = split(' ',$line);
	$rowno++;
	$colno = 0;
	foreach $i (@row){
		$colno++;
		chomp($i);
		$str = "$rowno $colno";
		$A{$str} = $i;

	}

	if($rowno == $n){
		last;
	}
}

#
# Sort based on the values in the matrix 
#
@sorted_keys = reverse sort {$A{$a} <=> $A{$b}} keys %A;

=for
print "Sorted Order\n";
foreach $k (@sorted_keys){
	$value = $A{$k};
	print "$k [$value]\n";
}
=cut

$current_max = 0;
%row_hash; %col_hash;
@max_match = ();
$match_value;
$match_size = 0;
for($i=0;$i<=$#sorted_keys;$i++){
	%row_hash = {}; %col_hash = {};
	$match_value = $A{$sorted_keys[$i]};
	$sorted_keys[$i] =~ /([\d]+) ([\d]+)/;
	$row_i = $1; $col_i = $2;
	$row_hash{$row_i}=1; $col_hash{$col_i}=1;
	@current_match = ();
	$str = "[$row_i $col_i]";
	push(@current_match,$str);
	$match_size = 1;

	for($j=$i+1;$j<=$#sorted_keys;$j++){
		$sorted_keys[$j] =~ /([\d]+) ([\d]+)/;
		$row_j = $1; $col_j = $2;
		if(!exists($row_hash{$row_j}) && !exists($col_hash{$col_j})){
			$str = "[$row_j $col_j]";
			push(@current_match,$str);
			$match_value = $match_value * ($A{$sorted_keys[$j]});
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
