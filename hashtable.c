#include <assert.h>
#include <stdlib.h>

#include "hashtable.h"

typedef struct bucket bucket_t;

struct bucket {
    void *key;
    void *data;
    bucket_t *next;
};

struct hashtbl {
    bucket_t **table;
    int size;
    int nvals;
    void *h_data;
    unsigned int (*hash)(void*, void*);
    int (*cmp)(void*, void*);
};

/*creates a new bucket*/
bucket_t *create_bucket(void *key, void *data, void *(*new_key)(void*));

/*frees the bucket, returning the data*/
void *free_bucket(bucket_t *bucket, void (*free_key)(void*));

/*functions for the hash table************************************************/
hashtbl_t *create_hashtbl(int size, unsigned int (*hash)(void*,void*), void* h_data, int (*cmp)(void*,void*)) {
    int i;
    hashtbl_t *hashtbl;

    hashtbl = (hashtbl_t*)malloc(sizeof(*hashtbl));
    assert(hashtbl != NULL);

    hashtbl->size = size;
    hashtbl->table = malloc(hashtbl->size*sizeof(*hashtbl->table));
    assert(hashtbl != NULL);

    for (i=0; i < hashtbl->size; i++) {
        hashtbl->table[i] = NULL;
    }

    hashtbl->nvals = 0;
    hashtbl->h_data = h_data;
    hashtbl->hash = hash;
    hashtbl->cmp = cmp;

    return hashtbl;
}

/*****************************************************************************/
void *hashtbl_get(hashtbl_t *hashtbl, void *key) {
    unsigned int h;
    bucket_t *curr_bucket, *prev_bucket;

    h = hashtbl->hash(key, hashtbl->h_data);

    curr_bucket = hashtbl->table[h];
    prev_bucket = NULL;

    while (curr_bucket) {
        if (0 == hashtbl->cmp(key, curr_bucket->key)) {
            /*move to front*/
            if (prev_bucket) {
                prev_bucket->next = curr_bucket->next;
                curr_bucket->next = hashtbl->table[h];
                hashtbl->table[h] = curr_bucket;
            }
            return curr_bucket->data;
        }
        prev_bucket = curr_bucket;
        curr_bucket = curr_bucket->next;
    }

    /*key is not in hashtable*/
    return NULL;
}

/******************************************************************************/
void *hashtbl_insert(hashtbl_t *hashtbl, void *key, void *data, void *(*new_key)(void*)) {
    unsigned int h;
    bucket_t *new_bucket, *curr_bucket, *prev_bucket;

    hashtbl->nvals += 1;

    h = hashtbl->hash(key, hashtbl->h_data);
    curr_bucket = hashtbl->table[h];
    prev_bucket = NULL;

    /*checks if key is in hash table*/
    while (curr_bucket) {

        if (0 == hashtbl->cmp(key, curr_bucket->key)) {

            /*move to front*/
            if (prev_bucket) {
                prev_bucket->next = curr_bucket->next;
                curr_bucket->next = hashtbl->table[h];
                hashtbl->table[h] = curr_bucket;
            }
            /*returns data if key is already in the hashtable*/
            return curr_bucket->data;
        }

        prev_bucket = curr_bucket;
        curr_bucket = curr_bucket->next;

    }

    /*key is not in hash table, so insert at front of bucket list*/
    new_bucket = create_bucket(key, data, new_key);
    new_bucket->next = hashtbl->table[h];
    hashtbl->table[h] = new_bucket;

    /*NULL return indicates sucessful insertion*/
    return NULL;
}

/*****************************************************************************/
void *hashtbl_delete(hashtbl_t *hashtbl, void *key, void (*free_key)(void*)) {
    void *ret_data;
    unsigned int h = hashtbl->hash(key, hashtbl->h_data);
    bucket_t *curr_bucket, *prev_bucket;

    curr_bucket = hashtbl->table[h];
    prev_bucket = NULL;

    while (curr_bucket) {
        if (0 == hashtbl->cmp(key, curr_bucket->key)) {
            if (prev_bucket) {
                prev_bucket->next = curr_bucket->next;
            } else {
                hashtbl->table[h] = curr_bucket->next;
            }
            hashtbl->nvals -= 1;
            ret_data = free_bucket(curr_bucket, free_key);
            return ret_data;
        }
        prev_bucket = curr_bucket;
        curr_bucket = curr_bucket->next;

    }

    /*key is not in hash table*/
    return NULL;
}

/*****************************************************************************/
void hashtbl_free(hashtbl_t *hashtbl, void (*free_key)(void*), void (*free_data)(void*), void (*free_h_data)(void*)) {
    int i;
    bucket_t *curr_bucket;

    for (i=0; i < hashtbl->size; i++) {
        curr_bucket = hashtbl->table[i];
        while (curr_bucket) {
            hashtbl->table[i] = curr_bucket->next;
            free_data(free_bucket(curr_bucket, free_key));
            curr_bucket = hashtbl->table[i];
        }
    }
    free_h_data(hashtbl->h_data);
    free(hashtbl->table);
    free(hashtbl);
}

/*****************************************************************************/
void hashtbl_process(hashtbl_t *hashtbl, void (*action)(void*, void*)) {
    int i;
    bucket_t *curr;

    for (i=0; i < hashtbl->size; i++) {
        curr = hashtbl->table[i];
        while (curr) {
            action(curr->key, curr->data);
            curr = curr->next;
        }

    }
}

/*****************************************************************************/
int hashtbl_size(hashtbl_t *hashtbl) {
    return hashtbl->size;
}

/*****************************************************************************/
int hashtbl_nvals(hashtbl_t *hashtbl) {
    return hashtbl->nvals;
}
/*hash functions**************************************************************/
unsigned int xor_hash(void *vkey, void *h_data) {
	char *key = vkey;
    unsigned int h = ((xor_data_t*)h_data)->seed;
    int i, size = ((xor_data_t*)h_data)->size;

	for (i = 0; key[i] != '\0'; i++) {
		h = h ^ ((h << 5) + key[i] + (h >> 2));
	}

	return h % size;
}

/*bucket helper functions*****************************************************/
bucket_t *create_bucket(void *key, void *data, void *(*new_key)(void*)) {
    bucket_t *bucket;

    assert(key != NULL);
    /*data may not be NULL since a null return is used to indicate no data*/
    assert(data != NULL);

    bucket = (bucket_t*)malloc(sizeof(*bucket));
    assert(bucket);

    /*key is copied so it cannot be changed from outside this library*/
    bucket->key = new_key(key);

    bucket->data = data;

    return bucket;
}

/*****************************************************************************/
void *free_bucket(bucket_t *bucket, void (*free_key)(void*)) {
    void *bucket_data = bucket->data;
    free_key(bucket->key);
    free(bucket);
    return bucket_data;
}
