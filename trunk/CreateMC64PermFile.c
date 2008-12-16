/*
 * This creates a .perm file which is a list of integers
 * corresponding to the permutation we use this to test the 
 * code on the solaris platform because we dont have the library
 * for the MKL on solaris.
 *
 *
 * Vamsi Kundeti, May 19, 2008.
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include "mc64.h"
#include "MeasureTime.h"

#define MC64_FAILED 0
#define MC64_SUCCESS 1 

unsigned char ComputePermutation(int *colind, int *rowptr, double *val,int nnz,int n,int *perm){
	int job=5;
    int liw, ldw, num;
    int *iw, icntl[10], info[10];
    double *dw;

    liw = 5*n;
	iw = (int *) malloc(liw * sizeof(int)) ;
    ldw = 3*n + nnz;
	dw = (double *) malloc (ldw * sizeof(double));
	if(!iw || !ldw){
		fprintf(stderr,"MALLOC:FAILED\n");
		return MC64_FAILED;
	}
	Clock *mc64_clk = CreateClock();
	StartClock(mc64_clk);
	mc64id_(icntl);
	mc64ad_(&job,&n,&nnz,colind,rowptr,val,&num,perm,&liw,iw,&ldw,dw,icntl,info);
	StopClock(mc64_clk);
	if(info[0]){
		if(info[0]==1){
			fprintf(stderr,"Matrix is singular\n");
			fprintf(stderr,"RANK: %d\n",n-num);
		}else{
			fprintf(stderr,"info has %d \n",info[0]);
		}
	}
	printf("Elapsed Clock Ticks %d \n",GetClockTicks(mc64_clk));
	free(dw); free(iw);
	return MC64_SUCCESS;
}


void Usage(void){
	fprintf(stdout,"mc64 file.txt<row compressed form>");
}

int *perm = NULL;
int *mc64_colind = NULL;
int *mc64_rowptr = NULL;
double *mc64_val = NULL;

#define SIZE_INCREMENT 4096 
int main(int argc,char **argv){
	FILE *ptr = NULL;
	int *colind = NULL;
	int *rowptr = NULL;
	double *val = NULL;
	unsigned int count=0;
	unsigned int curr_size =0;
	int ival; char cval;double dval;
	int *tptr; int *expander;
	double *tptr_d; double *expander_d;
	FILE *permfile = NULL;
	char buf[1024];
	unsigned int ccount=0;
	unsigned int rcount=0;
	unsigned int nnz;

	printf("argc %d\n",argc);
	if(argc < 2){
		Usage();
		exit(1);
	}
	ptr = fopen(argv[1],"r");
	assert(ptr);
	sprintf(buf,"%s.perm",argv[1]);
	permfile = fopen(buf,"w");

	if(/*!strcmp(argv[1],"-cm")*/ 1){
		colind = (int *) malloc(sizeof(int)*SIZE_INCREMENT); 
		rowptr = (int *) malloc(sizeof(int)*SIZE_INCREMENT); 
		val = (double *) malloc(sizeof(double)*SIZE_INCREMENT);
		curr_size = SIZE_INCREMENT;
		expander = colind;
		/*Scan the colind and rowptr */
		while(fscanf(ptr,"%d%c",&ival,&cval)==2){
			count++;
			if(count > curr_size){
				tptr = (int *)malloc(sizeof(int)*(curr_size+SIZE_INCREMENT));
				if(memcpy(tptr,expander,curr_size*sizeof(int))!=tptr){
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
		printf("Done scanning nnz = %u\n",nnz);
#if 0
		for(count=0;count<ccount;count++){
			fprintf(remove_this,"%d ",colind[count]);
		}
		fprintf(remove_this,"\n");

		for(count=0;count<rcount;count++){
			fprintf(remove_this,"%d ",rowptr[count]);
		}
		fprintf(remove_this,"\n");

		for(count=0;count<nnz;count++){
			fprintf(remove_this,"%30.20e ",val[count]);
		}
		fprintf(remove_this,"\n");
		close(remove_this);
#endif
		perm = (int *) malloc(sizeof(int)*(ccount-1));
		assert(perm);
		mc64_rowptr = colind ; mc64_colind = rowptr; mc64_val = val;
		ComputePermutation(colind,rowptr,val,nnz,ccount-1,perm);
#ifdef PERFORMANCE_TEST
		exit(0);
#endif
		unsigned int i;
		for(i=0;i<ccount-1;i++){
			printf("%d ",perm[i]);
			fprintf(permfile,"%d ",perm[i]);
		}
		printf("\n");
		fprintf(permfile,"\n");

	}

	fclose(permfile);

	return 0;
}
