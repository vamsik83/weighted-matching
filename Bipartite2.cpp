/*
 * May 20,2008. Vamsi Kundeti.
 * Implementing unweighted and weighted 
 * bipartite matching algorithms.
 *
 * July 15,2008 [Modified for 0 indexing in rowptr and colind ]
 */
#define BINARY_HEAP 1
//#define TURN_ON_SAVE_HEAP 1
//#define USE_BIT_ARRAY 1
#define NO_LOCAL_PROFILING 1
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include "MeasureTime.h"
#include "Heap.h"
#include "Bipartite.h"
#define MAX_DOUBLE_VALUE 1.7976931348622e+308
int anst_ticks;

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
#ifndef WIN32
	 diff = llabs(a64int-b64int);
#else
	 diff = a64int-b64int;
	 diff = (diff < 0)?-diff:diff;
#endif
	 if(diff <= 50000){
		 return 1;
	 }
	 return 0;
}
/****************************************/
/*****Maximum values of the Types*******/
template<class Type>
Type GetMaxTypeValue(void);

template<class Type>
Type GetMaxTypeValue(Type a){
	fprintf(stderr,"GetMaxTypeValue undefined for this Type\n");
	assert(0);
	return (Type)0;
}
template<>
double GetMaxTypeValue(double a){
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
template<class Indices>
void CreateMC21WorkSpace(Indices n,Indices **col_marker,Indices **p,
Indices **m_inv){
	*col_marker = new Indices[n];
	*p = new Indices[n];
	*m_inv = new Indices[n];
}
template<class Indices>
void FreeMC21WorkSpace(Indices *col_marker,Indices *p,Indices *m_inv){
	delete col_marker; delete p;
	delete m_inv;
}
/*******************************************/
/*This implements the MC21 perfect matching*/
/*******************************************/
template<class RowStarts,class ColIndices,class Indices>
Indices FindPerfectMatch(RowStarts rowptr,ColIndices colind,Indices n,Indices *m,
Indices *p,Indices *m_inv,Indices *col_marker){
	Indices match_size=(Indices)0;
	Indices i,j,k,i1,jend;node_t m_inv_prev;
	bool aug_extend=false;
	colind--;rowptr--;m--;p--;m_inv--;col_marker--;

	for(i=1;i<=n;i++){
		m_inv[i]=0;
		m[i] = 0;
	}

	for(i=1;i<=n;i++){
		/*Augmenting path at any unmatched node*/
		if(m_inv[i]){
			continue;
		}

		i1 = i; p[i1]=0; jend=0;
		while(i1 && !jend){
			for(k=rowptr[i1];k<rowptr[i1+1];k++){
				j = colind[k];
				if(!m[j]){
					jend=j;
					break;
				}
			}
			if(jend){
				/*Found an unmatched node*/
				break;
			}
			aug_extend = false;
			for(k=rowptr[i1];k<rowptr[i1+1];k++){
				j = colind[k];
				if((col_marker[j]!=i) && m[j]){
					p[m[j]]=i1;
					col_marker[j]=i;
					i1 = m[j];
					aug_extend = true;
					break;
				}
			}
			if(!aug_extend){
				/*Unable to find a unmarked matched node
				 *go back to parent of i1*/
				i1 = p[i1];
			}
		}
		if(jend){
			/*Augmenting path is found so augment*/
			j = jend; 
			/*printf("Augmenting the path {");*/
			while(i1){
				m_inv_prev = m_inv[i1];
				/*Flip the Match*/
				m[j] = i1; m_inv[i1] = j;
				/*printf("(%u,%u)",i1,j);*/
				j = m_inv_prev;
				i1 = p[i1];
			}
			/*printf("}\n");*/
			match_size++;
			/*printf("Match Size: %u\n",match_size);*/
		}
	}
	return match_size;
}
/**********MC21 Wrapper function**********/
template <class RowStarts,class ColIndices,class Indices>
void ANSTMC21(RowStarts rowptr,ColIndices colind,Indices n,Indices *m){
	Indices *col_marker;
	Clock *anst_clock = CreateClock();
	Indices *p; Indices *m_inv;
	CreateMC21WorkSpace(n,&col_marker,&p,&m_inv);
	StartClock(anst_clock);
	FindPerfectMatch(rowptr,colind,n,m,p,m_inv,col_marker);
	StopClock(anst_clock);
	anst_ticks = GetClockTicks(anst_clock);
	FreeMC21WorkSpace(col_marker,p,m_inv);
	free(anst_clock);
}
int InitialMatchTicks;
/*******************************************/
/***Initial Extreme Matching Function*******/
/**Also 1-Augment the Initial Extreme Match**/
/********************************************/
template <class ValueType,class Indices>
void ComputeInitialExtremeMatch(ValueType *u,ValueType *v,Indices *clabel,ValueType *C,
	Indices *m,Indices *m_inv,Indices* colind,Indices* rowptr,Indices n,ValueType *dist){

	Indices i,k,i1,k1;
	Indices k0,k10,j0,j,j1,j10;
	ValueType vmin;
	ValueType C1k;
	Clock *init_match_clk = CreateClock();
	StartClock(init_match_clk);
#if 0
	/*Compute u[j]*/
	for(j=1;j<=n;j++){
		u[j] = GetMaxTypeValue<ValueType>(u[j]); 
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

#endif
	/*Compute v[i]*/
	for(i=1;i<=n;i++){
		v[i] = GetMaxTypeValue<ValueType>(v[i]);
		for(k=rowptr[i]+1;k<(rowptr[i+1]+1);k++){ 
			j = colind[k]+1; 
			vmin = (C[k]-u[j]);
			if(vmin < v[i]){
				v[i] = vmin;
			}
		}
	}
	/*Update Cost and match.*/
	for(i=1;i<=n;i++){
		for(k=rowptr[i]+1;k<(rowptr[i+1]+1);k++){ 
			j = colind[k]+1; 
			C1k = C[k]-v[i]-u[j]; /*to handle -0.0*/
			if(fabs(C1k-0.0) <= 1.0e-30 && (!m[j] && !m_inv[i])){
				m[j] = i;
				m_inv[i] = j;
				clabel[i] = k;
			}
		}
	}
	/*1-Step Augmentation*/
	for(i=1;i<=n;i++){
		if(!m_inv[i]){ /*Unmatched Row*/
			for(k=rowptr[i]+1;k<(rowptr[i+1]+1) && !(m_inv[i]);k++){ 
				j = colind[k]+1; 
				C1k = fabs(C[k]-v[i]-u[j]);
				if(C1k <= 1.0e-30){
					/*assert(m[colind[k]]);*/
					i1 = m[j];
					/*assert(m_inv[i1] == j);*/
					/*See if we can find any C1(i1,j1) == 0*/
					for(k1=rowptr[i1]+1;k1<(rowptr[i1+1]+1);k1++){ 
						j1 = colind[k1]+1; 
						C1k = fabs(C[k1] - v[i1]-u[j1]);
						if(C1k <= 1.0e-30 && !(m[j1])){
							/*augment the match.*/
							m[j] = i;
							m_inv[i] = j;
							clabel[i] = k;
							m[j1] = i1;
							m_inv[i1] = j1;
							clabel[i1] = k1;
							break;
						}
					}
				}

			}
		}
	}
	StopClock(init_match_clk);
	InitialMatchTicks = GetClockTicks(init_match_clk);
}

#ifdef BINARY_HEAP
/*This is the dist_base, which helps in identifying the
 *index of an address in the heap.*/
unsigned long dist_base=0;
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
void CreateWorkSpace(ValueType **u,ValueType **v,Indices **m_inv,
Indices **p, ValueType **dist,Indices n){
	//*C1 = new ValueType[nnz_size];
	*u  = new ValueType[n];
	*v  = new ValueType[n];
	*dist = new ValueType[n];
	*p = new Indices[n];
	*m_inv = new Indices[n];
}
template<class ValueType,class Indices>
void FreeWorkSpace(ValueType *C1,ValueType *u,ValueType *v,Indices *m_inv,
Indices *m,Indices *p,ValueType *dist){
	delete dist;
	delete u;delete v;
	delete m;delete m_inv;
	delete p; 
}
/*Profile three Major Components
 *1. ComputeInitial Match
 *2. Operations on Heap
 *3. Dual Update operation (Including augmentation).
 */
#ifndef NO_LOCAL_PROFILING
Clock *hins_clk,*hdel_clk,*hupdate_clk;
Clock *dual_clk;
clock_t hins_ticks,hdel_ticks,hupdate_ticks;
clock_t dual_ticks;
void CreateProfilingClocks(void){
	hins_ticks=0;hdel_ticks=0;hupdate_ticks=0;
	dual_ticks=0;
	hins_clk = CreateClock(); hdel_clk = CreateClock();
	hdel_clk = CreateClock(); hupdate_clk = CreateClock();
	dual_clk = CreateClock();
}
#endif
void *free_this_guys[5];
/*Top Level Wrapper for WeightedMatching.*/
template <class RowStarts,class ColIndices,class ValueTypePtr,class Indices>
void ANSTMC64(RowStarts rowptr,ColIndices colind,ValueTypePtr val,Indices n,Indices *perm){
	typedef typename std::iterator_traits<ValueTypePtr>::value_type ValueType;
	ValueType *u,*v,*dist;
	Indices *p,*m_inv;
	Indices i,k;
	Indices nnz_count=0;
	/*Fake 0 indexing by doing a --*/
	for(i=0;i<=n;i++){
		rowptr[i]--;
	}
	for(i=0;i<n;i++){
		for(k=rowptr[i];k<rowptr[i+1];k++){
			colind[k]--;
			nnz_count++;
		}
	}

	CreateWorkSpace<double,node_t>(&u,&v,&m_inv,&p,&dist,n);
	LogTransformT(rowptr,colind,val,n,u,v,dist,perm,m_inv);
	WeightedMatching(rowptr,colind,val,dist,u,v,p,m_inv,perm,n,DoubleCompare);

	for(i=0;i<=n;i++){
		rowptr[i]++;
	}
	for(k=0;k<nnz_count;k++){
		colind[k]++;
	}

	delete u;delete v;delete dist;
	delete p;delete m_inv;
}
#ifdef WIN32 
unsigned long WeightedMatchTicks;
#else
clock_t WeightedMatchTicks;
#endif
/*********************************************/
/*Fully type parameterized MC64 Implementation*/
/**********************************************/
template <class RowStarts,class ColIndices,class Indices,
class ValueTypePtr,class CompareFunction>
size_t WeightedMatching(RowStarts rowptr,ColIndices colind,ValueTypePtr C,
ValueTypePtr dist,ValueTypePtr u,ValueTypePtr v,Indices *p,
Indices *m_inv,Indices *m, Indices n,CompareFunction cmpFunc){
	typedef typename std::iterator_traits<ValueTypePtr>::value_type ValueType;
	Indices i,j,i1,jend,k,m_inv_prev;
	Indices match_size=0; Indices k0,j0;
	ValueType curr_shortest_path = (ValueType)0;
	ValueType curr_aug_path = GetMaxTypeValue<ValueType>(curr_aug_path); 
	ValueType dist1; Indices itrace;
	/*Cost of the edges in the match if
	 *$(i,j) \in M$ then $clabel[i] = C[i][j]$*/
	Indices *clabel = new Indices[n];
	Indices *aug_label = new Indices[n];
	Indices *update_stack = new Indices[n];
	Indices update_stack_index;
	/*Save The Operations on the Heap.*/
	Indices save_heap_index;
	Indices *save_heap_op = new Indices[n];
#ifdef TURN_ON_SAVE_HEAP
	double close_factor = (double)1.0 + (double)1.0e-16;
#endif
	/*Force the write back to memory to avoid floating point issues*/
	ValueType force_mem_write[3];
#ifndef NO_LOCAL_PROFILING
	CreateProfilingClocks();
#endif

	/*Core Profiling Clock*/
	Clock *core_clk = CreateClock();
#ifdef USE_BIT_ARRAY
	BitArray_t *col_marker = CreateBitArray(n);
	BitArray_t *heap_marker = CreateBitArray(n);
#else
	Indices *col_marker = new Indices[n];
	unsigned int *heap_marker = NULL;
	col_marker--;
	for(i=1;i<=n;i++){ /*Do we need Initialization?*/
		col_marker[i] = (Indices)0;
	}
#endif
#if BINARY_HEAP
	Heap *bin_heap = NewBinaryHeap(cmpFunc,n,GetDistKeyID);  
	ValueType *dist_ptr = NULL;
	heap_marker = bin_heap->keyMap;
#endif
	/*Algorithm Uses 1-Indexing to be consistent*/
	C--;m--;dist--;u--;v--;p--;m_inv--;
	rowptr--;colind--;clabel--;save_heap_op--;
	update_stack--;aug_label--;
	assert(dist && u && v && p);
	ComputeInitialExtremeMatch<ValueType,Indices>(u,v,clabel,C,m,m_inv,colind,
		rowptr,n,dist);
	match_size=0; 

	StartClock(core_clk);

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
#ifdef USE_BIT_ARRAY
		ResetAllBits(col_marker);
		ResetAllBits(heap_marker);
#endif

#if BINARY_HEAP
		bin_heap->n = 0;
		dist_base = (unsigned long)&(dist[1]);
#endif
		curr_shortest_path=(ValueType)0;
		curr_aug_path=GetMaxTypeValue<ValueType>(curr_aug_path);
		save_heap_index = (Indices)0;
		update_stack_index = (Indices)0;
		while(1){
			for(k=rowptr[i1]+1;k<(rowptr[i1+1]+1);k++){ 
				j = colind[k]+1; 
#ifdef USE_BIT_ARRAY
				if(CheckBit(col_marker,j)){
#else
				if(col_marker[j]==i){
#endif
					continue;
				}
				force_mem_write[k%3] = C[k]-(v[i1]+u[j]);
				dist1 = curr_shortest_path + force_mem_write[k%3];
				/*Prune any dist1's > curr_aug_path, since
				 *all the costs>0 
				 */
				if(dist1 < curr_aug_path){
					if(!m[j]){
						/*we need itrace because, the last i1 which
						 *we explore may not actually give the shortest 
						 *augmenting path.*/
						jend = j; itrace = i1;
						curr_aug_path = dist1;
						aug_label[j] = k;
					}else if(dist1 < dist[j]){ 
						/*Update the dist*/
						dist[j] = dist1; p[m[j]] = i1;
						aug_label[j] = k;
#if SIMPLE_HEAP

#ifdef USE_BIT_ARRAY
						SetBit(heap_marker,j);
#else
						heap_marker[j] = i;
#endif

#elif BINARY_HEAP /*SIMPLE_HEAP*/

#ifdef USE_BIT_ARRAY
						if(CheckBit(heap_marker,j)){
#else
						if(heap_marker[j]){
#endif
#ifndef NO_LOCAL_PROFILING
							StartClock(hupdate_clk);
#endif
							/*Call the decrease Key Operation*/
							DecreaseKey(bin_heap,j);

#ifndef NO_LOCAL_PROFILING
							StopClock(hupdate_clk);
							hupdate_ticks += GetClockTicks(hupdate_clk);
#endif
						}
#ifdef TURN_ON_SAVE_HEAP 
						else if(curr_shortest_path &&  
							dist[j] <= (curr_shortest_path)*(close_factor)){
							/*If dist[j] is close to root push it in
							 *save_heap_op*/
							 assert(save_heap_index < n);
							 save_heap_op[++save_heap_index] = j;
						}
#endif					
						else{
#ifndef NO_LOCAL_PROFILING
							StartClock(hins_clk);
#endif
							InsertHeap(bin_heap,&(dist[j]));
#ifndef NO_LOCAL_PROFILING
							StopClock(hins_clk);
							hins_ticks += GetClockTicks(hins_clk);
#endif
#ifdef USE_BIT_ARRAY
							SetBit(heap_marker,j);
#endif
						}
#endif /*SIMPLE_HEAP*/
					}
				}
			}
			if(curr_aug_path <= curr_shortest_path){ 
				break;
			}
			/*We now have a heap of matched cols, so pick the min*/
#ifdef SIMPLE_HEAP
			j = SimplePickMin(heap_marker,dist,n);
			if(j){
				curr_shortest_path = dist[j]; 
				UnsetBit(heap_marker,j); 
#elif BINARY_HEAP


#ifndef NO_LOCAL_PROFILING
			StartClock(hdel_clk);
#endif
			if(save_heap_index){
				j = save_heap_op[save_heap_index];
				save_heap_index--;
				curr_shortest_path = dist[j]; 
#ifdef USE_BIT_ARRAY
				SetBit(col_marker,j);
#else
				col_marker[j] = (Indices)i;
				update_stack[++update_stack_index]=j;
#endif /*#ifdef USE_BIT_ARRAY*/

				i1 = m[j];
			}else if(dist_ptr = (ValueType *) HeapDelete(bin_heap)) {
#ifndef NO_LOCAL_PROFILING
				StopClock(hdel_clk);
				hdel_ticks += GetClockTicks(hdel_clk);
#endif
				assert((unsigned long)dist_ptr >= (unsigned long)&dist[1]);
				j = ((((unsigned long)dist_ptr -
					(unsigned long)&dist[1]))/sizeof(ValueType))+1;
				assert(j>=1 && j<=n);
				curr_shortest_path = dist[j]; 
				heap_marker[j] = 0; /*Setting the keyMap in Heap to 0*/
#endif /*#ifdef SIMPLE_HEAP */


#ifdef USE_BIT_ARRAY
				SetBit(col_marker,j);
				update_stack[++update_stack_index]=j;
#else
				col_marker[j] = (Indices)i;
				update_stack[++update_stack_index]=j;
#endif /*#ifdef USE_BIT_ARRAY*/

				i1 = m[j];
			}else{
				break;
			}
		}
		/*We found a shortest augmenting path*/
		if(jend){ 
			unsigned long **harray = bin_heap->heapArray;
#ifndef NO_LOCAL_PROFILING
			StartClock(dual_clk);
#endif
			/*NOTE1: We need a very fast way to update
			 *the dual variables and also reset the dist[]
			 *we avoid linear scan where ever we can to update
			 *these dual variables*/
			while(update_stack_index){ /*Update u[j]: while*/
				j=update_stack[update_stack_index--];
				u[j] = (u[j]+dist[j])-curr_aug_path;
				if(m[j]){ /*See NOTE1*/
					i1 = m[j];
					v[i1] = C[clabel[i1]] - u[j];
				}
				dist[j] = MAX_DOUBLE_VALUE;
				if(bin_heap->n){
					dist_ptr = (double *)harray[bin_heap->n];
					j = ((((unsigned long)dist_ptr -
						(unsigned long)&dist[1]))/sizeof(ValueType))+1;
					heap_marker[j] = 0;
					*((double *)harray[bin_heap->n]) = MAX_DOUBLE_VALUE;
					bin_heap->n -= 1 ;
				}
			} /*Update u[j]: while*/
			
			/*Uncomment if you need to print augmenting path*/
			/*node_t itrace_prev;*/
			/*printf("Shortest augmenting Path {");*/

			j=jend;
			while(itrace){
				m_inv_prev = m_inv[itrace];
				m[j] = itrace; m_inv[itrace]=j;
				/*See NOTE1(above)*/
				clabel[itrace] = aug_label[j];
				v[itrace] = C[clabel[itrace]] - u[j];
				/*printf("(%u,%u)",itrace,j);*/
				j=m_inv_prev;
				/*itrace_prev = itrace;*/
				itrace = p[itrace];
				/*
				if(itrace){
					printf("(%u,%u)",itrace_prev,m_inv_prev);
				}*/
			}
			/*printf("}\n");*/
			/*There may some dist[] still in the heap*/
			while(bin_heap->n){
				dist_ptr = (double *)harray[bin_heap->n];
				j = ((((unsigned long)dist_ptr -
					(unsigned long)&dist[1]))/sizeof(ValueType))+1;
				heap_marker[j] = 0;
				*((double *)harray[bin_heap->n]) = MAX_DOUBLE_VALUE;
				bin_heap->n -= 1;
			}
			match_size++;
			/*End Dual Update*/
#ifndef NO_LOCAL_PROFILING
			StopClock(dual_clk);
			dual_ticks += GetClockTicks(dual_clk);
#endif
		} /*if(jend) : Found Augmeting Path*/
	} /*for(i=1;i<=n;i++): Main Outer Loop*/

	StopClock(core_clk);
	WeightedMatchTicks = GetClockTicks(core_clk);

#ifndef NO_LOCAL_PROFILING
	printf("Profile Summary\n");
	printf("HINS=(%d) HDEL=(%d) HUPDATE=(%d)\n",(int)hins_ticks,(int)hdel_ticks,
		(int)hupdate_ticks);
	printf("DUAL=(%d) \n",(int)dual_ticks);
#endif

#ifdef USE_BIT_ARRAY
	FreeBitArray(col_marker);
	FreeBitArray(heap_marker);
#else
	col_marker++;
	delete col_marker; 
#endif

#ifdef SIMPLE_HEAP
	heap_marker++;
	delete heap_marker;
#endif

	aug_label++;
	delete aug_label;
	save_heap_op++;
	delete save_heap_op;
	clabel++;
	delete clabel;
#ifdef BINARY_HEAP	
	FreeHeap(bin_heap);
#endif
	return match_size;
}
/*O(n) time picking the maximum from the heap_marker */
node_t SimplePickMin(BitArray_t *bit_heap,double *dist,node_t n){
	node_t min_j=0;node_t j; 
	double curr_min = HUGE_VAL; 
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
/*****Templated LogTranform call******/
template <class RowStarts,class ColIndices,class Indices,class ValueType>
void LogTransformT(RowStarts *rowptr,ColIndices *colind,ValueType *val,Indices n,ValueType *u,
ValueType *v,ValueType *dist,Indices *m,Indices *m_inv){
	ValueType *max_c = new ValueType[n];
	rowptr--;colind--;val--;max_c--; m--; m_inv--; u--; dist--;
	Indices k,i,j,j0;
	Clock *anst_clk;

	anst_clk = CreateClock();
	StartClock(anst_clk);
	/*TODO: Avoid HUGE_VAL directly in templated code*/
	for(j=1;j<=n;j++){
		/*Find the maximum in the column*/
		max_c[j] = (ValueType)0.0;
		m[j] = (Indices)0; m_inv[j]=0;
		u[j] = HUGE_VAL;dist[j]=HUGE_VAL;
	}

	for(i=1;i<=n;i++){
		for(k=rowptr[i]+1;k<(rowptr[i+1]+1);k++){
			val[k] = fabs(val[k]);
			j = colind[k]+1; 
			if(val[k] > max_c[j]){
				max_c[j] = val[k];
			}
		}
	}
#if 0
	for(k=1;k<=n;k++){
		printf("max in col %u is %e \n",k,max_c[k]);
	}
#endif
	for(i=1;i<=n;i++){
		for(k=rowptr[i]+1;k<(rowptr[i+1]+1);k++){
			j = colind[k]+1; 
			if(val[k]<=1.0e-30){
				val[k] = HUGE_VAL;
			}else{
				if(max_c[j]<=1.0e-30){
					val[k] = HUGE_VAL;//MAX_DOUBLE_VALUE/n - (log(val[k])/M_LN10);
				}else{
					val[k] = log10(max_c[j]/val[k]);
					val[k] = fabs(val[k]);
					if(val[k]< u[j]){
						u[j] = val[k];
					}
				}
			}
			/*take care of -0.0*/
			/*assert(val[k]>=0.0);*/
		}
	}

	StopClock(anst_clk);
	anst_ticks = GetClockTicks(anst_clk);
	++max_c;
	delete max_c;
}

void LogTransform(SparseGraph *G){
	node_t *rowptr = G->rowptr; rowptr--;
	node_t *colind = G->colind; colind--;
	double *val = G->nnz;val--;
	node_t n = G->order; node_t k;
	node_t nnz_size = G->nnz_size;
	node_t k0,j0;
	double *max_c = (double *)calloc(n,sizeof(double));max_c--;
#if 0
	for(k=1;k<=n;k++){
		/*Find the maximum in the column*/
		max_c[k] = (double)0.0;
	}
#endif
	Clock *anst_clk = CreateClock();
	StartClock(anst_clk);
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
		if(fabs(val[k]-0.0)<=1.0e-30){
			val[k] = HUGE_VAL;
		}else{
			if(fabs(max_c[colind[k]]-0.0)<=1.0e-30){
				val[k] = HUGE_VAL;//MAX_DOUBLE_VALUE/n - (log(val[k])/M_LN10);
			}else{
				val[k] = log10(max_c[colind[k]]/val[k]);
				val[k] = fabs(val[k]);
			}
		}
		/*take care of -0.0*/
		assert(val[k]>=0.0);
	}
	StopClock(anst_clk);
	anst_ticks = GetClockTicks(anst_clk);
	free(++max_c);
}
#ifndef SOLARIS 
#ifndef STANDALONE_MODE
extern int mc64_ticks;
#endif
#endif

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
	/*This is the permutation vector passing from outside**/
	m->m = new unsigned int[G->order];


#ifdef USE_OLD_MC64_CALL
	/**Create the WorkSpace for MC64****/
	double *C1,*u,*v,*dist;
	node_t *m_inv,*p;
	CreateWorkSpace<double,node_t>(&u,&v,&m_inv,&p,&dist,G->order);
	LogTransformT(G->rowptr,G->colind,G->nnz,G->order,u,v,dist,m->m,m_inv);
	WeightedMatching<node_t,node_t,double,KeyCompare>(G->rowptr,G->colind,G->nnz,dist,
		u,v,p,m_inv,m->m,G->order,DoubleCompare);

#else

#ifndef USE_MC21 
	ANSTMC64(G->rowptr,G->colind,G->nnz,G->order,(m->m));
#else
	ANSTMC21(G->rowptr,G->colind,G->order,(m->m));
#endif /*USE_MC21*/

#endif /*USE_OLD_MC64_CALL*/
	val1 = G->nnz; val1--;

#ifdef STANDALONE_MODE
#ifdef USE_MC21
	printf("MC21 TICKS = (%d) \n",anst_ticks);
	exit(0);
#else

#ifndef SOLARIS

#ifndef STANDALONE_MODE
	printf("Ticks(Initial Match) = (%d) , Ticks(Core) = (%d),LogTransform(%d),MC64(%d)\n",(int)InitialMatchTicks,(int)WeightedMatchTicks,(int)anst_ticks,(int)mc64_ticks);
#else
	printf("Ticks(Initial Match) = (%d) , Ticks(Core) = (%d),LogTransform(%d)\n",(int)InitialMatchTicks,(int)WeightedMatchTicks,(int)anst_ticks);
#endif

#else
	printf("Ticks(Initial Match) = (%d) , Ticks(Core) = (%d),LogTransform(%d)\n",(int)InitialMatchTicks,(int)WeightedMatchTicks,(int)anst_ticks);
#endif
	printf("Total Ticks = (%d) \n",(int)InitialMatchTicks+(int)WeightedMatchTicks+(int)anst_ticks);
	exit(0);
#endif
#endif

	char filebuffer[1024];

/*Lets call this first*/
#ifndef SOLARIS
	/*Now call the MC64*/
	printf("Starting MC64....\n");
	//perm = (int *)malloc(sizeof(int)*(G->order));
	//ComputePermutation((int *)G->rowptr,(int *)G->colind,G->nnz,G->nnz_size,G->order,perm);
	MC64Driver(argc,argv);
#endif


#ifdef SOLARIS
	/**********************************/
	/*Open the .perm file*/
	sprintf(filebuffer,"%s.perm",argv[1]);
	int *perm;
	FILE *perm_file = fopen(filebuffer,"r");
	if(!perm_file){
		fprintf(stderr,"Unable to open the permfile Creating it....\n");
		sprintf(filebuffer,"./create_perm %s",argv[1]);
		sprintf(filebuffer,"%s.perm",argv[1]);
		perm_file = fopen(filebuffer,"r");
	}
	/*Read the permutation*/
	perm = NULL;
	perm = (int *)malloc(sizeof(int)*(G->order));
	assert(perm);
	for(i=0;i<G->order;i++){
		fscanf(perm_file,"%d",&(perm[i]));
	}
#endif
	printf("Verifying the permutation\n");
	char failed=0;
	double unmatched_product_i1=1.0;
	double unmatched_product_i2=1.0;
	double unmatched_sum_i1=0.0;
	double unmatched_sum_i2=0.0;
	/*Write out the diagonal elements*/
	sprintf(filebuffer,"%s.mc64.diag",argv[1]);
	FILE *diag1 = fopen(filebuffer,"w"); sprintf(filebuffer,"%s.anst.diag",argv[1]);
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
#ifndef SOLARIS

#ifndef STANDALONE_MODE
			printf("TIME1 = (%d) , TIME2 = (%d) \n",anst_ticks,mc64_ticks);
#endif

#endif
			exit(1);
		}
	}
	printf("\n\nSUCCESS\n");
	printf("\n pd1=%e pd2=%e \n",unmatched_product_i1,unmatched_product_i2);
	printf("sum1=%e sum2=%e \n",unmatched_sum_i1,unmatched_sum_i2);
	printf("\n");
#ifndef SOLARIS
#ifndef USE_MC21 

#ifndef STANDALONE_MODE
	printf("TIME1 = (%d) , TIME2 = (%d) \n",((int)InitialMatchTicks+(int)WeightedMatchTicks),mc64_ticks);
#endif

#else

#ifndef STANDALONE_MODE
	printf("TIME1 = (%d) ,TIME2 = (%d) \n",anst_ticks,mc64_ticks);
#endif

#endif
#endif
#ifndef USE_MC21 

#ifndef SOLARIS
	printf("Ticks(Initial Match) = (%d) , Ticks(Core) = (%d),LogTransform(%d),MC64(%d)\n",
	(int)InitialMatchTicks,(int)WeightedMatchTicks,(int)anst_ticks,(int)mc64_ticks);
#else
	printf("Ticks(Initial Match) = (%d) , Ticks(Core) = (%d),LogTransform(%d)\n",(int)InitialMatchTicks,(int)WeightedMatchTicks,(int)anst_ticks);
#endif


#endif
#ifndef NO_LOCAL_PROFILING
	printf("Ticks(Initial Match) = (%d) , Ticks(Core) = (%d)\n",InitialMatchTicks,
		(int)WeightedMatchTicks);
	printf("Profile Summary\n");
	printf("===============\n");
	printf("HINS=(%d) HDEL=(%d) HUPDATE=(%d)\n",(int)hins_ticks,(int)hdel_ticks,
		(int)hupdate_ticks);
	printf("DUAL=(%d) \n",(int)dual_ticks);
#endif
#ifdef USE_OLD_MC64_CALL
	FreeWorkSpace<double,node_t>(C1,u,v,m_inv,m->m,p,dist);
#else
	delete (m->m);
#endif
	return 0;
}
#endif
