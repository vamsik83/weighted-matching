#ifndef LIST_H
#define LIST_H
typedef struct _list_ {
	void *_data;
	struct _list_ *next;
} List;
#define FIRST 1
#define LAST 0
void InsertList(char type,List **,void *_data);
/*A Call back has to be provided by the caller*/
/*Note: bool compare(void *a,void *b)
 *This will return**/
void SortedInsertList(List **,void *,
	char (*)(void *,void *));
void FreeList(List*,void (*)(void *));
#endif
