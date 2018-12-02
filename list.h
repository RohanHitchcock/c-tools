typedef struct node node_t;

struct node {
    node_t *next;     /*pointer to the next node*/
    void *data;       /*anon data pointer*/
};

typedef struct {
    node_t *head;    /*first item in list*/
    node_t *foot;    /*last item in list*/
    int nvals;
} list_t;


list_t *make_empty_list(void);

int list_size(list_t *list);

void free_list(list_t *list);

list_t *list_insert_head(list_t *list, void *data);

list_t *list_insert_foot(list_t *list, void *data);

void list_process(list_t *list, void action(void*));

void *list_pop(list_t *list, void *key, int (*cmp)(void*, void*));

list_t *filter_list(list_t *list, int filter(void*));

void *list_find_mtf(list_t *list, void *key, int (*cmp)(void*, void*));
