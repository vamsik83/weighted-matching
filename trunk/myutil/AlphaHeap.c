#include<stdlib.h>
#include "AlphaHeap.h"
#include "Heap.h"

AlphaHeap* NewAlphaHeap(KeyCompare cmp,unsigned int KeyMapSize,KeyMapFunction kfunc){
	AlphaHeap *aheap = NULL;
	aheap = (AlphaHeap *) malloc(sizeof(AlphaHeap)*1);
	aheap->alpha_array = (unsigned long *)malloc(sizeof(unsigned long)*KeyMapSize);
}
