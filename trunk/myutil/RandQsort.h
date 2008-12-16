#ifndef __RAND_QUICK_SORT_H
#define __RAND_QUICK_SORT_H
#include<stdio.h>
#include<malloc.h>
#include<assert.h>
typedef void (*void_void_fptr)(void *,void *);
typedef unsigned char (*bool_void_fptr)(void *,void *);
void RandQsort(void *data,void *end,unsigned int size, 
void_void_fptr swp_fptr,bool_void_fptr cmp_fptr_l);
/*Some inbuilt predefined routines*/
extern inline unsigned char FloatCompare(void *,void *);
extern inline void FloatSwap(void *,void *);
extern unsigned char CharCompare_L(void *a,void *b);
extern void CharSwap(void *a,void *b);
unsigned char CharCompare_G(void *a,void *b);
unsigned char CharCompare_L(void *a,void *b);
unsigned char IntCompare(void *a,void *b);

void IntSwap(void *a,void *b);
#define SortFloats(a,b) do{\
	RandQsort((void *)a,(void *)b,4,FloatSwap,FloatCompare);\
}while(0);

#define SortChars(a,b) do{\
	RandQsort((void *)a,(void *)b,1,CharSwap,CharCompare_L);\
}while(0);

#if 0
typedef struct EigArray{
	real *eig;
/*Compressed bit-wise representation*/
	unsigned int graph;
	unsigned int size;
} EigArray;

inline void EigenArraySwap(void *a,void *b);
inline unsigned char EigenArrayCompare(void *a,void *b);
#endif

#endif
