#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
/*Simple O(n^2) Insertion sort*/
void InsertionSort(int *A,unsigned int len){
	int i,k;
	int value;
	for(i=0;i<len;i++){
		value = A[i];
		for(k=i-1;k>=0;k--){
			if(A[k] <= value){
				break;
			}
			A[k+1] = A[k];
		}
		A[k+1] = value;
	}
}
#ifdef UNIT_TEST_INSERTION_SORT 
int main(){
	unsigned int i;
	printf("Please enter the # of elements\n");
	scanf("%u",&length);
	A = (int *) malloc(sizeof(int)*length);
	assert(A);
	for(i=0;i<length;i++){
		assert(scanf("%d",&A[i])==1);
	}
	InsertSort(A,length);
	PrintElements();
}
#endif
