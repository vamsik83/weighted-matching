/*
 * Adding Heap to myutil.
 * DATE: 02/28/08
 * Vamsi Kundeti (vamsik@engr.uconn.edu)
 *
 * June 5,2008. Modified to 1 indexing. @Ansoft 
 * June 6,2008. Unit tested with doubles @Ansoft
 * June 9,2008. Added the DecreaseKey opeartion @Ansoft
 */
/*Heap Specifically tuned to find Shortest Augmenting Path.*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<assert.h>
#include<string.h>
#include "Heap.h"
#define NO_ASSERTs

extern unsigned long dist_base;
inline keyid_t GetDistKeyID1(void *dist_ptr){ assert((unsigned long)dist_ptr >= dist_base);
	return (((((unsigned long)dist_ptr-dist_base))/sizeof(double))+1);
}

inline char DoubleCompare1(void *a,void *b);
/*Swap two address's*/
inline void XORSwap(void *a,void *b){
	unsigned long *a1 = (unsigned long *)a;
	unsigned long *b1 = (unsigned long *)b;
	if(*a1 == *b1) return;
	(*a1) = ((*a1)^(*b1));
	(*b1) = ((*a1)^(*b1));
	(*a1) = ((*a1)^(*b1));
}

inline void Heapify(Heap *h,unsigned int i){
	unsigned long **harray = (unsigned long **)h->heapArray;
	unsigned long n = h->n;
	unsigned int index;
	unsigned int kid1,kid2;

	while(i<=(n/2)){
		index = ((2*i+1)>n)?(2*i):((DoubleCompare1((void *)harray[2*i],
			(void *)harray[2*i+1]))? (2*i):(2*i+1));
#ifndef NO_ASSERTS 
		assert(i< n && index <=n);
#endif
		if(!((DoubleCompare1)(harray[i],harray[index]))){ 
			/*Update the indices to help decrease key.*/
		/*	if(h->keyMap && h->GetKeyID){*/ /*Minimize Checks*/
				kid1 = (GetDistKeyID1)(harray[i]);
				kid2 = (GetDistKeyID1)(harray[index]);
#ifndef NO_ASSERTS
				assert(kid1>=1 && kid1<=h->keyMapSize);
				assert(kid2>=1 && kid2<=h->keyMapSize);
				assert((h->keyMap)[kid1]==i && (h->keyMap)[kid2]==index);
#endif
				(h->keyMap)[kid1] = index;
				(h->keyMap)[kid2] = i; 
		/*	}*/
			XORSwap(&harray[i],&harray[index]);
		}else{
			break;
		}
		i = index;
	}
}
/*A Simpler Interface compared to HeapInsert*/
unsigned int InsertHeap(Heap *h,void *key){
#ifdef DYNAMIC_EXPAND
	unsigned long **ptr = NULL;
#endif
	unsigned long **harray = NULL;
	unsigned int i;
	unsigned int kid1,kid2;
#ifndef NO_ASSERTS	
	assert(h);
	assert(h->n <= h->fill);
#endif

#ifdef DYNAMIC_EXPAND 
	/*Expand If necessary:Double the heap size*/
	if(((h->n)+1) > h->fill){
		ptr = (unsigned long **)malloc(sizeof(unsigned long *)*(2*h->fill));
		assert(memcpy(ptr,++(h->heapArray),(h->n)*(sizeof(unsigned long*))) == ptr);
		free(h->heapArray);
		h->heapArray = ptr;
		(h->heapArray)--;
		h->fill =2*(h->fill);
	}
#endif

	harray = (unsigned long **)h->heapArray;
	i = (h->n)+1;
	harray[i] = (unsigned long *)key;
	/*if(h->keyMap && h->GetKeyID){*/ /*Minimize Checks*/
		/*Supporting Decrease Key operation.*/
		kid1 = (GetDistKeyID1)(key);
#ifndef NO_ASSERTS
		assert(kid1>=1 && kid1<=h->keyMapSize);
#endif
		(h->keyMap)[kid1] = i;
	/*}*/

	while(i>1){
		if((DoubleCompare1)(harray[i],harray[i/2])){
		/*	if(h->keyMap && h->GetKeyID){ */
				/*Supporting Decrease Key Operation*/
				kid1 = (GetDistKeyID1)(harray[i]);
				kid2 = (GetDistKeyID1)(harray[i/2]);
#ifndef NO_ASSERTS
				assert((h->keyMap)[kid1]==i && (h->keyMap)[kid2]==(i/2));
#endif
				(h->keyMap)[kid1] = i/2; 
				(h->keyMap)[kid2] = i; 
			/*} */
			XORSwap(&(harray[i]),&(harray[i/2]));
		}else{
			break;
		}
		i = i/2;
	}
	h->n +=1;
	return i;
}
/*Returns the position where the insert happened, If h1=NULL
 *the heap will be created automatically
 */
unsigned int HeapInsert(Heap **h1,void *key,KeyCompare cmp){
	unsigned long **ptr = NULL;
	unsigned long **harray = NULL;
	Heap *h;
	unsigned int i;
	if(!(*h1)){
		*h1 = (Heap *)malloc(sizeof(Heap)*1);
		(*h1)->n = 0;
		(*h1)->heapArray = (unsigned long **)malloc(sizeof(unsigned long *)*(HEAP_START_SIZE));
		((*h1)->heapArray)--;
#ifndef NO_ASSERTS
		assert((*h1)->heapArray);
#endif
		(*h1)->fill = HEAP_START_SIZE;
		(*h1)->cmp = cmp; 
	}
	h = *h1;
#ifndef NO_ASSERTS
	/*Sanity Check*/
	assert(h->n <= h->fill);
#endif
	/*Expand If necessary:Double the heap size*/
	if(((h->n)+1) > h->fill){
		ptr = (unsigned long **)malloc(sizeof(unsigned long *)*(2*h->fill));
		assert(memcpy(ptr,++(h->heapArray),(h->n)*(sizeof(unsigned long*))) == ptr);
		free(h->heapArray);
		h->heapArray = ptr;
		(h->heapArray)--;
		h->fill =2*(h->fill);
	}
	harray = (unsigned long **)h->heapArray;
	i = (h->n)+1;
	harray[i] = (unsigned long *)key;
	while(i>1){
		if((DoubleCompare1)(harray[i],harray[i/2])){
			XORSwap(&(harray[i]),&(harray[i/2]));
		}else{
			break;
		}
		i = i/2;
	}
	h->n +=1;
	return i;
}

void* GetMin(Heap *h){
	return (!h->n)?NULL:(((unsigned long **)h->heapArray)[1]);
}

/*Delete's the root and returns's it*/
void* HeapDelete(Heap *h){
#ifndef NO_ASSERTS
	assert(h);
#endif
	unsigned long **harray = (unsigned long **)h->heapArray;
	void *element=NULL;
	unsigned int kid;
	if(!h->n){
		return NULL;
	}
	element = harray[1]; 
	harray[1] = harray[h->n];
	h->n -= 1;
	/*if(h->keyMap && h->GetKeyID){ */
		/*Supporting the decrease key operation*/
		kid = (GetDistKeyID1)(harray[1]);
		(h->keyMap)[kid] = 1;
	/*}*/
	Heapify(h,1);	
	return element;
}
void FreeHeap(Heap *h){
	assert(h);
	free(++(h->heapArray));
	if(h->keyMap){free(++(h->keyMap));}
	free(h);
}
/*User Creates keyMapArray of size nkeys and calls this function.*/
void SetKeyMapArray(Heap *h,unsigned long nkeys,void *keyMapArray){
	assert(h);
	h->keyMap = (unsigned int *)keyMapArray;
	h->keyMapSize = nkeys;
}
/*
 *Specify the cmp and keyMap size if you need to support
 *DecreaseKey operation
 */
Heap* NewBinaryHeap(KeyCompare cmp,unsigned int keyMapSize,
	KeyMapFunction keyMapFunc){
	Heap *h = (Heap *)malloc(sizeof(Heap)*1);
	if(keyMapFunc && keyMapSize){
		h->keyMapSize = keyMapSize;
		h->GetKeyID = keyMapFunc;
		h->keyMap = (unsigned int *)
			calloc(h->keyMapSize,sizeof(unsigned int));
		assert(h->keyMap);
		(h->keyMap)--;
	}
	h->n = 0;
	h->heapArray = (unsigned long **)malloc(sizeof(unsigned long)*(keyMapSize/*HEAP_START_SIZE*/));
	h->fill = keyMapSize/*HEAP_START_SIZE*/;
	assert(h->heapArray);
	h->cmp = cmp;
	(h->heapArray)--; 
	return h;
}
/*Decrease Key: This is very useful in shortest path
 *algorithms. The user need not pass the value here
 *
 */
unsigned int DecreaseKey(Heap *h,keyid_t kid){
	unsigned int i,kid1,kid2;
	unsigned long **harray = NULL;
#ifndef NO_ASSERTS
	assert(h && h->keyMap);
#endif
	harray = h->heapArray;
	i = (h->keyMap)[kid];
	/*
	 *the keyid should be less than
	 *the keyMapSize we started off initially
	 */
#ifndef NO_ASSERTS
	assert(harray && kid>=1 && kid<= h->keyMapSize);
	assert(i>=1 && i<=(h->n) && h->cmp);
#endif

	while(i>1){
		if((DoubleCompare1)(harray[i],harray[i/2])){
			/*Swap These two address's*/
			kid1 = (GetDistKeyID1)(harray[i/2]);
			kid2 = (GetDistKeyID1)(harray[i]);
#ifndef NO_ASSERTS
			assert((h->keyMap)[kid1]== i/2 && (h->keyMap)[kid2]==i);
#endif
			(h->keyMap)[kid1] = i; 
			(h->keyMap)[kid2] = i/2; 
			XORSwap(&harray[i/2],&harray[i]);
		}else{
			break;
		}
		i = i/2;
	}
	return i;
}
/*Builds a heap from the 'h' (an array of pointers to the
data elements held by the heap). A virtual address is a unsigned 
long, so void* will be casted to unsigned long*/
Heap* BuildHeap(unsigned long **h,size_t n,KeyCompare c){
	unsigned int i;
	Heap *hptr = NULL;
	hptr = (Heap *) malloc(sizeof(Heap)*1);
	hptr->heapArray = h;
	(hptr->heapArray)--;
	/*Heap*/
	hptr->n = n; hptr->fill = n; hptr->cmp = c;
	
	for(i=(n/2);i>=1;i--){
		Heapify(hptr,i);
	}
	return hptr;
}
void* GetMax(Heap *h){
	return (void *)*((unsigned long *)h->heapArray);
}
inline char IntCompare(void *a,void *b){
	int a1,b1;
	a1 = *((int *)a);b1 = *((int *)b);
	return (a1 <= b1)?(char)1:(char)0;
}
/*This works only for positive doubles*/
inline char DoubleCompare1(void *a,void *b){
	//return (*((long long int*)a) <= *((long long int*)b))?(char)1:(char)0;
	return (*((double*)a)<=*((double *)b));
}

char DoubleCompare(void *a,void *b){
	return '0';
}
#ifdef XOR_TEST
int main(int argc,char **argv){
	unsigned int *a = malloc(10);
	unsigned int *b = a;
	XORSwap(&a,&b);
	printf("a=%x b=%x\n",a,b);
}
#endif
#ifdef UNIT_TEST
int main(int argc,char** argv){
	char typebuffer[128];
	scanf("%s",typebuffer);
	if(!strcmp(typebuffer,"double")){
		HeapTestDoubleCompare(argc,argv);
	}else if(!strcmp(typebuffer,"int")){
		HeapTestIntCompare(argc,argv);
	}else{
		fprintf(stderr,"Unrecognised type...quitting\n");
	}
	return 0;
}
int HeapTestDoubleCompare(int argc,char **argv){
	double *doublearray=NULL;
	double prevdouble; double currentdouble;
	Heap *heap = NULL; 
	int n;int i=0,k=0;
	unsigned long **heaparray = NULL;
	scanf("%d",&n);
	doublearray = (double *)malloc(sizeof(double)*n);
	assert(doublearray);
	while(i<n){
		scanf("%lf",&doublearray[i++]);
		HeapInsert(&heap,(void *)&doublearray[i-1],DoubleCompare);
	}
	printf("Deleting the heap\n");

	for(k=0;k<n;k++){
	}

	while(i){
		currentdouble = *((double *)HeapDelete(heap));
		if(i<n){
			assert(DoubleCompare((void *)&prevdouble,(void *)&currentdouble));
		}
		prevdouble = currentdouble;
		i--;
	}
	printf("Test Passed...\n");
	FreeHeap(heap);
	heaparray = (unsigned long **)malloc(sizeof(unsigned long *)*n);
	for(i=0;i<n;i++){
		heaparray[i] = (unsigned long *)&(doublearray[i]);
	}
	printf("Unit Testing the BuildHeap Operation \n");
	heap = BuildHeap(heaparray,n,DoubleCompare);
	for(i=0;i<n;i++){
		currentdouble = *((double *)HeapDelete(heap));
		if(i>0){
			assert(DoubleCompare((void *)&prevdouble,(void *)&currentdouble));
		}
		prevdouble = currentdouble;
	}
	FreeHeap(heap);
	fprintf(stdout,"UNIT TESTING OF BuildHeap Passed\n");
	return 0;
}
int HeapTestIntCompare(int argc,char **argv){
	Heap *heap = NULL;
	int *intarray;
	int i=0;
	int prevint;
	int currentint;
	int n;
	unsigned long **heaparray = NULL;

	printf("Enter n\n");
	scanf("%d",&n);

	intarray = (int *)malloc(sizeof(int)*n);
	assert(intarray);
	printf("Please enter the Integers:\n");
	while(i<n){
		scanf("%d",&intarray[i++]);
		HeapInsert(&heap,(void *)&intarray[i-1],IntCompare);
	}
	printf("Deleteing the heap\n");
	while(i){
		currentint = *((int *)HeapDelete(heap));
		printf("%d ",currentint);
		if(i<n &&  i>1){
			assert(prevint <= currentint);
		}
		prevint = currentint;
		i--;
	}
	FreeHeap(heap);
	printf("UNIT TEST FOR HEAP INSERT PASSED...\n");
	printf("UNIT TESTING O(n) BuildHeap...\n");

	heaparray = (unsigned long **)malloc(sizeof(unsigned long *)*n);
	for(i=0;i<n;i++){
		heaparray[i]= (unsigned long *)&(intarray[i]);
	}
	heap = BuildHeap(heaparray,n,IntCompare);
	for(i=0;i<n;i++){
		currentint = *((int *) HeapDelete(heap));
		printf("%d ",currentint);
		if(i>0){
			assert(prevint <= currentint);
		}
		prevint = currentint;
	}
	FreeHeap(heap);
	printf("UNIT TEST BuildHeap Passed on Integers\n");
	return 0;
}
unsigned long array_key_base = 0;
/*The heap calls this function with 
the pointer to the data
*/
inline unsigned int ArrayKeyMap(void *data_ptr){
	return (((unsigned long)data_ptr - 
		array_key_base)/sizeof(int)+1);
}
/*UNIT TESTING */
int UnitTestDecreaseKey(int argc,char **argv){
	Heap *h = NULL;
	int n;
	int current_int,previous_int;
	int *data_array = NULL;
	int i;
	scanf("%d",&n); assert(n>0);
	data_array = (int *)malloc(sizeof(int)*n);
	assert(data_array);
	array_key_base = (unsigned long) data_array;
	h = NewBinaryHeap(IntCompare,n,ArrayKeyMap);
	assert(h);
	for(i=0;i<n;i++){
		scanf("%d",&data_array[i]);
		InsertHeap(h,&data_array[i]);
	}

	/*Now decrease the key's by some amount*/
	for(i=1;i<=n;i++){
		if(i%2){
			if(data_array[i-1] > 0){
				data_array[i-1] = data_array[i-1]/2;
			}else{
				data_array[i-1] = 2*data_array[i-1];
			}
			DecreaseKey(h,i);
		}
	}
	for(i=1;i<=n;i++){
		current_int = *((int *)HeapDelete(h));
		printf("%d ",current_int);
		if(i>1){
			assert(previous_int <= current_int);
		}
		previous_int = current_int;
	}
}
#endif
