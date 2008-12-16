/*
 * May 20,2008. Vamsi Kundeti.
 * Implementing unweighted and weighted bipartite matching algorithms.
 */
#define BINARY_HEAP 1
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include "Heap.h"
#include "Bipartite.h"
#define MAX_DOUBLE_VALUE 1.7976931348622e+308
// MAX_DOUBLE_VALUE
 
#define COMPLIMENT_CONSTANT ((long long int)0x8000000000000000)
/*Equality of double precision floating point numbers*/
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
	 diff = llabs(a64int-b64int);
	 if(diff <= 50000){
		 return 1;
	 }
	 return 0;
}
/*This implements the MC21 perfect matching*/
match_size_t FindPerfectMatch(Match_t *M,SparseGraph *G){
	unsigned int match_size=0;
	assert(G && M);
	node_t n = G->order;
	node_t *colind=G->colind;colind--;
	node_t *rowptr=G->rowptr;rowptr--;
	node_t *m = M->m;m--;
	BitArray_t *col_marker = CreateBitArray(n);
	BitArray_t *matched_row = CreateBitArray(n);
	node_t *p = (node_t *) malloc(sizeof(node_t)*n);p--;
	node_t *m_inv = (node_t *) malloc(sizeof(node_t)*n);m_inv--;
	node_t i,j,k,i1,jend;node_t m_inv_prev;char aug_extend=0;

	match_size=0;
	for(i=1;i<=n;i++){
		m_inv[i]=0;
	}
	for(j=1;j<=n;j++){
		if(m[j]){
			m_inv[m[j]]=j;
			match_size++;
		}
	}
	for(i=1;i<=n;i++){
		/*Augmenting path at any unmatched node*/
		if(m_inv[i]){
			continue;
		}
		i1 = i; p[i1]=0; jend=0;
		ResetAllBits(col_marker);
		while(i1 && !jend){
			for(k=0;k<(rowptr[i1+1]-rowptr[i1]);k++){
				j = colind[rowptr[i1]+k];
				if(!m[j]){
					jend=j;
					break;
				}
			}
			if(jend){
				/*Found an unmatched node*/
				break;
			}
			aug_extend=0;
			for(k=0;k<(rowptr[i1+1]-rowptr[i1]) && !jend;k++){
				j = colind[rowptr[i1]+k];
				if(!CheckBit(col_marker,j) && m[j]){
					p[m[j]]=i1;
					m_inv[m[j]]=j;
					SetBit(col_marker,j);
					i1 = m[j];
					aug_extend = 1;
					break;
				}
			}
			if(!aug_extend){
				/*Unable to find a unmarked matched node*/
				i1 = p[i1];
			}
		}
		if(i1){
			/*Augmenting path is found so augment*/
			j = jend; 
			printf("Augmenting the path {");
			while(i1){
				m_inv_prev = m_inv[i1];
				m[j] = i1; m_inv[i1] = j;
				printf("(%u,%u)",i1,j);
				j = m_inv_prev;
				i1 = p[i1];
			}
			printf("}\n");
			match_size++;
			printf("Match Size: %u\n",match_size);
		}else{
			/*the matching is maximum*/
			break;
		}
	}
	FreeBitArray(col_marker); FreeBitArray(matched_row);
	free(++m_inv); free(++p);
	printf("Done freeing\n");
	return match_size;
}
void ComputeInitialExtremeMatch(double *u,double *v,double *C1,double *C,
	node_t *m,node_t *m_inv,node_t* colind,node_t* rowptr,node_t n,double *dist,
	double *clabel){
	node_t j,i,k,i1,k1;
	double vmin;
	double C1k;
	/*Compute u[j]*/
	for(j=1;j<=n;j++){
		u[j] = MAX_DOUBLE_VALUE;
		dist[j] = MAX_DOUBLE_VALUE;
		m[j]=0;m_inv[j]=0;
	}
	for(i=1;i<=n;i++){
		for(k=rowptr[i];k<rowptr[i+1];k++){
			if(C[k]<u[colind[k]]){
				u[colind[k]] = C[k];
			}
		}
	}
	/*Compute v[i]*/
	for(i=1;i<=n;i++){
		v[i] = MAX_DOUBLE_VALUE;
		for(k=rowptr[i];k<rowptr[i+1];k++){
			vmin = (C[k]-u[colind[k]]);
			if(vmin < v[i]){
				v[i] = vmin;
			}
		}
	}
	/*Update Cost and match.*/
	for(i=1;i<=n;i++){
		for(k=rowptr[i];k<rowptr[i+1];k++){
			C1[k] = C[k]-v[i]-u[colind[k]];
			if((fabs(C1[k]-0.0) <= 1.0e-14) && (!m[colind[k]] && !m_inv[i])){
				m[colind[k]] = i;
				m_inv[i] = colind[k];
				clabel[i] = C[k];
			}
		}
	}

	/****************/
	/*1-Step Augmentation*/
	for(i=1;i<=n;i++){
		if(!m_inv[i]){ /*Unmatched Row*/
			for(k=rowptr[i];k<rowptr[i+1] && !(m_inv[i]);k++){
				C1k = C[k]-v[i]-u[colind[k]];
				if(fabs(C1k-0.0) <= 1.0e-14){
					assert(m[colind[k]]);
					i1 = m[colind[k]];
					assert(m_inv[i1] == colind[k]);
					/*See if we can find any C1(i1,j1) == 0*/
					for(k1=rowptr[i1];k1<rowptr[i1+1];k1++){
						C1k = C[k1] - v[i1]-u[colind[k1]];
						if( fabs(C1k-0.0) <= 1.0e-14 && !(m[colind[k1]])){
							/*augment the match.*/
							m[colind[k]] = i;
							m_inv[i] = colind[k];
							clabel[i] = C[k];
							m[colind[k1]] = i1;
							m_inv[i1] = colind[k1];
							clabel[i1] = C[k1];
							break;
						}
					}
				}

			}
		}
	}





}
#ifdef BINARY_HEAP
/*This is the dist_base, which helps in identifying the
 *index of an address in the heap.*/
static unsigned long dist_base=0;
#endif
/*MC64: Weighted Bipartite matching, MAKE SURE that M is *a 'extreme' 
 *matching w.r.t nnz values in G->nnz, if you are not passing an empty
 *match.
 */
match_size_t WeightedMatching(Match_t *M,SparseGraph *G){
	double *C = G->nnz;C--;node_t *m = M->m;m--;
	node_t n = G->order;node_t i,j,i1,jend,k,m_inv_prev;
	double curr_shortest_path=0.0;double curr_aug_path=MAX_DOUBLE_VALUE;
	double *C1 = (double *)malloc(sizeof(double)*(G->nnz_size));C1--;
	double *dist = (double *)malloc(sizeof(double)*n);dist--;
	double *u = (double *)malloc(sizeof(double)*n);u--;
	double *v = (double *)malloc(sizeof(double)*n);v--;
	double force_mem_write[3];
	node_t *m_inv = (node_t *)malloc(sizeof(node_t)*n);m_inv--;
	node_t *rowptr = G->rowptr; rowptr--;
	node_t *colind = G->colind; colind--;
	node_t *p = (node_t *) malloc(sizeof(node_t)*n);p--;
	unsigned int match_size=0;double dist1; node_t itrace;
	BitArray_t *col_marker = CreateBitArray(n);
	BitArray_t *heap_marker = CreateBitArray(n);
	double *clabel = (double *)malloc(sizeof(double)*n);clabel--;
	node_t *update_stack = (node_t *)malloc(sizeof(node_t)*n); update_stack--;
	node_t update_stack_index;
	double *aug_label = (double *)malloc(sizeof(double)*n);aug_label--;
#if BINARY_HEAP
	Heap *bin_heap = NewBinaryHeap(DoubleCompare,n,GetDistKeyID);  
	double *dist_ptr = NULL;
#endif
	assert(C1 && dist && u && v && p);


	ComputeInitialExtremeMatch(u,v,C1,C,m,m_inv,colind,rowptr,n,dist,clabel);
	match_size=0;
	for(i=1;i<=n;i++){
		if(m_inv[i]){
			match_size++;
			continue;
		}
		/*
		 *Aim is to find a value for jend such that the path
		 *from i-->jend is the shortest
		 */
		i1 = i; p[i1] = 0; jend=0; itrace=i;
		ResetAllBits(col_marker);
		ResetAllBits(heap_marker);
		update_stack_index=0;
#if BINARY_HEAP
		bin_heap->n = 0;
		dist_base = (unsigned long)&(dist[1]);
#endif
		curr_shortest_path=(double)0.0;curr_aug_path=MAX_DOUBLE_VALUE;
		while(1){
			for(k=0;k<(rowptr[i1+1]-rowptr[i1]);k++){
				j = colind[rowptr[i1]+k];
				if(CheckBit(col_marker,j)){
					continue;
				}
				force_mem_write[1] = C[rowptr[i1]+k]-(v[i1]+u[j]);
				dist1 = curr_shortest_path + force_mem_write[1];
				/*Prune any dist1's > curr_aug_path, since
				 *all the costs>0 
				 */
				if(*((long long int *)&dist1) < *((long long int *)&curr_aug_path)){
					if(!m[j]){
						/*we need itrace because, the last i1 which
						 *we explore may not actually give the shortest 
						 *augmenting path.*/
						jend = j; itrace = i1;
						curr_aug_path = dist1;
						aug_label[j] = C[rowptr[i1]+k];
					}else if(*((long long int *)&dist1) < *((long long int *)&(dist[j]))){ /*Update the dist*/
						dist[j] = dist1; p[m[j]] = i1;
						aug_label[j] = C[rowptr[i1]+k];
#if SIMPLE_HEAP
						SetBit(heap_marker,j);
#elif BINARY_HEAP
						if(CheckBit(heap_marker,j)){
							DecreaseKey(bin_heap,j);
						}else{
							InsertHeap(bin_heap,&(dist[j]));
							SetBit(heap_marker,j);
						}
#endif
					}
				}
			}
#if 0
			if(/*!(curr_aug_path>curr_shortest_path)*/(curr_aug_path<curr_shortest_path) || 
				CompareDoubles(curr_aug_path,curr_shortest_path)){
				break;
			}
#endif

			if(*((long long int *)&curr_aug_path) <= *((long long int *)&curr_shortest_path)){ 
				break;
			}

			/*We now have a heap of matched cols, so pick the min*/
#ifdef SIMPLE_HEAP
			j = SimplePickMin(heap_marker,dist,n);
			if(j){
				curr_shortest_path = dist[j]; 
				UnsetBit(heap_marker,j); 
#elif BINARY_HEAP
			dist_ptr = (double *) HeapDelete(bin_heap);
			if(dist_ptr){
				assert((unsigned long)dist_ptr >= (unsigned long)&dist[1]);
				j = ((((unsigned long)dist_ptr -
					(unsigned long)&dist[1]))/sizeof(double))+1;
				assert(j>=1 && j<=n);
				curr_shortest_path = dist[j]; 
				UnsetBit(heap_marker,j); 
#endif
				SetBit(col_marker,j);
				update_stack[++update_stack_index] = j;
				i1 = m[j];
			}else{
				break;
			}
		}
		if(jend){ /*We found a shortest augmenting path*/
			unsigned long **harray = bin_heap->heapArray;
			while(update_stack_index){
				j=update_stack[update_stack_index--];
				u[j] = (u[j]+dist[j])-curr_aug_path;
				/*Reset the dist values*/
				if(m[j]){
					i1 = m[j];
					v[i1] = clabel[i1] - u[j];
				}
				dist[j] = MAX_DOUBLE_VALUE;
				if(bin_heap->n){
					*((double *)harray[bin_heap->n]) = MAX_DOUBLE_VALUE;
					bin_heap->n -= 1 ;
				}
			}
			j=jend;
			node_t itrace_prev;
			//printf("Shortest augmenting Path {");
			while(itrace){
				m_inv_prev = m_inv[itrace];
				m[j] = itrace; m_inv[itrace]=j;
				clabel[itrace] = aug_label[j];
				v[itrace] = clabel[itrace] - u[j];
				//printf("(%u,%u)",itrace,j);
				j=m_inv_prev;
				itrace_prev = itrace;
				itrace = p[itrace];
				if(itrace){
				//	printf("(%u,%u)",itrace_prev,m_inv_prev);
				}
				if(bin_heap->n){
					*((double *)harray[bin_heap->n]) = MAX_DOUBLE_VALUE;
					bin_heap->n -= 1;
				}
			}
			while(bin_heap->n){
				*((double *)harray[bin_heap->n]) = MAX_DOUBLE_VALUE;
				bin_heap->n -= 1;
			}
			match_size++;
			//printf("}\n");
			/*Update the cost with new match m*/

#if 0
			for(i1=1;i1<=n;i1++){
				if(!m_inv[i1]) continue;
				j = m_inv[i1];
				for(k=0;k<rowptr[i1+1]-rowptr[i1];k++){
					if(colind[rowptr[i1]+k] == j){
						if(!CompareDoubles(C[rowptr[i1]+k],clabel[i1])){
							printf("Variation for %d\n",i1);
							exit(1);
						}
						v[i1] = C[rowptr[i1]+k] - u[j];
					}
				}
			}

			/*Update the cost*/
			for(i1=1;i1<=n;i1++){
				for(k=0;k<(rowptr[i1+1]-rowptr[i1]);k++){
					j = colind[rowptr[i1]+k];
					C1[rowptr[i1]+k] = C[rowptr[i1]+k]-(u[j]+v[i1]);
				}
				/*The index should be j rather than i1 but just 
				 *avoiding another loop*/
			//	dist[i1] = MAX_DOUBLE_VALUE;
			}
#endif
		}
	}
	free(++C1); free(++dist); free(++u);
	free(++v); free(++m_inv); free(++p);
	FreeBitArray(col_marker);
	FreeBitArray(heap_marker);
#ifdef BINARY_HEAP	
	FreeHeap(bin_heap);
#endif

	return match_size;
}
/*O(n) time picking the maximum from the heap_marker */
node_t SimplePickMin(BitArray_t *bit_heap,double *dist,node_t n){
	node_t min_j=0;node_t j; 
	double curr_min = MAX_DOUBLE_VALUE; 
	for(j=1;j<=n;j++){
		if(CheckBit(bit_heap,j) && dist[j] < curr_min){
			min_j = j;
			curr_min = dist[j];
		}
	}
	return min_j;
}
#ifdef BINARY_HEAP 
inline keyid_t GetDistKeyID(void *dist_ptr){ assert((unsigned long)dist_ptr >= dist_base);
	return (((((unsigned long)dist_ptr-dist_base))/sizeof(double))+1);
}
#endif

BitArray_t* CreateBitArray(unsigned int size){
	div_t d = div(size,SIZE_OF_BYTE_IN_BITS);
	BitArray_t *bits = (BitArray_t *)malloc(sizeof(BitArray_t)*1);
	assert(bits);
	bits->size = (d.rem > 0)?(d.quot+1):d.quot;
	bits->ba = (char *)malloc(sizeof(char)*(bits->size));
	assert(bits->ba);
	memset(bits->ba,'\0',bits->size);
	return bits;
}
inline void SetBit(BitArray_t *b,unsigned int bitno){
	div_t d;
	assert(bitno>=1 && bitno<=(b->size*SIZE_OF_BYTE_IN_BITS));
	d = div((bitno-1),SIZE_OF_BYTE_IN_BITS);
	(b->ba)[d.quot] = (char)((b->ba)[d.quot]|(1<<(d.rem)));
}
inline void UnsetBit(BitArray_t *b,unsigned int bitno){
	div_t d;
	assert(bitno>=1 && bitno<=(b->size*SIZE_OF_BYTE_IN_BITS));
	d = div((bitno-1),SIZE_OF_BYTE_IN_BITS);
	(b->ba)[d.quot] = (char)((b->ba)[d.quot]^(1<<(d.rem)));
}
inline unsigned char CheckBit(BitArray_t* b,unsigned int bitno){
	div_t d;
	assert(bitno>=1 && bitno<=(b->size*SIZE_OF_BYTE_IN_BITS));
	d = div(bitno-1,SIZE_OF_BYTE_IN_BITS);
	return (char)((b->ba)[d.quot] & (1<<(d.rem)));
}
inline void ResetAllBits(BitArray_t *b){
	memset(b->ba,'\0',b->size);
}
void FreeBitArray(BitArray_t *b){
	free(b->ba);
	free(b);
}
/*node_t with value 0 is considered an empty node*/
Match_t * CreateEmptyMatch(unsigned int n){
	unsigned int i;
	Match_t *ma = (Match_t *)malloc(sizeof(Match_t)*1);
	ma->m = (node_t *) malloc(sizeof(node_t)*n);
	for(i=0;i<n;i++){
		ma->m[i] = 0;
	}
	return ma;
}
void LogTransform(SparseGraph *G){
	node_t *rowptr = G->rowptr; rowptr--;
	node_t *colind = G->colind; colind--;
	double *val = G->nnz;val--;
	node_t n = G->order; node_t k;
	node_t nnz_size = G->nnz_size;
	double *max_c = (double *)malloc(sizeof(double)*n);max_c--;
	for(k=1;k<=n;k++){
		/*Find the maximum in the column*/
		max_c[k] = (double)0.0;
	}
	for(k=1;k<=nnz_size;k++){
		val[k] = fabs(val[k]);
		if(val[k] > max_c[colind[k]]){
			max_c[colind[k]] = val[k];
		}
	}
#if 0
	for(k=1;k<=n;k++){
		printf("max in col %u is %e \n",k,max_c[k]);
	}
#endif
	for(k=1;k<=nnz_size;k++){
		if(fabs(val[k]-0.0)<=1.0e-14){
			val[k] = MAX_DOUBLE_VALUE;
		}else{
			if(fabs(max_c[colind[k]]-0.0)<=1.0e-14){
				val[k] = MAX_DOUBLE_VALUE;//MAX_DOUBLE_VALUE/n - (log(val[k])/M_LN10);
			}else{
				val[k] = (log(max_c[colind[k]]) - log(val[k]))/M_LN10;
			}
		}
		/*take care of -0.0*/
		val[k] = fabs(val[k]);
		assert(val[k]>=0.0);
	}
	free(++max_c);
}

#ifndef NO_UNIT_TEST 
int main(int argc,char** argv){
	FILE *ptr = NULL; unsigned int i;
	SparseGraph *G = NULL;
	Match_t *m = NULL;
	node_t *rowptr;node_t *colind; 
	double *val,*val1;
	unsigned int i1,i2,j;
	unsigned int k;
	if(argc<2){
		fprintf(stderr,"./a.out <sparse_file>");
		exit(1);
	}
	ptr = fopen(argv[1],"r");
	assert(ptr);
	G = ReadSparseGraph(ptr);
	m = CreateEmptyMatch(G->order);
	if(argc > 2 && argv[2]){
		FILE *mfile = fopen(argv[2],"r");
		node_t count=0;
		node_t mid;
		node_t *m1 = m->m; m1--;
		while(fscanf(mfile,"%u",&mid)==1){
			count++;
			m1[count] = mid;
		}
	}
	rowptr = G->rowptr;rowptr--; colind = G->colind;colind--;
	val = (double *)malloc(sizeof(double)*(G->nnz_size));
	memcpy(val,G->nnz,sizeof(double)*(G->nnz_size));
	val--;
	LogTransform(G);
	val1 = G->nnz; val1--;
	WeightedMatching(m,G);
#ifdef STANDALONE_MODE
	exit(0);
#endif
	/*Now call the MC64*/
	MC64Driver(argc,argv);

	printf("Verifying the permutation\n");
	char failed=0;
	double unmatched_product_i1=1.0;
	double unmatched_product_i2=1.0;
	double unmatched_sum_i1=0.0;
	double unmatched_sum_i2=0.0;
	/*Write out the diagonal elements*/
	char filebuffer[1024];
	sprintf(filebuffer,"%s.mc64.diag",argv[1]);
	FILE *diag1 = fopen(filebuffer,"w");
	sprintf(filebuffer,"%s.anst.diag",argv[1]);
	FILE *diag2 = fopen(filebuffer,"w");
	assert(diag1 && diag2);

	for(i=0;i<G->order;i++){
	//	printf("%d %d\n",(i+1),(m->m)[i]);
		printf("%u(%d) ",(m->m)[i],perm[i]);
		if(perm[i]!=(int)(m->m)[i]){
			failed=1;
		}
		/*Print the value of C[j] i1 & i2*/
		j = (int)i+1;
		i1 = (int)(m->m)[i]; i2 = perm[i];

		if(!i1){
			printf("Missing match\n");
		}else{

		for(k=0;k<rowptr[i1+1]-rowptr[i1];k++){
			if(colind[rowptr[i1]+k] == j){
				if(perm[i] != (int) (m->m)[i]){
					printf("< %e >",val[rowptr[i1]+k]);
				}
				unmatched_product_i1 += fabs(val[rowptr[i1]+k]);
				unmatched_sum_i1 += val1[rowptr[i1]+k];
				fprintf(diag2,"%.10lf\n",fabs(val1[rowptr[i1]+k]));
				
			}
		}
		}

		for(k=0;k<rowptr[i2+1]-rowptr[i2];k++){
			if(colind[rowptr[i2]+k] == j){
				if(perm[i] != (int) (m->m)[i]){
					printf("< %e >",val[rowptr[i2]+k]);
				}
				unmatched_product_i2 += fabs(val[rowptr[i2]+k]);
				unmatched_sum_i2 += val1[rowptr[i2]+k];
				fprintf(diag1,"%.10lf\n",fabs(val1[rowptr[i2]+k]));
				
			}
		}
	}
	fclose(diag1);fclose(diag2);
	if(failed){
		if(CompareDoubles(unmatched_product_i1,unmatched_product_i2)){
			printf("MULTIPLE SOLUTIONS the final cost matches\n");
		}else{
			printf("FAILED\n");
			printf("\n pd1=%e pd2=%e \n",unmatched_product_i1,unmatched_product_i2);
			printf("sum1=%e sum2=%e \n",unmatched_sum_i1,unmatched_sum_i2);
			exit(1);
		}
	}
	printf("\n\nSUCCESS\n");
	printf("\n pd1=%e pd2=%e \n",unmatched_product_i1,unmatched_product_i2);
	printf("sum1=%e sum2=%e \n",unmatched_sum_i1,unmatched_sum_i2);
	printf("\n");
	
	return 0;
}
#endif
