Flat profile:

Each sample counts as 0.01 seconds.
  %   cumulative   self              self     total           
 time   seconds   seconds    calls   s/call   s/call  name    
 50.26     56.91    56.91        1    56.91    56.91  ReadSparseGraph(_IO_FILE*)
 49.57    113.04    56.13        1    56.13    56.13  MC64Driver(int, char**)
  0.09    113.14     0.10        1     0.10     0.10  void ComputeInitialExtremeMatch<double, unsigned>(double*, double*, double*, double*, unsigned*, unsigned*, unsigned*, unsigned*, unsigned, double*)
  0.04    113.18     0.04        1     0.04     0.14  unsigned WeightedMatching<unsigned, unsigned, unsigned, double, char (*)(void*, void*)>(unsigned*, unsigned*, double*, double*, double*, double*, double*, unsigned*, unsigned*, unsigned*, unsigned, char (*)(void*, void*))
  0.02    113.20     0.02        1     0.02     0.02  LogTransform(_sparse_graph_*)
  0.02    113.22     0.02                             mc64ad_
  0.01    113.23     0.01                             main
  0.01    113.24     0.01                             mc64wd_
  0.00    113.24     0.00        2     0.00     0.00  HeapDelete(_heap_*)
  0.00    113.24     0.00        2     0.00     0.00  StartClock()
  0.00    113.24     0.00        2     0.00     0.00  GetDistKeyID(void*)
  0.00    113.24     0.00        2     0.00     0.00  GetClockTicks()
  0.00    113.24     0.00        2     0.00     0.00  StopClock()
  0.00    113.24     0.00        2     0.00     0.00  putchar
  0.00    113.24     0.00        1     0.00     0.00  InsertHeap(_heap_*, void*)
  0.00    113.24     0.00        1     0.00     0.00  NewBinaryHeap(char (*)(void*, void*), unsigned, unsigned (*)(void*))
  0.00    113.24     0.00        1     0.00     0.00  ComputePermutation(int*, int*, double*, int, int, int*)
  0.00    113.24     0.00        1     0.00     0.00  Heapify(_heap_*, unsigned)
  0.00    113.24     0.00        1     0.00     0.00  FreeHeap(_heap_*)

 %         the percentage of the total running time of the
time       program used by this function.

cumulative a running sum of the number of seconds accounted
 seconds   for by this function and those listed above it.

 self      the number of seconds accounted for by this
seconds    function alone.  This is the major sort for this
           listing.

calls      the number of times this function was invoked, if
           this function is profiled, else blank.
 
 self      the average number of milliseconds spent in this
ms/call    function per call, if this function is profiled,
	   else blank.

 total     the average number of milliseconds spent in this
ms/call    function and its descendents per call, if this 
	   function is profiled, else blank.

name       the name of the function.  This is the minor sort
           for this listing. The index shows the location of
	   the function in the gprof listing. If the index is
	   in parenthesis it shows where it would appear in
	   the gprof listing if it were to be printed.

		     Call graph (explanation follows)


granularity: each sample hit covers 4 byte(s) for 0.01% of 113.24 seconds

index % time    self  children    called     name
                                                 <spontaneous>
[1]    100.0    0.01  113.20                 main [1]
               56.91    0.00       1/1           ReadSparseGraph(_IO_FILE*) [2]
               56.13    0.00       1/1           MC64Driver(int, char**) [3]
                0.04    0.10       1/1           unsigned WeightedMatching<unsigned, unsigned, unsigned, double, char (*)(void*, void*)>(unsigned*, unsigned*, double*, double*, double*, double*, double*, unsigned*, unsigned*, unsigned*, unsigned, char (*)(void*, void*)) [4]
                0.02    0.00       1/1           LogTransform(_sparse_graph_*) [7]
                0.00    0.00       1/2           StartClock() [29]
                0.00    0.00       1/2           GetClockTicks() [31]
                0.00    0.00       1/2           StopClock() [32]
                0.00    0.00       1/2           putchar [9]
-----------------------------------------------
               56.91    0.00       1/1           main [1]
[2]     50.3   56.91    0.00       1         ReadSparseGraph(_IO_FILE*) [2]
-----------------------------------------------
               56.13    0.00       1/1           main [1]
[3]     49.6   56.13    0.00       1         MC64Driver(int, char**) [3]
                0.00    0.00       1/1           ComputePermutation(int*, int*, double*, int, int, int*) [35]
                0.00    0.00       1/2           putchar [9]
-----------------------------------------------
                0.04    0.10       1/1           main [1]
[4]      0.1    0.04    0.10       1         unsigned WeightedMatching<unsigned, unsigned, unsigned, double, char (*)(void*, void*)>(unsigned*, unsigned*, double*, double*, double*, double*, double*, unsigned*, unsigned*, unsigned*, unsigned, char (*)(void*, void*)) [4]
                0.10    0.00       1/1           void ComputeInitialExtremeMatch<double, unsigned>(double*, double*, double*, double*, unsigned*, unsigned*, unsigned*, unsigned*, unsigned, double*) [5]
                0.00    0.00       2/2           HeapDelete(_heap_*) [28]
                0.00    0.00       1/1           NewBinaryHeap(char (*)(void*, void*), unsigned, unsigned (*)(void*)) [34]
                0.00    0.00       1/1           FreeHeap(_heap_*) [37]
                0.00    0.00       1/1           InsertHeap(_heap_*, void*) [33]
-----------------------------------------------
                0.10    0.00       1/1           unsigned WeightedMatching<unsigned, unsigned, unsigned, double, char (*)(void*, void*)>(unsigned*, unsigned*, double*, double*, double*, double*, double*, unsigned*, unsigned*, unsigned*, unsigned, char (*)(void*, void*)) [4]
[5]      0.1    0.10    0.00       1         void ComputeInitialExtremeMatch<double, unsigned>(double*, double*, double*, double*, unsigned*, unsigned*, unsigned*, unsigned*, unsigned, double*) [5]
-----------------------------------------------
                                                 <spontaneous>
[6]      0.0    0.02    0.00                 mc64ad_ [6]
-----------------------------------------------
                0.02    0.00       1/1           main [1]
[7]      0.0    0.02    0.00       1         LogTransform(_sparse_graph_*) [7]
-----------------------------------------------
                                                 <spontaneous>
[8]      0.0    0.01    0.00                 mc64wd_ [8]
-----------------------------------------------
                0.00    0.00       1/2           MC64Driver(int, char**) [3]
                0.00    0.00       1/2           main [1]
[9]      0.0    0.00    0.00       2         putchar [9]
-----------------------------------------------
                0.00    0.00       2/2           unsigned WeightedMatching<unsigned, unsigned, unsigned, double, char (*)(void*, void*)>(unsigned*, unsigned*, double*, double*, double*, double*, double*, unsigned*, unsigned*, unsigned*, unsigned, char (*)(void*, void*)) [4]
[28]     0.0    0.00    0.00       2         HeapDelete(_heap_*) [28]
                0.00    0.00       1/1           Heapify(_heap_*, unsigned) [36]
                0.00    0.00       1/2           GetDistKeyID(void*) [30]
-----------------------------------------------
                0.00    0.00       1/2           ComputePermutation(int*, int*, double*, int, int, int*) [35]
                0.00    0.00       1/2           main [1]
[29]     0.0    0.00    0.00       2         StartClock() [29]
-----------------------------------------------
                0.00    0.00       1/2           InsertHeap(_heap_*, void*) [33]
                0.00    0.00       1/2           HeapDelete(_heap_*) [28]
[30]     0.0    0.00    0.00       2         GetDistKeyID(void*) [30]
-----------------------------------------------
                0.00    0.00       1/2           ComputePermutation(int*, int*, double*, int, int, int*) [35]
                0.00    0.00       1/2           main [1]
[31]     0.0    0.00    0.00       2         GetClockTicks() [31]
-----------------------------------------------
                0.00    0.00       1/2           ComputePermutation(int*, int*, double*, int, int, int*) [35]
                0.00    0.00       1/2           main [1]
[32]     0.0    0.00    0.00       2         StopClock() [32]
-----------------------------------------------
                0.00    0.00       1/1           unsigned WeightedMatching<unsigned, unsigned, unsigned, double, char (*)(void*, void*)>(unsigned*, unsigned*, double*, double*, double*, double*, double*, unsigned*, unsigned*, unsigned*, unsigned, char (*)(void*, void*)) [4]
[33]     0.0    0.00    0.00       1         InsertHeap(_heap_*, void*) [33]
                0.00    0.00       1/2           GetDistKeyID(void*) [30]
-----------------------------------------------
                0.00    0.00       1/1           unsigned WeightedMatching<unsigned, unsigned, unsigned, double, char (*)(void*, void*)>(unsigned*, unsigned*, double*, double*, double*, double*, double*, unsigned*, unsigned*, unsigned*, unsigned, char (*)(void*, void*)) [4]
[34]     0.0    0.00    0.00       1         NewBinaryHeap(char (*)(void*, void*), unsigned, unsigned (*)(void*)) [34]
-----------------------------------------------
                0.00    0.00       1/1           MC64Driver(int, char**) [3]
[35]     0.0    0.00    0.00       1         ComputePermutation(int*, int*, double*, int, int, int*) [35]
                0.00    0.00       1/2           StartClock() [29]
                0.00    0.00       1/2           GetClockTicks() [31]
                0.00    0.00       1/2           StopClock() [32]
-----------------------------------------------
                0.00    0.00       1/1           HeapDelete(_heap_*) [28]
[36]     0.0    0.00    0.00       1         Heapify(_heap_*, unsigned) [36]
-----------------------------------------------
                0.00    0.00       1/1           unsigned WeightedMatching<unsigned, unsigned, unsigned, double, char (*)(void*, void*)>(unsigned*, unsigned*, double*, double*, double*, double*, double*, unsigned*, unsigned*, unsigned*, unsigned, char (*)(void*, void*)) [4]
[37]     0.0    0.00    0.00       1         FreeHeap(_heap_*) [37]
-----------------------------------------------

 This table describes the call tree of the program, and was sorted by
 the total amount of time spent in each function and its children.

 Each entry in this table consists of several lines.  The line with the
 index number at the left hand margin lists the current function.
 The lines above it list the functions that called this function,
 and the lines below it list the functions this one called.
 This line lists:
     index	A unique number given to each element of the table.
		Index numbers are sorted numerically.
		The index number is printed next to every function name so
		it is easier to look up where the function in the table.

     % time	This is the percentage of the `total' time that was spent
		in this function and its children.  Note that due to
		different viewpoints, functions excluded by options, etc,
		these numbers will NOT add up to 100%.

     self	This is the total amount of time spent in this function.

     children	This is the total amount of time propagated into this
		function by its children.

     called	This is the number of times the function was called.
		If the function called itself recursively, the number
		only includes non-recursive calls, and is followed by
		a `+' and the number of recursive calls.

     name	The name of the current function.  The index number is
		printed after it.  If the function is a member of a
		cycle, the cycle number is printed between the
		function's name and the index number.


 For the function's parents, the fields have the following meanings:

     self	This is the amount of time that was propagated directly
		from the function into this parent.

     children	This is the amount of time that was propagated from
		the function's children into this parent.

     called	This is the number of times this parent called the
		function `/' the total number of times the function
		was called.  Recursive calls to the function are not
		included in the number after the `/'.

     name	This is the name of the parent.  The parent's index
		number is printed after it.  If the parent is a
		member of a cycle, the cycle number is printed between
		the name and the index number.

 If the parents of the function cannot be determined, the word
 `<spontaneous>' is printed in the `name' field, and all the other
 fields are blank.

 For the function's children, the fields have the following meanings:

     self	This is the amount of time that was propagated directly
		from the child into the function.

     children	This is the amount of time that was propagated from the
		child's children to the function.

     called	This is the number of times the function called
		this child `/' the total number of times the child
		was called.  Recursive calls by the child are not
		listed in the number after the `/'.

     name	This is the name of the child.  The child's index
		number is printed after it.  If the child is a
		member of a cycle, the cycle number is printed
		between the name and the index number.

 If there are any cycles (circles) in the call graph, there is an
 entry for the cycle-as-a-whole.  This entry shows who called the
 cycle (as parents) and the members of the cycle (as children.)
 The `+' recursive calls entry shows the number of function calls that
 were internal to the cycle, and the calls entry for each member shows,
 for that member, how many times it was called from other members of
 the cycle.


Index by function name

  [28] HeapDelete(_heap_*)    [34] NewBinaryHeap(char (*)(void*, void*), unsigned, unsigned (*)(void*)) [32] StopClock()
  [33] InsertHeap(_heap_*, void*) [2] ReadSparseGraph(_IO_FILE*) [1] main
   [3] MC64Driver(int, char**) [4] unsigned WeightedMatching<unsigned, unsigned, unsigned, double, char (*)(void*, void*)>(unsigned*, unsigned*, double*, double*, double*, double*, double*, unsigned*, unsigned*, unsigned*, unsigned, char (*)(void*, void*)) [6] mc64ad_
  [29] StartClock()           [35] ComputePermutation(int*, int*, double*, int, int, int*) [8] mc64wd_
  [30] GetDistKeyID(void*)     [5] void ComputeInitialExtremeMatch<double, unsigned>(double*, double*, double*, double*, unsigned*, unsigned*, unsigned*, unsigned*, unsigned, double*) [9] putchar
   [7] LogTransform(_sparse_graph_*) [36] Heapify(_heap_*, unsigned)
  [31] GetClockTicks()        [37] FreeHeap(_heap_*)
