#ifndef __BI_PARTITE_H
#define __BI_PARTITE_H
#define SIZE_OF_BYTE_IN_BITS 8
#include<stdio.h>
typedef unsigned int node_t;
/*A Match representation (i,m[i]) 
 */
typedef struct _match_ {
	node_t size;
	node_t *m;
}Match_t;
/*A row compressed format for the Matrix/graph */
typedef struct _sparse_graph_{
	double *nnz;
	node_t *colind;
	node_t *rowptr;
	node_t order; /*Order of the sparse graph*/
	node_t nnz_size; /*no.of nnz values*/
} SparseGraph;
typedef struct _bt_array_ {
	node_t size;
	char *ba;
}BitArray_t;
typedef unsigned int match_size_t;
BitArray_t* CreateBitArray(unsigned int);
inline void SetBit(BitArray_t*,unsigned int);
inline unsigned char CheckBit(BitArray_t*,unsigned int);
inline void ResetAllBits(BitArray_t *);
SparseGraph* ReadSparseGraph(FILE *);
node_t SimplePickMin(BitArray_t *bit_heap,double *dist,node_t n);
inline void UnsetBit(BitArray_t *b,unsigned int bitno);
void FreeBitArray(BitArray_t *b);
#endif
