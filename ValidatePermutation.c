/*
 * This program validates the permutation and reports 
 * if there are any differences.
 *
 * vamsik@engr.uconn.edu 11/25/2008
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<math.h>
#include "Bipartite.h"

long long int COMPLIMENT_CONSTANT=((long long int)0x8000000000000000LL);
char CompareDoubles(double A,double B){
	 long long int a64int = *((long long int *)&A);
	 long long int b64int= *((long long int *)&B);
	 long long int diff;

	 if(A==B){
		 return 1;
	 }
	 if(a64int < 0){
		 a64int = COMPLIMENT_CONSTANT - a64int; 
	 }
	 if(b64int < 0){
		 b64int = COMPLIMENT_CONSTANT - b64int;
	 }
#ifndef WIN32
	 diff = llabs(a64int-b64int);
#else
	 diff = a64int-b64int;
	 diff = (diff < 0)?-diff:diff;
#endif
	 if(diff <= 1){
		 return 1;
	 }
	 return 0;
}
/****************************************/

void Usage(void){
	fprintf(stderr,"verify_perm {file1.perm} {file2.perm} {mat.rcf}\n");
	return;
}

int main(int argc,char **argv){
	SparseGraph *G = NULL;
	node_t *rowptr,*colind;
	node_t *p1,*p2;
	FILE *ptr = NULL; FILE *perm1 = NULL; 
	FILE *perm2 = NULL;
	double *val;
	char filenamebuf[256];
	
	if(argc < 4){
		Usage();
		exit(1);
	}
	perm1 = fopen(argv[1],"r");
	perm2 = fopen(argv[2],"r");
	ptr = fopen(argv[3],"r");
	assert(perm1 && perm2 && ptr);

	G = ReadSparseGraph(ptr);
	/*Read the permuation and print the corresponding values.*/
	p1 = (node_t *) malloc(sizeof(node_t)*(G->order));
	p2 = (node_t *) malloc(sizeof(node_t)*(G->order));
	assert(p1 && p2);
	unsigned int i=0;
	unsigned int i1,i2,j,k;
	FILE *diff_file1[2]; /*print out the differing entries.*/
	FILE **diff_file = diff_file1;
	node_t n1,n2;
	diff_file--;

	i=0;
	while(fscanf(perm1,"%lu",&n1)>0 && fscanf(perm2,"%lu",&n2)>0){
		p1[i] = n1;
		p2[i++] = n2; 
	}
	assert(i == G->order);
	for(i=1;i<=2;i++){
		if(strlen(argv[i]) < 200){
			sprintf(filenamebuf,"%s.diag.diff",argv[i]);
		}else{
			sprintf(filenamebuf,"%199s.diag.diff",argv[i]);
		}
		diff_file[i] = fopen(filenamebuf,"w");
		if(!(diff_file[i])){
			perror("FAILED:");
		}
		assert(diff_file[i]);
	}

	val = G->nnz; val--;
	rowptr = G->rowptr; rowptr--;
	colind = G->colind; colind--;

	/*Print Out the diagonal Entries.*/
	unsigned pdiff_count=0;
	for(i=0;i<G->order;i++){
		if(p1[i] != p2[i]){
			i1 = p1[i];
			i2 = p2[i];
			j = i+1;
			pdiff_count++;
			assert(i1 <= G->order);

			for(k=rowptr[i1];k<rowptr[i1+1];k++){
				if(colind[k] == j){
					fprintf(diff_file[1],"%e\n",val[k]);
					break;
				}
			}

			assert(i2 <= G->order);
			for(k=rowptr[i2];k<rowptr[i2+1];k++){
				if(colind[k] == j){
					fprintf(diff_file[2],"%e\n",val[k]);
					break;
				}
			}
		}
	}
	printf("The input permutations differ at %lu places \n",pdiff_count);
	fclose(diff_file[1]);
	fclose(diff_file[2]);

	/*Sort Both the files*/
	char cmdbuffer[1024];
	for(i=1;i<=2;i++){
		if(strlen(argv[i]) < 200){
			sprintf(filenamebuf,"%s.diag.diff",argv[i]);
		}else{
			sprintf(filenamebuf,"%199s.diag.diff",argv[i]);
		}
		sprintf(cmdbuffer,"sort -n %s > %s.sorted",filenamebuf,filenamebuf);
		if(system(cmdbuffer) < 0){
			fprintf(stderr,"Failed to invoke UNIX sort utility on the system\n");
			fprintf(stderr,"Make sure sort is in the PATH\n");
			exit(1);
		}
	}
#define NO_DIFF_COMPARE
#ifdef NO_DIFF_COMPARE /*Sort Compare*/
	for(i=1;i<=2;i++){
		if(strlen(argv[i]) < 200){
			sprintf(filenamebuf,"%s.diag.diff.sorted",argv[i]);
		}else{
			sprintf(filenamebuf,"%199s.diag.diff.sorted",argv[i]);
		}
		diff_file[i] = fopen(filenamebuf,"r");
		if(!diff_file[i]){
			fprintf(stderr,"Unable to open sorted file %s \n", filenamebuf);
			exit(1);
		}
	}

	/*Read and compare the floats*/
	double perm1_value; double val1=0.0;
	double perm2_value; double val2=0.0;
	long double prod_perm1=1.0; long double prod_perm2=1.0;
	unsigned int fdiff_count = 0;
	while(fscanf(diff_file[1],"%lf",&perm1_value)==1 &&
		fscanf(diff_file[2],"%lf",&perm2_value)==1){
		if(!CompareDoubles(perm1_value,perm2_value)){
			val1 += fabs(perm1_value);
			val2 += fabs(perm2_value);
			prod_perm1 *= fabs(perm1_value);
			prod_perm2 *= fabs(perm2_value);
			fdiff_count++;
		}
	}

	printf("======================\n");
	printf("Accuracy differences = %ld \n",fdiff_count);
	printf("\n");
	printf("PERM1 sum along diagonal = %E \n",val1);
	printf("PERM2 sum along diagonal = %E \n",val2);
	printf("DIFFERENCE is %E \n",fabs(val1-val2));
	printf("\n");
	printf("PERM1 product along diagonal = %E \n",perm1_value);
	printf("PERM2 product along diagonal = %E \n",perm2_value);
	printf("============\n");
	
#endif


#ifndef NO_DIFF_COMPARE
	if(strlen(argv[1]) < 200 && strlen(argv[2]) < 200){
		sprintf(cmdbuffer,"diff %s.diag.diff.sorted %s.diag.diff.sorted > %s.diff",argv[1],
			argv[2],argv[3]);
		if(system(cmdbuffer)<0){
			fprintf(stderr,"FATAL: Unable to execute diff on the system (or) Failed creating a temporary file in the directory\n");
			exit(1);
		}
		sprintf(cmdbuffer,"%s.diff",argv[3]);
		diff_file[1] = fopen(cmdbuffer,"r");
		if(!(diff_file[1])){
			fprintf(stderr,"FATAL: Unable to open the diff file");
			exit(1);
		}
		/*Multiply all the differences.*/
		fprintf(stdout,"Computing the product and sum of the differences\n");
		double perm1_value=0.0;
		double perm2_value=0.0;
		double scan_val;
		unsigned int perm_diff_count=0;

		/**Diff format %lu%c%lu%c%lu**/
		unsigned int lineno;
		char op;
		while(fscanf(diff_file[1],"%c",&op) > 0){
			if(op == '>'){
				fscanf(diff_file[1],"%lf",&scan_val);
				printf("> %e \n",scan_val);
				perm1_value += fabs(scan_val);
			}else if(op == '<'){
				fscanf(diff_file[1],"%lf",&scan_val);
				printf("< %e \n",scan_val);
				perm2_value += fabs(scan_val);
			}else{
				/*skip the line*/
				fscanf(diff_file[1],"%*[^\n]\n");
			}
		}
		printf("PERMUTAION1 '>' is %E \n",perm1_value);
		printf("PERMUTATION2 '<' is %E \n",perm2_value);

	}else{
		fprintf(stderr,"UNABLE DO THE DIFF FILE NAMES TOO LONG\n");
		exit(1);
	}
#endif


}
