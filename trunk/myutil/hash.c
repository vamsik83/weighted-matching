/* $RCSfile: hash.c,v $$Revision: 1.1.1.1 $$Date: 2008/09/16 21:45:44 $
 *
 *    Copyright (c) 1991-2001, Larry Wall
 *
 *    You may distribute under the terms of either the GNU General Public
 *    License or the Artistic License, as specified in the README file.
 *
 * $Log: hash.c,v $
 * Revision 1.1.1.1  2008/09/16 21:45:44  vamsik
 *
 *
 * Importing into the CVS the developed code base at Ansoft
 *
 * Revision 1.2  2008/05/25 19:58:44  vamsik
 *
 * Changing the RandQsort.h
 *
 * Revision 1.1.1.1  2008/01/31 02:20:14  vamsik
 *
 * Importing myutil package fixed the bug in RandQsort.c
 *
 * Revision 1.2  2007/07/08 07:11:35  vamsik
 *
 * Fixed the bug in pdb_format.c due to hstore in the hash
 *
 * Revision 1.1.1.1  2007/06/26 09:18:42  vamsik
 *
 *
 * import
 *
 * Revision 1.1.1.1  2007/06/01 04:08:04  vamsik
 *  June 01, 2007
 *  Restarted the SPICE2LAYOUT project
 *
 */
 /****
  * Added from perl's source code
  * to get a hash datastructure.
  * 21 Feb,2007 vamsi.krishnak@gmail.com
  * to unit test it -DUNIT_TEST_HASH
  */
#include<strings.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include <stdio.h>
#include "hash.h"
#ifdef DOINIT
char coeff[] = {
		61,59,53,47,43,41,37,31,29,23,17,13,11,7,3,1,
		61,59,53,47,43,41,37,31,29,23,17,13,11,7,3,1,
		61,59,53,47,43,41,37,31,29,23,17,13,11,7,3,1,
		61,59,53,47,43,41,37,31,29,23,17,13,11,7,3,1,
		61,59,53,47,43,41,37,31,29,23,17,13,11,7,3,1,
		61,59,53,47,43,41,37,31,29,23,17,13,11,7,3,1,
		61,59,53,47,43,41,37,31,29,23,17,13,11,7,3,1,
		61,59,53,47,43,41,37,31,29,23,17,13,11,7,3,1};
#endif

STR *
hfetch(register HASH *tb, char *key)
{
    register char *s;
    register int i;
    register int hash;
    register HENT *entry;

    if (!tb)
	return Nullstr;
    for (s=key,		i=0,	hash = 0;
      /* while */ *s;
	 s++,		i++,	hash *= 5) {
	hash += *s * coeff[i];
    }
    entry = tb->tbl_array[hash & tb->tbl_max];
    for (; entry; entry = entry->hent_next) {
	if (entry->hent_hash != hash)		/* strings can't be equal */
	    continue;
	if (strNE(entry->hent_key,key))	/* is this it? */
	    continue;
	return entry->hent_val;
    }
    return Nullstr;
}

bool
hstore(register HASH *tb, char *key, STR *val)
{
    register char *s;
    register int i;
    register int hash;
    register HENT *entry;
    register HENT **oentry;

    if (!tb)
	return FALSE;
    for (s=key,		i=0,	hash = 0;
      /* while */ *s;
	 s++,		i++,	hash *= 5) {
	hash += *s * coeff[i];
    }

    oentry = &(tb->tbl_array[hash & tb->tbl_max]);
    i = 1;

    for (entry = *oentry; entry; i=0, entry = entry->hent_next) {
	if (entry->hent_hash != hash)		/* strings can't be equal, necessary
		but not sufficient condition */
	    continue;
	if (strNE(entry->hent_key,key))	/* is this it? */
	    continue;
	/*NOSTRICT*/
/*
 *  Its the responsibility of the 
 *  user to free this.
	safefree(entry->hent_val);
 */
	entry->hent_val = val;
	return TRUE;
    }
    /*NOSTRICT*/
    entry = (HENT*) safemalloc(sizeof(HENT));

	entry->hent_key = (char *) malloc(sizeof(char)*
						(strlen(key)+2));
	assert(entry->hent_key!=NULL);
	sprintf(entry->hent_key,"%s",key);	
    /*entry->hent_key = savestr(key);*/
    entry->hent_val = val;
    entry->hent_hash = hash;
    entry->hent_next = *oentry;
    *oentry = entry;

    if (i) {				/* initial entry? */
	tb->tbl_fill++;
	if ((tb->tbl_fill * 100 / (tb->tbl_max + 1)) > FILLPCT)
	    hsplit(tb);
    }

    return FALSE;
}

bool
hdelete(register HASH *tb, char *key)
{
    register char *s;
    register int i;
    register int hash;
    register HENT *entry;
    register HENT **oentry;

    if (!tb)
	return FALSE;
    for (s=key,		i=0,	hash = 0;
      /* while */ *s;
	 s++,		i++,	hash *= 5) {
	hash += *s * coeff[i];
    }

    oentry = &(tb->tbl_array[hash & tb->tbl_max]);
    entry = *oentry;
    i = 1;
    for (; entry; i=0, oentry = &entry->hent_next, entry = entry->hent_next) {
	if (entry->hent_hash != hash)		/* strings can't be equal */
	    continue;
	if (strNE(entry->hent_key,key))	/* is this it? */
	    continue;
	safefree((char*)entry->hent_val);
	safefree(entry->hent_key);
	*oentry = entry->hent_next;
	safefree((char*)entry);
	if (i)
	    tb->tbl_fill--;
	return TRUE;
    }
    return FALSE;
}

void
hsplit(HASH *tb)
{
    int oldsize = tb->tbl_max + 1;
    register int newsize = oldsize * 2;
    register int i;
    register HENT **a;
    register HENT **b;
    register HENT *entry;
    register HENT **oentry;

    a = (HENT**) saferealloc((char*)tb->tbl_array, newsize * sizeof(HENT*));
    bzero((char*)&a[oldsize], oldsize * sizeof(HENT*)); /* zero second half */
    tb->tbl_max = --newsize;
    tb->tbl_array = a;

    for (i=0; i<oldsize; i++,a++) {
	if (!*a)				/* non-existent */
	    continue;
	b = a+oldsize;
	for (oentry = a, entry = *a; entry; entry = *oentry) {
	    if ((entry->hent_hash & newsize) != i) {
		*oentry = entry->hent_next;
		entry->hent_next = *b;
		if (!*b)
		    tb->tbl_fill++;
		*b = entry;
		continue;
	    }
	    else
		oentry = &entry->hent_next;
	}
	if (!*a)				/* everything moved */
	    tb->tbl_fill--;
    }
}

HASH *
hnew(void)
{
    register HASH *tb = (HASH*)safemalloc(sizeof(HASH));

    tb->tbl_array = (HENT**) safemalloc(8 * sizeof(HENT*));
    tb->tbl_fill = 0;
    tb->tbl_max = 7;
    hiterinit(tb);	/* so each() will start off right */
    bzero((char*)tb->tbl_array, 8 * sizeof(HENT*));
    return tb;
}

#ifdef NOTUSED
hshow(register HASH *tb)
{
    fprintf(stderr,"%5d %4d (%2d%%)\n",
	tb->tbl_max+1,
	tb->tbl_fill,
	tb->tbl_fill * 100 / (tb->tbl_max+1));
}
#endif

int
hiterinit(register HASH *tb)
{
    tb->tbl_riter = -1;
    tb->tbl_eiter = NULL;
    return tb->tbl_fill;
}

HENT *
hiternext(register HASH *tb)
{
    register HENT *entry;

    entry = tb->tbl_eiter;
    do {
	if (entry)
	    entry = entry->hent_next;
	if (!entry) {
	    tb->tbl_riter++;
	    if (tb->tbl_riter > tb->tbl_max) {
		tb->tbl_riter = -1;
		break;
	    }
	    entry = tb->tbl_array[tb->tbl_riter];
	}
    } while (!entry);

    tb->tbl_eiter = entry;
    return entry;
}

char *
hiterkey(register HENT *entry)
{
    return entry->hent_key;
}

STR *
hiterval(register HENT *entry)
{
    return entry->hent_val;
}


#ifdef UNIT_TEST_HASH
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
int main(){
	HASH *my_hash = hnew();
	unsigned char i;
	int *tmp = NULL;
	char *string_key;
	int size;
	static int change = -99;
	for(i=0;i<100;i++){
		tmp = (int *)malloc(sizeof(int)*1);
		*tmp = i;
		string_key = (char *) malloc(sizeof(char)*10);
		sprintf(string_key,"Num#%d",(int)i);
		if(hstore(my_hash,string_key,(void *)tmp)){
			fprintf(stderr,"warning::element exists\n");
		}
	}
	/*Print one by one*/	
	size = hiterinit(my_hash);
	printf("The old size is %d\n",size);
	HENT *entry =NULL; 
	for(i=0;entry=(HENT *)hiternext(my_hash);i++){
		printf("%s -> %d\n",hiterkey(entry),*((int *)hiterval(entry)));
	}
	printf("Inserts # %d\n",i);
	if(!hdelete(my_hash,"Num#10")){
		fprintf(stderr,"Hdelete element dont exist\n");
	}

	if(!hdelete(my_hash,"vamsi")){
		fprintf(stderr,"Hdelete element dont exist\n");
	}

	hstore(my_hash,"Num#0",(void *)&change);

	size = hiterinit(my_hash);
	printf("The new size is %d\n",size);

	for(i=0;entry=(HENT *)hiternext(my_hash);i++){
		printf("%s -> %d\n",hiterkey(entry),*((int *)hiterval(entry)));
	}
	printf("The new count is %d\n",i);
	printf("Testing hfetch\n");
	printf("The value of Num#90 is %d\n",*((int *)hfetch(my_hash,"Num#90")));

	printf("The value of Num#0 is %d\n",*((int *)hfetch(my_hash,"Num#0")));
	printf("The value of Num#19 is %d\n",*((int *)hfetch(my_hash,"Num#19")));
	printf("The value of Num#20 is %d\n",*((int *)hfetch(my_hash,"Num#20")));
	printf("The value of Num#1 is %d\n",*((int *)hfetch(my_hash,"Num#1")));
}
#endif
