#ifndef _ALPHA_HEAP_H
#define _ALPHA_HEAP_H
#include "Heap.h"
typedef struct _aheap_ {
	/*All the elements in the alpha array 
	 *are such that whose value <= d_min (1+\alpha)
	 */
	unsigned long *alpha_array;
	unsigned long afill;
	Heap *h;
}AlphaHeap;
AlphaHeap* NewAlphaHeap(KeyCompare,unsigned int,KeyMapFunction);
#endif
