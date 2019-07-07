typedef struct disjoint_set djset_t;

djset_t *make_set(void *data);

void *set_find(djset_t *set);

void set_union(djset_t *set1, djset_t *set2);
