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
// HUGE_VAL

/*****Equality of double precision floating point numbers*/
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
	 diff = llabs(a64int-b64int);
	 if(diff <= 100){
		 return 1;
	 }
	 return 0;
}
/****************************************/
/*****Maximum values of the Types*******/
template<class Type>
Type GetMaxTypeValue(void);

template<class Type>
Type GetMaxTypeValue(void){
	fprintf(stderr,"GetMaxTypeValue undefined for this Type\n");
	assert(0);
	return (Type)0;
}

template<>
double GetMaxTypeValue(void){
	return HUGE_VAL; 
}
/*********************************/
/***Type Specific Absolute Values*/
template<class Type>
Type GenericFabs(Type a){
	assert(0);
	return (Type)0;
}
template<>
double GenericFabs(double a){
	return fabs(a);
}
template<>
int GenericFabs(int a){
	return abs(a);
}
/*******************************************/
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
/*******************************************/
/***Initial Extreme Matching Function*******/
template <class ValueType,class Indices>
void ComputeInitialExtremeMatch(ValueType *u,ValueType *v,ValueType *C1,ValueType *C,
	Indices *m,Indices *m_inv,Indices* colind,Indices* rowptr,Indices n,ValueType *dist){
	Indices j,i,k;
	ValueType vmin;
	/*Compute u[j]*/
	for(j=1;j<=n;j++){
		u[j] = GetMaxTypeValue<ValueType>(); 
		dist[j] = u[j]; 
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
		v[i] = GetMaxTypeValue<ValueType>();
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
			if((fabs(C1[k]-0.0) <= 1.0e-300) && (!m[colind[k]] && !m_inv[i])){
				m[colind[k]] = i;
				m_inv[i] = colind[k];
			}
		}
	}

}

#ifdef BINARY_HEAP
/*This is the dist_base, which helps in identifying the
 *index of an address in the heap.*/
static unsigned long dist_base=0;
#endif

/*WorkSpace Allocation Details: 
 * C1 = new ValueType[nnz_size]
 * u = new ValueType[nnz_size]
 * v = new ValueType[nnz_size]
 * m_inv = new Indices[n]
 * m = new Indices[n]
 * p = new Indices[n]
 * dist = new ValueType[n]
 **/
template<class ValueType,class Indices>
void CreateWorkSpace(ValueType **C1,ValueType **u,ValueType **v,Indices **m_inv,
Indices **m, Indices **p, ValueType **dist,Indices n,unsigned long nnz_size){
	*C1 = new ValueType[nnz_size];
	*u  = new ValueType[nnz_size];
	*v  = new ValueType[nnz_size];
	*dist = new ValueType[n];
	*m  = new Indices[n];
	*p = new Indices[n];
	*m_inv = new Indices[n];
}
template<class ValueType,class Indices>
void FreeWorkSpace(ValueType *C1,ValueType *u,ValueType *v,Indices *m_inv,
Indices *m,Indices *p,ValueType *dist){
	delete C1;delete dist;
	delete u;delete v;
	delete m;delete m_inv;
	delete p; 
}
/*********************************************/
/*Fully type parameterized MC64 Implementation*/
template <class RowStarts,class ColIndices,class Indices,
class ValueType,class CompareFunction>
size_t WeightedMatching(RowStarts *rowptr,ColIndices *colind,ValueType *C,
ValueType *C1,ValueType *dist,ValueType *u,ValueType *v,Indices *p,
Indices *m_inv,Indices *m, Indices n,CompareFunction cmpFunc){

	size_t i,j,i1,jend,k,m_inv_prev;
	size_t match_size=0;
	ValueType curr_shortest_path = (ValueType)0;
	ValueType curr_aug_path = GetMaxTypeValue<ValueType>(); 
	ValueType dist1; Indices itrace;
	BitArray_t *col_marker = CreateBitArray(n);
	BitArray_t *heap_marker = CreateBitArray(n);
	C--;m--;C1--;dist--;u--;v--;p--;m_inv--;
	rowptr--;colind--;
#if BINARY_HEAP
	Heap *bin_heap = NewBinaryHeap(cmpFunc,n,GetDistKeyID);  
	ValueType *dist_ptr = NULL;
#endif
	assert(C1 && dist && u && v && p);
	ComputeInitialExtremeMatch<ValueType,Indices>(u,v,C1,C,m,m_inv,colind,rowptr,n,dist);
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
#if BINARY_HEAP
		bin_heap->n = 0;
		dist_base = (unsigned long)&(dist[1]);
#endif
		curr_shortest_path=(ValueType)0;
		curr_aug_path=GetMaxTypeValue<ValueType>();
		while(1){
			for(k=rowptr[i1];k<rowptr[i1+1];k++){
				j = colind[k];
				if(CheckBit(col_marker,j)){
					continue;
				}
				dist1 = curr_shortest_path + C1[k];
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
					}else if(*((long long int *)&dist1) < *((long long int *)&(dist[j]))){ 
						/*Update the dist*/
						dist[j] = dist1; p[m[j]] = i1;
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
			dist_ptr = (ValueType *) HeapDelete(bin_heap);
			if(dist_ptr){
				assert((unsigned long)dist_ptr >= (unsigned long)&dist[1]);
				j = ((((unsigned long)dist_ptr -
					(unsigned long)&dist[1]))/sizeof(double))+1;
				assert(j>=1 && j<=n);
				curr_shortest_path = dist[j]; 
				UnsetBit(heap_marker,j); 
#endif
				SetBit(col_marker,j);
				i1 = m[j];
			}else{
				break;
			}
		}
		if(jend){ /*We found a shortest augmenting path*/
			j=jend;
			node_t itrace_prev;
			//printf("Shortest augmenting Path {");
			while(itrace){
				m_inv_prev = m_inv[itrace];
				m[j] = itrace; m_inv[itrace]=j;
				//printf("(%u,%u)",itrace,j);
				j=m_inv_prev;
				itrace_prev = itrace;
				itrace = p[itrace];
				if(itrace){
				//	printf("(%u,%u)",itrace_prev,m_inv_prev);
				}
			}
			match_size++;
			//printf("}\n");
			/*Update the cost with new match m*/
			for(j=1;j<=n;j++){
				if(CheckBit(col_marker,j)){
					u[j] = (u[j]+dist[j])-curr_aug_path;
					/*Reset the dist values*/
				}
			}
			for(i1=1;i1<=n;i1++){
				if(!m_inv[i1]) continue;
				j = m_inv[i1];
				for(k=rowptr[i1];k<rowptr[i1+1];k++){
					if(colind[k] == j){
						v[i1] = C[k] - u[j];
					}
				}
			}
			/*Update the cost*/
			for(i1=1;i1<=n;i1++){
				for(k=rowptr[i1];k<rowptr[i1+1];k++){
					j = colind[k];
					C1[k] = C[k]-(u[j]+v[i1]);
				}
				/*The index should be j rather than i1 but just 
				 *avoiding another loop*/
				dist[i1] = GetMaxTypeValue<double>();
			}
		}
	}
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
		if(fabs(val[k]-0.0)<=1.0e-300){
			val[k] = HUGE_VAL;
		}else{
			if(fabs(max_c[colind[k]]-0.0)<=1.0e-300){
				val[k] = HUGE_VAL;//MAX_DOUBLE_VALUE/n - (log(val[k])/M_LN10);
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
	/*****WorkSpace for MC64***/ 
	double *C1,*u,*v,*dist;
	node_t *m_inv,*p;
	/**************************/

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

	/**Create the WorkSpace for MC64****/
	CreateWorkSpace<double,node_t>(&C1,&u,&v,&m_inv,&(m->m),&p,&dist,G->order,G->nnz_size);

	WeightedMatching<node_t,node_t,node_t,double,KeyCompare>(G->rowptr,G->colind,G->nnz,
		C1,dist,u,v,p,m_inv,m->m,G->order,DoubleCompare);

	/**********************************/

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

	FreeWorkSpace<double,node_t>(C1,u,v,m_inv,m->m,p,dist);
	return 0;
}
#endif
