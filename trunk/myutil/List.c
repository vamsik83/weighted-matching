#include "List.h"
#include<stdlib.h>
#include<malloc.h>
#include<stdio.h>
#include<assert.h>

void SortedInsertList(List **ptr,void *data,
	char (*list_compare)(void *,void *)){
	List *new_node = NULL;
	List *itr = *ptr;
	(new_node) = (List *) malloc(sizeof(List)*1);
	assert(new_node != NULL);
	if(!*ptr){
		(new_node)->next = NULL;
		*ptr = new_node;
		new_node->_data = data;
		return;
	}
	while(itr->next && 
		list_compare(itr->_data,data)){
		itr = itr->next;
	}
	new_node->_data = data;
	new_node->next = itr->next;
	itr->next = new_node;

	if(!list_compare((itr)->_data,data)){
		new_node->_data = (itr)->_data;
		(itr)->_data = data;
	}
}
void InsertList(char type,List **ptr,void *_data){

	List *node = (List *) malloc(sizeof(List)*1);
//	List *node = (List *) calloc(1,sizeof(List));
	List *itr;
	if(!node){
		fprintf(stderr,"Unable to create a node in the list\n");
		exit(1);
	}
	if(!(*ptr)){
		*ptr = node;
		node->_data = _data;
		(*ptr)->next = NULL;
		return;
	}
	node->next = (*ptr)->next;
	(*ptr)->next = node;
	if(type == FIRST){
		node->_data = (*ptr)->_data;
		(*ptr)->_data = _data;
	}else{
		itr = (*ptr)->next;
		while(itr->next){
			itr->_data = (itr->next)->_data;
			itr = itr->next;
		}
		itr->_data = _data;
	}
}

void PrintList(List *ptr){
	while(ptr){
		printf("%p\n",(void *)ptr->_data);
		ptr=ptr->next;
	}
}
/*Call free data to free up _data if its not null
 */
void FreeList(List *ptr,void (*free_data)(void *)){
	List *tmp;
	while(ptr){
		if(free_data){
			free_data(ptr->_data);
		}
		tmp = ptr;
		ptr = ptr->next;
		free(tmp);
	}
}
#ifdef _UNIT_TEST_LIST
#include<stdlib.h>
char my_compare(void *a, void *b){
	if(*((int *)a) < *((int *)b)){
		return 1;
	}else{
		return 0;
	}
}
int main(){
	List *l = NULL;
	int *insert_data = NULL;
	char i;
	/*Should have some garbage value which we want 
	 *to use for our seed
	 */
	int my_seed;
	srand(my_seed);
	for(i=0;i<10;i++){
		insert_data = (int *) malloc(sizeof(int)*1);
		*insert_data = rand()%100; 
		SortedInsertList(&l,insert_data,
		my_compare);
	}
	
	while(l){
		printf("%d->",*((int *)l->_data));
		l = l->next;
	}
}
#endif
