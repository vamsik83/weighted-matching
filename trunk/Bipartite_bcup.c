/*
 * May 20,2008. Vamsi Kundeti.
 * Implementing unweighted and weighted bipartite matching algorithms.
 */
#include<stdlib.h>
#include<math.h>
#include<assert.h>
#include "Bipartite.h"
/*This implements the MC21 perfect matching*/
template <class RowStarts, class ColIndices, class Indices>
match_size_t FindPerfectMatch(Indices match, RowStarts row_starts, 
							  ColIndices col_indices, std::size_t n, 
							  std::size_t nnz, Indices col_marker,
							  Indices P, Indices Minv){
	unsigned int match_size=0;
	assert(G && M);
	//std::size_t n = G->order;
	//double *nnz=G->nnz;
	//std::size_t *colind=G->colind;colind--;
	//std::size_t *rowptr=G->rowptr;rowptr--;
	//std::size_t *m = M->m;m--;
	//BitArray_t *col_marker = CreateBitArray(n);
	//BitArray_t *matched_row = CreateBitArray(n);
	//std::size_t *p = (std::size_t *) malloc(sizeof(std::size_t)*n);p--;
	//std::size_t *m_inv = (std::size_t *) malloc(sizeof(std::size_t)*n);m_inv--;
	std::size_t i,j,k,i1,jend;std::size_t m_inv_prev;char aug_extend=0;
	match_size=0;
	for(i=0;i<n;i++){
		Minv[i] = n+1;
	}
	/*for(j=1;j<=n;j++){
		if(m[j]){
			m_inv[m[j]]=j;
			match_size++;
		}
	}*/
	for(i=1;i<=n;i++){
		/*Augmenting path at any unmatched node*/
		if(m_inv[i]){
			continue;
		}
		i1 = i; p[i1]=0; jend=0;
		//ResetAllBits(col_marker);
		while(i1 && !jend){
			std::size_t end = row_ptr [i1+1] ;
			for(std::size_t k = row_ptr [i1] ; k < end ; k++){
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
			bool aug_extend=false;
			for(k=0;k<(rowptr[i1+1]-rowptr[i1]) && !jend;k++){
				j = colind[rowptr[i1]+k];
				if(!CheckBit(col_marker,j)){
					p[m[j]]=i1;
					//m_inv[m[j]]=j;
					SetBit(col_marker,j);
					i1 = m[j];
					aug_extend = true ;
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
	//FreeBitArray(col_marker); FreeBitArray(matched_row);
	//free(++m_inv); free(++p);
	return match_size;
}
/*MC64: Weighted Bipartite matching, MAKE SURE that M is *a 'extreme' 
 *matching w.r.t nnz values in G->nnz, if you are not passing an empty
 *match.
 */
match_size_t WeightedMatching(Match_t *M,SparseGraph *G){
	double *C = G->nnz;C--;std::size_t *m = M->m;m--;
	std::size_t n = G->order;std::size_t i,j,i1,jend,k,m_inv_prev;
	double curr_shortest_path=0;double curr_aug_path=HUGE_VAL;
	double *C1 = (double *)malloc(sizeof(double)*(G->nnz_size));C1--;
	double *dist = (double *)malloc(sizeof(double)*n);dist--;
	double *u = (double *)malloc(sizeof(double)*n);u--;
	double *v = (double *)malloc(sizeof(double)*n);v--;
	std::size_t *m_inv = (std::size_t *)malloc(sizeof(std::size_t)*n);m_inv--;
	std::size_t *rowptr = G->rowptr; rowptr--;
	std::size_t *colind = G->colind; colind--;
	std::size_t *p = (std::size_t *) malloc(sizeof(std::size_t)*n);p--;
	unsigned int match_size=0;double dist1; std::size_t itrace;
	BitArray_t *col_marker = CreateBitArray(n);
	BitArray_t *heap_marker = CreateBitArray(n);

	assert(C1 && dist && u && v && p);

	/*If the matching is not M has to be an extreme matching*/
	for(i=1;i<=G->nnz_size;i++){
		if(i<=n){
			m_inv[i] = 0;
			u[i]=0; v[i]=0;
		}
		C1[i] = C[i];
	}
	for(j=1;j<=n;j++){
		if(m[j]){
			m_inv[m[j]]=j;
		}
		dist[j] = HUGE_VAL; 
	}

	for(i=1;i<=n;i++){
		if(m_inv[i]){
			continue;
		}
		/*
		 *Aim is to find a value for jend such that the path
		 *from i-->jend is the shortest
		 */
		i1 = i; p[i1] = 0; jend=0; 
		ResetAllBits(col_marker);
		ResetAllBits(heap_marker);
		curr_shortest_path=0;curr_aug_path=HUGE_VAL;
		while(curr_aug_path > curr_shortest_path){
			for(k=0;k<(rowptr[i1+1]-rowptr[i1]);k++){
				j = colind[rowptr[i1]+k];
				if(CheckBit(col_marker,j)){
					continue;
				}
				dist1 = curr_shortest_path + C1[rowptr[i1]+k];
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
					}else if(dist1 < dist[j]){ /*Update the dist*/
						dist[j] = dist1; p[m[j]] = i1;
						SetBit(heap_marker,j);
					}
				}
			}
			/*We now have a heap of matched cols, so pick the min*/
			j = SimplePickMin(heap_marker,dist,n);
			if(j){
				curr_shortest_path = dist[j]; 
				UnsetBit(heap_marker,j); SetBit(col_marker,j);
				i1 = m[j];
			}else{
				break;
			}
		}
		if(jend){ /*We found a shortest augmenting path*/
			j=jend;
			std::size_t itrace_prev;
			//printf("Shortest augmenting Path {");
			match_size = 0;
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
				match_size++;
			}
			//printf("}\n");
			/*Update the cost with new match m*/
			for(j=1;j<=n;j++){
				if(CheckBit(col_marker,j)){
					u[j] = u[j]+dist[j]-curr_aug_path;
					/*Reset the dist values*/
				}
			}
			for(i1=1;i1<=n;i1++){
				if(!m_inv[i1]) continue;
				j = m_inv[i1];
				std::size_t end = rowptr [i1 + 1] ;
				for(std::size_t k = rowptr[i1];k < end ; k++){
					if(colind[k] == j){
						v[i1] = C[k] - u[j];
						assert (C[k] - u[j] - v[i1] == 0.0) ;
						break ;
					}
				}
			}
			/*Update the cost*/
			for(i1=1;i1<=n;i1++){
				for(k=0;k<(rowptr[i1+1]-rowptr[i1]);k++){
					j = colind[rowptr[i1]+k];
					C1[rowptr[i1]+k] = C[rowptr[i1]+k]-u[j]-v[i1];
				}
				/*The index should be j rather than i1 but just 
				 *avoiding another loop*/
				dist[i1] = HUGE_VAL;
			}
		}
	}
	/*TODO: Freeup the stuff*/
}
std::size_t SimplePickMin(BitArray_t *bit_heap,double *dist,std::size_t n){
	std::size_t min_j=0;std::size_t j; 
	double curr_min = HUGE_VAL; 
	for(j=1;j<=n;j++){
		if(CheckBit(bit_heap,j) && dist[j]<curr_min){
			min_j = j;
			curr_min = dist[j];
		}
	}
	return min_j;
}

BitArray_t* CreateBitArray(unsigned int size){
	/* change it to O(n) representation */
	div_t d = div(size,SIZE_OF_BYTE_IN_BITS);
	unsigned int len;
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
	(b->ba)[d.quot] = (b->ba)[d.quot]|(1<<(d.rem));
}
inline void UnsetBit(BitArray_t *b,unsigned int bitno){
	div_t d;
	assert(bitno>=1 && bitno<=(b->size*SIZE_OF_BYTE_IN_BITS));
	d = div((bitno-1),SIZE_OF_BYTE_IN_BITS);
	(b->ba)[d.quot] = (b->ba)[d.quot]^(1<<(d.rem));
}
inline unsigned char CheckBit(BitArray_t* b,unsigned int bitno){
	div_t d;
	assert(bitno>=1 && bitno<=(b->size*SIZE_OF_BYTE_IN_BITS));
	d = div(bitno-1,SIZE_OF_BYTE_IN_BITS);
	return ((b->ba)[d.quot] & (1<<(d.rem)));
}
inline void ResetAllBits(BitArray_t *b){
	memset(b->ba,'\0',b->size);
}
void FreeBitArray(BitArray_t *b){
	free(b->ba);
	free(b);
}
/*std::size_t with value 0 is considered an empty node*/
Match_t * CreateEmptyMatch(unsigned int n){
	unsigned int i;
	Match_t *ma = (Match_t *)malloc(sizeof(Match_t)*1);
	ma->m = (std::size_t *) malloc(sizeof(std::size_t)*n);
	for(i=0;i<n;i++){
		ma->m[i] = 0;
	}
	return ma;
}

void LogTransform(SparseGraph *G){
	std::size_t *rowptr = G->rowptr; rowptr--;
	std::size_t *colind = G->colind; colind--;
	double *val = G->nnz;val--;
	std::size_t n = G->order; std::size_t k;
	std::size_t nnz_size = G->nnz_size;
	double *max_c = (double *)malloc(sizeof(double)*n);max_c--;
	for(k=1;k<=n;k++){
		/*Find the maximum in the column*/
		max_c[k] = 0;
	}
	//use absolute value of the elements
	for(k=1;k<=nnz_size;k++){
		if(std::abs(val[k]) > max_c[colind[k]]){
			max_c[colind[k]] = std::abs(val[k]);
		}
	}
#if 0
	for(k=1;k<=n;k++){
		printf("max in col %u is %lf \n",k,max_c[k]);
	}
#endif

	/*Update*/
	for(k=1;k<=nnz_size;k++){
		//if val[k] = 0, handle the case
		val[k] = log(max_c[colind[k]]) - log(fabs(val[k]));
	}
	free(++max_c);
}

extern int *perm;


#ifndef NO_UNIT_TEST 
int main(int argc,char** argv){
	FILE *ptr = NULL; unsigned int i;
	SparseGraph *G = NULL;
	Match_t *m = NULL;
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
		std::size_t count=0;
		std::size_t mid;
		std::size_t *m1 = m->m; m1--;
		while(fscanf(mfile,"%u",&mid)==1){
			count++;
			m1[count] = mid;
		}
	}
	LogTransform(G);
	WeightedMatching(m,G);
	/*Now call the MC64*/
	MC64Driver(argc,argv);

	printf("Verifying the permutation\n");

	for(i=0;i<G->order;i++){
	//	printf("%d %d\n",(i+1),(m->m)[i]);
		printf("%u(%d) ",(m->m)[i],perm[i]);
		if(perm[i]==(int)(m->m)[i]){
			continue;
		}else{
			printf("FAILED\n");
			exit(1);
		}
	}
	printf("\nSUCCESS\n");
	printf("\n");
}
#endif
