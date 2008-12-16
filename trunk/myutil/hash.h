/* $RCSfile: hash.h,v $$Revision: 1.1.1.1 $$Date: 2008/09/16 21:45:44 $
 *
 *    Copyright (c) 1991-2001, Larry Wall
 *
 *    You may distribute under the terms of either the GNU General Public
 *    License or the Artistic License, as specified in the README file.
 *
 * $Log: hash.h,v $
 * Revision 1.1.1.1  2008/09/16 21:45:44  vamsik
 *
 *
 * Importing into the CVS the developed code base at Ansoft
 *
 * Revision 1.1.1.1  2008/01/31 02:20:14  vamsik
 *
 * Importing myutil package fixed the bug in RandQsort.c
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
 /**
  * Got this from perl source code of hash implementation,
  * since I saw that perl handles hashes in a great manner
  * I thought I'll plugin the hash implementation here.
  * NOTE: I found that that perl is not doing better than the
  * the direct chaining based hash scheme where you create 
  * 'N' Buckets and do a key%N and use the linked list if 
  * collisions occur, The expected size of each collison list
  * |S|/N where |S| is the #of elements.
  *
  * How to use this interface??
  * HASH *my_hash = HNEW();
  * hstore(my_hash,key_string,value_void_star);
  * hfetch(my_hash,key_string);
  *	size = hiterinit(my_hash);
  *	printf("The new size is %d\n",size);
  *	for(i=0;entry=(HENT *)hiternext(my_hash);i++){
  */
#ifndef _HASH_H
#define _HASH_H
#include <stdlib.h>
#define FILLPCT 60		/* don't make greater than 99 */
#define safemalloc malloc
#define safecalloc calloc
#define saferealloc realloc
#define safefree	free
#define DOINIT
#define bool char
#define FALSE 0
#define TRUE 1
#define Nullstr NULL

#define STR void

typedef struct hentry HENT;

struct hentry {
    HENT	*hent_next;
    char	*hent_key;
    STR		*hent_val;
    int		hent_hash;
};

struct htbl {
    HENT	**tbl_array;
    int		tbl_max;
    int		tbl_fill;
    int		tbl_riter;	/* current root of iterator */
    HENT	*tbl_eiter;	/* current entry of iterator */
};
#define strNE(a,b) strcmp(a,b)
typedef struct htbl HASH;
bool hdelete (HASH *tb, char *key);
STR * hfetch ( HASH *tb, char *key );
int hiterinit ( HASH *tb );
char * hiterkey ( HENT *entry );
HENT * hiternext ( HASH *tb );
STR * hiterval ( HENT *entry );
HASH * hnew ( void );
void hsplit ( HASH *tb );
bool hstore ( HASH *tb, char *key, STR *val );
#endif
