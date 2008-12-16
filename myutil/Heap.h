#ifndef _MY_UTIL_HEAP
#define _MY_UTIL_HEAP
#define MAX_HEAP 1
#define MIN_HEAP 0
/*This assumes the keyid's of the keys are within 
 *the range of unsigned int 
 */
typedef unsigned int keyid_t;
typedef char (*KeyCompare)(void*,void*);
/*PHeap: Is a pointer heap, this works independently of
 *the data items.That is PHeap maintains a array of pointers
 *to the data items and just manupulates the pointer array.
 *all the operations need/return pointer to the data item.
 *so PHeap is independent of any type
 */
typedef struct _heap_{
	unsigned long **heapArray;
	unsigned long n;
	unsigned long fill;
	char (*cmp)(void *,void *);
	unsigned int *keyMap;
	unsigned long keyMapSize;
	unsigned int (*GetKeyID)(void *);
}PHeap;
typedef PHeap Heap;
void* GetMax(Heap *);
void* GetMin(Heap *);
char DoubleEqual(double a,double b);
char DoubleCompare(void *a,void *b);
unsigned int HeapInsert(Heap **h1,void *key,KeyCompare cmp);
void* HeapDelete(Heap *h);
void FreeHeap(Heap *h);
Heap* BuildHeap(unsigned long **h,size_t n,KeyCompare c);
typedef unsigned int (*KeyMapFunction)(void *key);
Heap* NewBinaryHeap(KeyCompare,unsigned int,
	KeyMapFunction);
unsigned int DecreaseKey(Heap *,keyid_t);
unsigned int InsertHeap(Heap *,void *);
char CompareDoubles(double,double);
char CompareDoubles1(double,double);
char IntCompare(void *a,void *b);
char DoubleCompare(void *a,void *b);
/*UNIT TESTING DECLARATIONS*/
int HeapTestDoubleCompare(int argc,char **argv);
int HeapTestIntCompare(int argc,char **argv);
void SetKeyMapArray(Heap *h,unsigned long nkeys,void *keyMapArray);
char DoubleEqual(double a,double b);
#define HEAP_START_SIZE 2048 
#endif
