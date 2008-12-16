#include<stdio.h>
/*Items to be permuted*/
unsigned int *data_items;
unsigned int *perm;
typedef char (*SwapPair)(void *,void *);

/*Writes a 0 into the permutation destroys it*/
void Permute(unsigned int *perm, unsigned int *data_items, unsigned int n){
	unsigned int orbit_start=0;
	unsigned int next=0;
	unsigned int popped;
	unsigned int pindex=0;
	unsigned int temp;
	unsigned int orbit_stack[n];
	unsigned int orbit_stack_index=0;

	popped = data_items[0];
	while(next < n){
		if(perm[pindex] == n+1){
			next++;
			pindex = next;
			popped = data_items[pindex];
			continue;
		}
		temp = data_items[perm[pindex]];
		data_items[perm[pindex]] = popped;
		popped = temp;
		temp = perm[pindex];
		perm[pindex] = n+1;
		pindex = temp;
	}

	unsigned int i;
	for(i=0;i<n;i++){
		printf("%u ",data_items[i]);
	}
}

void LinearFill(unsigned int n){
	unsigned int i;
	for(i=0;i<n;i++){
		data_items[i] = i;
	}
}

int main(int argc,char **argv){
	unsigned int n;
	unsigned int i;
	printf("Please enter n:");
	scanf("%u",&n);
	data_items = (unsigned int *)malloc(sizeof(unsigned int)*n);
	LinearFill(n);
	perm = (unsigned int *)malloc(sizeof(unsigned int)*n);
	printf("Please enter the permutation\n");
	for(i=0;i<n;i++){
		scanf("%u",&perm[i]);
	}
	Permute(perm,data_items,n);
}
