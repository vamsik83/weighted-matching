/*Reads a SparseGraph from a FILE
 *the file should have any whitespace as delimiter
 *and a newline to seperate each of the 3 entries
 *
 * vamsi kundeti, May 18, 2008
 ***/
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<assert.h>
#include "Bipartite.h"
#define SIZE_INCREMENT 4096 
SparseGraph* ReadSparseGraph(FILE *ptr){
	SparseGraph *G = (SparseGraph *)malloc(sizeof(SparseGraph)*1);
	unsigned int rcount=2;unsigned int nnz;
	node_t *expander; double *expander_d;unsigned int ccount=0;
	node_t ival; char cval; double dval;unsigned int count=0;
	node_t *tptr; double *tptr_d; unsigned int curr_size;
	node_t *colind = (node_t *) malloc(sizeof(node_t)*SIZE_INCREMENT); 
	node_t *rowptr = (node_t *) malloc(sizeof(node_t)*SIZE_INCREMENT); 
	double *val = (double *) malloc(sizeof(double)*SIZE_INCREMENT);
	curr_size = SIZE_INCREMENT;
	expander = colind;
	assert(G && colind && rowptr && val);
	/*Scan the colind and rowptr */
	while(fscanf(ptr,"%u%c",&ival,&cval)==2){
		count++;
		if(count > curr_size){
			tptr = (node_t *)malloc(sizeof(node_t)*(curr_size+SIZE_INCREMENT));
			if(memcpy(tptr,expander,curr_size*sizeof(node_t))!=tptr){
				fprintf(stderr,"SCAN_INPUT: Failed\n");
				exit(1);
			}
			free(expander);
			if(colind == expander){
				colind = tptr;
			}else{
				rowptr = tptr;
			}
			expander = tptr;
			curr_size += SIZE_INCREMENT;
		}
		expander[count-1] = ival;

		if(cval == '\n'){
			if(expander == colind){
				expander = rowptr;
				ccount = count;
				printf("COLINDEX SCANNED: %u \n",ccount);
				count = 0;
				curr_size = SIZE_INCREMENT;

			}else{
				rcount = count;
				printf("ROWINDEX SCANNED: %u \n",rcount);
				break;
			}
		}
	}

	assert(rcount > 0 && ccount > 0);
	/*Scan the nnz values*/
	expander_d = val; 
	count = 0;curr_size = SIZE_INCREMENT; 
	while(fscanf(ptr,"%lf%c",&dval,&cval)==2){
		count++;
		if(count > curr_size){
			tptr_d = (double *) malloc(sizeof(double)*(curr_size+SIZE_INCREMENT));
			if(memcpy(tptr_d,expander_d,sizeof(double)*curr_size)!=tptr_d){
				fprintf(stderr,"SCANNING: Failed during nnz scan\n");
				exit(1);
			}
			free(expander_d);
			expander_d = tptr_d;
			curr_size += SIZE_INCREMENT;
		}
		expander_d[count-1] = dval;
	}
	val = expander_d;
	nnz = count;
	G->order = ccount-1;
	/*Just reversed rowptr and colind*/
	G->nnz = val; G->colind = rowptr; G->rowptr = colind;
	G->nnz_size = count;
	printf("Done scanning nnz = %u\n",nnz);
	return G;
}
