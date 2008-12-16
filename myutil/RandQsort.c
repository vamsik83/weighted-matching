/*A generic Randomized Quicksort:
 *The key idea of being generic comes
 *from the fact that you take a memory 
 *block and size of each element and 
 *sort this memory chunk, so we always
 *deal with address's.
 *
 *
 *Sep 20,2007 vamsik@engr.uconn.edu
 **/
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<assert.h>
#include<string.h>
#include<math.h>
#include "RandQsort.h"

/*INPUT: swap_routine,compare_routine
 * swap_routine: The algorithm gives the 
 * (void *)'s swap_routine of two things
 * which need to be swapped.
 *
 * compare_routine: The algorithm gives the
 * (void *)'s to the compare_routine its 
 */
static char QSORT_RAND_SEED=0;
static void (*swap_routine)(void *,void *) = NULL;
static unsigned char (*compare_routine_l)(void *,void *) = NULL;
static unsigned char (*compare_routine_g)(void *,void *) = NULL;
static time_t t_rqsort;
unsigned int GetPivot(void){
	if(!QSORT_RAND_SEED){
		assert(((time_t)-1)!=time(&t_rqsort));
		srand(t_rqsort);
		//fprintf(stdout,"Setting RAND_SEED to %d \n",t_rqsort);
		QSORT_RAND_SEED=1;
	}
	return ((unsigned int)rand());
}
/*Avoid loosing the pivot during swaps*/
void UpdatePivot(void **pivot,void **i,void **j){
	if(*i==*pivot){
		*pivot = *j;
	}else if(*j == *pivot){
		*pivot = *i;
	}
}
/*Take a memory address location and size 
of the data items[Inplace partition]*/
static void PartitionWithPivot(void* start,void* end,
unsigned int dsize){
	void *pivot=NULL;
	void* i=start;
	void* j=end;
	unsigned int p_index = GetPivot();
	if(start==end){
		return;
	}
	p_index %= (((unsigned int)(end-start))/dsize);
	pivot=(void *)((unsigned long)start+
		(unsigned long)((p_index)*dsize));
	while(i<j){
		/*Find a element greater than the pivot*/
		while((i<=end) && compare_routine_l(i,pivot)){
			i+=dsize;
		}
		/*Find a element less than the pivot*/
		while( j>=start && !compare_routine_l(j,pivot)){
			j-=dsize;
		}
		/*Swap i,j*/
		if(i<j){
			/*Make sure we update the pivot.*/
			UpdatePivot(&pivot,&i,&j);
			swap_routine(i,j);
		}
	}
	/*i is the pivot element at (i-(dsize)) */
	if((i-dsize)>start){
		swap_routine(pivot,(void *)(i-dsize));
		PartitionWithPivot(start,(void *)(i-(2*dsize)),
		dsize);
	}
	if((i+dsize)<=end){
		PartitionWithPivot(i,end,dsize);
	}
}
/*Call PartitionWithPivot recursively*/
void RandQsort(void *start,void *end,unsigned int dsize,
void_void_fptr sroutine,bool_void_fptr croutine_l){
	swap_routine = sroutine;
	compare_routine_l = croutine_l;
	assert(swap_routine && compare_routine_l);
	PartitionWithPivot(start,end,dsize);
}
unsigned char CharCompare_L(void *a,void *b){
	return ((*((char *)a))<=(*((char *)b)))?1:0;
}
unsigned char CharCompare_G(void *a,void *b){
	return ((*((char *)a))>=(*((char *)b)))?1:0;
}
void CharSwap(void *a,void *b){
	char temp=*((char *)a);
	*((char *)a) = *((char *)b);
	*((char *)b) = temp;
}
void TestCharSort(){
	char *data = malloc(sizeof(char)*10);
	char test_buffer[64];
	unsigned int i,j,k;
	time_t test_time;
	for(i=0;i<10;i++){
		data[9-i] = '0'+i;
	}
	/*Randomize the input data*/
	time(&test_time);
	srand(test_time);
	for(i=0;i<100;i++){
		j=(rand())%10;
		k=(rand())%10;
		test_buffer[63]=data[j];
		data[j]=data[k];
		data[k]=test_buffer[63];
	}
	/*Print the buffer*/
	if(strncpy(test_buffer,data,10)!=test_buffer){
		fprintf(stderr,"SYSTEM_ISSUE:Copy into buffer failed\n");
	}else{
		test_buffer[10]='\0';
		fprintf(stdout,"%s\n",test_buffer);
	}
	RandQsort((void *)data,(void *)(data+9),1,
	CharSwap,CharCompare_L);
	for(i=0;i<10;i++){
		if(data[i]-('0'+i)){
			printf("Test Failed for Chars\n");
			printf("Expecting %d but found %d\n",i,
				((unsigned int)data[i]-'0'));
			exit(1);
		}
	}
	test_buffer[0]='\0';
	if(strncpy(test_buffer,data,10)!=test_buffer){
		fprintf(stderr,"FAILED_TEST: UNABLE TO COPY BUFFER\n");
		fprintf(stderr,"MAY_BE_SOME_MEMORY_CORRUPTION_DURING_SORT\n");
		exit(1);
	}else{
		fprintf(stdout,"%s\n",data);
	}
	printf("Test Passed For Chars....\n");
}
#include<math.h>
void TestFloatSort(){
	float *data = malloc(sizeof(float)*10);
	float temp;
	unsigned int i,j,k;
	time_t test_time;
	for(i=0;i<10;i++){
		if(i<5){
			data[9-i] = (float)sin(i);
		}else{
			data[9-i] = (float)cos(i);
		}
	}
	/*Randomize the input data*/
	time(&test_time);
	srand(test_time);
	for(i=0;i<100;i++){
		j=(rand())%10;
		k=(rand())%10;
		temp=data[j];
		data[j]=data[k];
		data[k]=temp;
	}
	/*Print the buffer*/
	for(i=0;i<10;i++){
		printf("%f ",data[i]);
	}
	printf("\n");
	printf("The # of elements %d\n",(&data[9]-&data[0])/4);
	RandQsort((void *)&data[0],(void *)&(data[9]),4,
	FloatSwap,FloatCompare);
	for(i=1;i<10;i++){
		if(!FloatCompare((void *)&data[i-1],(void *)&data[i])){
			printf("Test FAILED comparing %f , %f\n",
			data[i-1],data[i]);
			exit(1);
		}
	}
	for(i=0;i<10;i++){
		printf("%f ",data[i]);
	}
	printf("\n");
	printf("Test Passed For Floats....\n");
}
unsigned char IntCompare(void *a,void *b){
	return ((*(int *)a)<=(*(int *)b))?1:0;
}

void IntSwap(void *a,void *b){
	int temp;
	temp = *(int *)a;
	*(int *)a = *(int *)b;
	*(int *)b = temp;
}
void TestIntSort(){
	int *data = malloc(sizeof(int)*10);
	int temp;
	unsigned int i,j,k;
	time_t test_time;
	time(&test_time);
	srand(test_time);
	for(i=0;i<10;i++){
		data[i] = (rand())%10;
		printf("%d ",data[i]);
	}
	printf("\n");
	/*Print the buffer*/
	RandQsort((void *)&data[0],(void *)&(data[9]),4,
	IntSwap,IntCompare);
	for(i=1;i<10;i++){
		if(!IntCompare((void *)(&data[i-1]),(void *)(&data[i]))){
			fprintf(stderr,"Test for Integers failed\n");
			exit(1);
		}
	}
	for(i=0;i<10;i++){
		printf("%d ",data[i]);
	}
	printf("\n");
	printf("Test Passed For Integers....\n");
}

/*Test for floats*/
#if 0
int main(){
	TestCharSort();
	TestFloatSort();
	TestIntSort();
	exit(0);
}
#endif
/*This make sense only comparing normalized floats [0,1] */
inline unsigned char FloatCompare(void *a,void *b){
	register int a_int = (int)((*(float *)a)*100000);
	register int b_int = (int)((*(float *)b)*100000);
	return (a_int<=b_int)?1:0;
}

inline void FloatSwap(void *a,void *b){
	register float temp= *((float *)a);
	*((float *)a) = *((float *)b);
	*((float *)b) = temp;
}

/*
inline void EigenArraySwap(void *a,void *b){
	EigArray *a_eig = (EigArray *)a;
	EigArray *b_eig = (EigArray *)b;
	unsigned int graph = a_eig->graph;
	real *tmp = a_eig->eig;
	a_eig->eig = b_eig->eig;
	b_eig->eig = tmp;
	a_eig->graph = b_eig->graph;
	b_eig->graph = graph;
}


inline unsigned char EigenArrayCompare(void *a,void *b){
	EigArray *a_eig = (EigArray *)a;
	EigArray *b_eig = (EigArray *)b;
	unsigned int size=a_eig->size;
	register double cmp;
	unsigned int i=0;
	while(i < size){
		cmp = fabs((a_eig->eig)[i] - (b_eig->eig)[i]);
		if( cmp < 0.001 ){
			i++;
			continue;
		}
		return FloatCompare(&((a_eig->eig)[i]),&((b_eig->eig)[i]));;
	}
	return 1;
}
*/
