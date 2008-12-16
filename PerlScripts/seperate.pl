open(MAIN_TESTS,"total_tests.txt") or die("$!\n");
open(RUNTHIS,">not_finished.txt") or die("$!\n");
open(FINISHED,"finished_tests.txt");
%test_hash;
while(<FINISHED>){
	 $line = $_;
	  chomp($line);
	  $test_hash{$line} = 1;
}
while(<MAIN_TESTS>){
	$line = $_;
	chomp($line);
	if(exists $test_hash{$line}){
		next;
	}else{
		print RUNTHIS "../bipartite1 $line\n";
	}

}

close(RUNTHIS);
close(MAIN_TESTS);
close(FINISHED);

