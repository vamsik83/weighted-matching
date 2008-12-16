#!/bin/perl
#
# Takes .gz file expands it and runs 
# the fast dual version and slow version
# and logs the details.
#
# perl run_ufl_tests.pl <.gz | .rcf file> -C RunDir
#

#
# Please include the full path.
#
$fast_dual_exec_name = "./bipartite1-linux64-fast-dual-update ";
$slow_dual_exec_name = "./bipartite1-linux64 ";

$#ARGV == 2 or die("USAGE: perl run_ufl_test.pl {.gz | .rcf file} -C {run_dir} \n");

$input_file = $ARGV[0];
$file_type = 0;
if($input_file =~ /\.rcf/){
	$file_type = 1;
}elsif($input_file =~ /\.tar\.gz/){
	$file_type = 2;
	if(!($ARGV[1] eq "-C")){
		die("ERROR: expecting -C <RUNDIR>");
	}
	if(!(-e $ARGV[2])){
		die("ERROR: The run directory does not exist");
	}
	$run_dir = $ARGV[2];
	print "INFO: Directory $run_dir will be used for generating all output\n";
	$tar_output = `tar -xvzf $input_file -C $run_dir`;
	if($tar_output =~ /Error/){
		die("ERROR: Execution of tar failed");
	}
	@extracted_files = split('\n',$tar_output);
	for($k=0;$k<=$#extracted_files;$k++){
		$extracted_files[$k] = $run_dir."/".$extracted_files[$k];
# RUN MM2RC to create a .rcf file
		$file_name = $extracted_files[$k];
		print "EXTRACTED FILE $file_name \n";
		$output = `perl mm2rc.pl $file_name`;
		if(!($output =~ /SUCCESSFUL/)){
			die("FATAL: Failed to Create the .rcf file");
		}
		$file_name =~ /(.*)\.mtx/;
		$file_name = $1.".rcf";
		$extracted_files[$k] = $file_name;
		print "RCF FILE --> $file_name [CREATED]\n";
	}
}else{
	die("ERROR: Unrecognized file extension to do the test :( ");
}
#
# Run them in parallel.
#
$pid = fork();

if($pid == 0){
	foreach $i (@extracted_files){
		$output = `$fast_dual_exec_name $i`;
		$log_file_name = $i.".fast.log";
		open(FAST_LOG,">$log_file_name") or die("ERROR: $!");
		print FAST_LOG $output;
		close(FAST_LOG);
		print "LOG FILE $log_file_name [CREATED] \n";
	}
	exit(0);
}elsif($pid < 0){
	die("ERROR: Unable to fork to start the run in parallel");
}

#
# Run the slow dual in the parent
#
foreach $i (@extracted_files){
	$output = `$slow_dual_exec_name $i`;
	$log_file_name = $i.".slow.log";
	open(SLOW_LOG,">$log_file_name") or die("ERROR: $!");
	print SLOW_LOG $output;
	close(SLOW_LOG);
	print "LOG FILE $log_file_name [CREATED] \n";
}

$child_pid = wait();
print "CHILD exited with $? \n";

print "........DONE......\n";
