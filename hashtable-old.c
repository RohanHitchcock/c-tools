#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "list.c"

#define NUM_HASH_VALS 20
#define GROWTH_RATE 2
#define ITEMS_SIZE_RATIO 2

typedef struct {
	int num_hash_vals;
	int *hash_vals;
	int size;
    int nvals;
    list_t **table;
} hashtable_t;


static int hash(hashtable_t *h, char *key);
static void init_hash_vals(hashtable_t *h);
hashtable_t *make_table(int size);
hashtable_t *hashtable_insert(hashtable_t *h, char **item);
char **hashtable_lookup(hashtable_t *h, char **key);
char **hashtable_pull(hashtable_t *h, char **key);
void hashtable_process(hashtable_t *h, void action(void*));
void hashtable_free(hashtable_t *h);
int hashtable_num_items(hashtable_t *h);

int nextprime(int n);
int stringcmp(void *v1, void *v2);
int isprime(int n);

/******************************************************************************/

/*based of moffat*/
static void
init_hash_vals(hashtable_t *h) {
    int i;

    for (i=0; i<h->num_hash_vals; i++) {
        h->hash_vals[i] = nextprime(h->size + rand()%h->size);
    }
}

/******************************************************************************/
/*based off moffat*/
hashtable_t
*make_table(int size) {
    hashtable_t *h;
    int i;

    h = malloc(sizeof(*h));
    assert(h!=NULL);

    h->hash_vals = (int*)malloc(NUM_HASH_VALS*sizeof(*(h->hash_vals)));
    assert(h->hash_vals != NULL);

    h->table = (list_t**)malloc(size*sizeof(*(h->table)));
    assert(h->table != NULL);

    h->num_hash_vals = NUM_HASH_VALS;
    h->size = size;

    /*sets all lists to NULL*/
    for (i=0; i<h->size; i++) {
        h->table[i] = make_empty_list();
    }

    init_hash_vals(h);


    h->nvals = 0;
    return h;
}

/******************************************************************************/
/*based of moffat*/
static int hash(hashtable_t *h, char *key) {
    int i, k=0, hval=0;

    for(i=0; key[i]!='\0'; i++) {
        hval += key[i] * h->hash_vals[k];
		k += 1;
		if (k == h->num_hash_vals) {
			k = 0;
		}
    }
	return hval % h->size;
}

/******************************************************************************/

hashtable_t
*hashtable_insert(hashtable_t *h, char **item) {
    int i;

    i = hash(h, *item);

	if (!list_move_to_head(h->table[i], item, stringcmp)) {
		h->table[i] = list_insert_at_head(h->table[i], item);
		h->nvals += 1;
	}

    return h;
}


/******************************************************************************/

char
**hashtable_lookup(hashtable_t *h, char **key) {

	return list_move_to_head(h->table[hash(h, *key)], key, stringcmp);
}

/******************************************************************************/

char
**hashtable_pull(hashtable_t *h, char **key) {
	char **result;
	result = list_pop(h->table[hash(h, *key)], key, stringcmp);
	if (result) {
		h->nvals -= 1;
	}
	return result;
}


/******************************************************************************/
void
hashtable_process(hashtable_t *h, void action(void*)) {
	int i;

	for (i=0; i < h->size; i++) {
		list_process(h->table[i], action);
	}
}
/******************************************************************************/

void hashtable_free(hashtable_t *h) {
	int i;

	for (i=0; i < h->size; i++) {
		free_list(h->table[i]);
	}

	free(h);
}

/******************************************************************************/

int hashtable_num_items(hashtable_t *h) {
	return h->nvals;
}

/******************************************************************************/


/*comparison functions for anonymous data pointers*/
int stringcmp(void *v1, void *v2) {
    char **s1 = v1, **s2 = v2;
    return strcmp(*s1, *s2);
}



/******************************************************************************/
/*from Alistair Moffat in hashing_moffat.c*/

/* A couple of auxiliary functions */
int
isprime(int n) {
	int divisor;
	if (n<2) {
		return 0;
	}
	for (divisor=2; divisor*divisor<=n; divisor++) {
	       if (n%divisor==0) {
		       /* factor found, so can't be prime */
		       return 0;
		}
	}
	/* no factors, so must be prime */
	return 1;
}

int
nextprime(int n) {
	n = n+1;
	while (!isprime(n)) {
		n = n+1;
	}
	return n;
}

/******************************************************************************/
/*indicated functions based of alistair moffat*/
/* =====================================================================
   Program written by Alistair Moffat, as an example for the book
   "Programming, Problem Solving, and Abstraction with C", Pearson
   Custom Books, Sydney, Australia, 2002; revised edition 2012,
   ISBN 9781486010974.

   See http://people.eng.unimelb.edu.au/ammoffat/ppsaa/ for further
   information.

   Prepared December 2012 for the Revised Edition.
   ================================================================== */
