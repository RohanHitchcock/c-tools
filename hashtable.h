typedef struct hashtbl hashtbl_t;

/*data types for hash functions*/
typedef struct {
    unsigned int seed;
    int size;
} xor_data_t;

/*creates a new hash table. */
hashtbl_t *create_hashtbl(int size, unsigned int (*hash)(void*,void*), void* h_data, int (*cmp)(void*,void*));

/*gets the data associated with key from the hashtable, or NULL if the key is
not in the hash table*/
void *hashtbl_get(hashtbl_t *hashtbl, void *key);

/*deletes the key from the hash table and returns its data. returns NULL if the
key is not in the hash table*/
void *hashtbl_delete(hashtbl_t *hashtbl, void *key, void (*free_key)(void*));

/*inserts key into the hash table. NULL return indicates the key has been
sucessfully inserted. If the key is in the hash table, no changes are made and
its data is returned*/
void *hashtbl_insert(hashtbl_t *hashtbl, void *key, void *data, void *(*new_key)(void*));

/*frees all data*/
void hashtbl_free(hashtbl_t *hashtbl, void (*free_key)(void*), void (*free_data)(void*), void (*free_h_data)(void*));

void hashtbl_process(hashtbl_t *hashtbl, void (*action)(void*, void*));

/*returns the size of the hash table*/
int hashtbl_size(hashtbl_t *hashtbl);

/*returns the number of values stored in the hash table*/
int hashtbl_nvals(hashtbl_t *hashtbl);

/*hash functions*/
unsigned int xor_hash(void *vkey, void *h_data);
