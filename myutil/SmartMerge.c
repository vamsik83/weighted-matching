#include<stdio.h>
#include<stdlib.h>
#include "myutil.h"
#define D_SIZE 5
unsigned int MyCeil(unsigned int a,unsigned int b){
	return (((a/b)*b)<(a*b))?(a/b)+1:(a/b);
}
int *intarray = NULL;
int main(int argc,char **argv){
	int scanint;
	int *newptr=NULL;
	unsigned int scansize=0;
	unsigned long currentsize;
	unsigned int min;
	unsigned int mcmpcount=0;
	unsigned int runs=0,finishedruns=0;
	unsigned int *mindex = NULL;
	intarray = (int *)malloc(sizeof(int)*64);
	currentsize=64;
	while(scanf("%d",&scanint)==1){
		scansize++;
		if(scansize > currentsize){
			newptr = (int *)malloc(sizeof(int)*(2*currentsize));
			currentsize *=2;
			assert(memcpy(newptr,intarray,scansize-1)==newptr);
			free(intarray);
			intarray = newptr;
		}
		intarray[scansize-1] = scanint;
	}

	/*STEP1: Divide into n/d parts*/
	for(i=0;i<scansize;i+=D_SIZE){
		min = (((i+D_SIZE-1)>=n)?n-1:(i+D_SIZE-1));
		RandQSort((void *)&intarray[i],(void *)&intarray[min],
			sizeof(int),IntSwap,IntCompare);
		runs++;
	}
	mindex = malloc(sizeof(int *)*runs); assert(mindex);
	for(i=0;i<runs;i++){
		mindex[i]=0;
	}
	finishedruns = runs;
	/*STEP2: Smart Merge*/
	while(finishedruns){
		scanint = (1<<31)-1;
		for(i=0;i<runs;i++){
			if(mindex[i] < scanint){
				mindex[i] 
			}
		}
	}
}
