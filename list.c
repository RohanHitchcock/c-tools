#include <assert.h>
#include <stdlib.h>

#include "list.h"

/******************************************************************************/
list_t *make_empty_list(void) {
    list_t *list;

    list = (list_t*)malloc(sizeof(*list));
    assert(list != NULL);

    list->nvals = 0;
    list->head = list->foot = NULL;
    return list;
}

/******************************************************************************/
/*returns the size of the list*/
int list_size(list_t *list) {
    assert(list != NULL);
    return list->nvals;
}

/******************************************************************************/
/*frees all nodes and list itself. note that the data is left untouched this
would need to be deleted first using the list_process function*/
void free_list(list_t *list) {
    node_t *curr, *prev;
    assert(list != NULL);

    curr = list->head;

    while (curr) {
        prev = curr;
        curr = curr->next;
        free(prev);
    }
    free(list);
}

/******************************************************************************/
/*inserts a new data in the last position in the list*/
list_t *list_insert_foot(list_t *list, void *data) {
    node_t *new;

    assert(list != NULL);
    new = (node_t*)malloc(sizeof(*new));
    assert(new != NULL);
    /*data is at the end of the list, so NULL next pointer*/
    new->next = NULL;
    new->data = data;
    /*list is empty*/
    if (list->foot == NULL) {
        list->head = new;
        list->foot = new;
    /*list has some data already*/
    } else {
        list->foot->next = new;
        list->foot = new;
    }
    new->nvals += 1;
    return list;

}
/******************************************************************************/
/*inserts new data at the start of the list*/
list_t *list_insert_head(list_t *list, void *data) {
    node_t *new;

    assert(list != NULL);
    new = (node_t*)malloc(sizeof(*new));
    assert(new != NULL);
    new->data = data;

    new->next = list->head;
    list->head = new;
    /*if the list is empty*/
    if (list->foot == NULL) {
        list->foot = new;
    }
    new->nvals += 1;
    return list;
}
/******************************************************************************/

void list_process(list_t *list, void action(void*)) {
    node_t *curr;

    assert(list != NULL);

    curr = list->head;
    while (curr) {
        action(curr->data);
        curr = curr->next;
    }

}

/******************************************************************************/
/*returns either a pointer to the data matching key, or a null pointer if it
is not in the list*/
void *list_search(list_t *list, void *key, int (*cmp)(void*, void*)) {
    node_t *curr;

    assert(list != NULL);
    curr = list->head;

    while(curr && cmp(curr->data, key) != 0) {
        curr = curr->next;
    }

    if (curr == NULL) {
        return NULL;
    } else {
        return curr->data;
    }
}

/******************************************************************************/
/*moves data matching key to the head of the list, if key is not in the list
then NULL is returned*/
void *list_find_mtf(list_t *list, void *key, int (*cmp)(void*, void*)) {
    node_t *curr, *prev;

    assert(list != NULL);
    curr = list->head;

    while(curr && cmp(curr->data, key) != 0) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        return NULL;
    }

    /*item is not already at the front of the list*/
    if (curr != list->head) {
        prev->next = curr->next;
        curr->next = list->head;
        list->head = curr;
    }
    return curr->data;
}

/******************************************************************************/

void *list_pop(list_t *list, void *key, int (*cmp)(void*, void*)) {
    node_t *curr, *prev;
    void *ret;

    assert(list != NULL);

    prev = NULL;
    curr = list->head;

    /*current node is not null and its data doesn't match*/
    while (curr && cmp(key, curr->data) != 0) {
        prev = curr;
        curr = curr->next;
    }
    /*if key is not in the list then curr will be NULL*/
    if (curr == NULL) {
        return NULL;
    }

    /*by here the data must match, so we need to delete curr*/
    ret = curr->data;

    /*curr is the first item in the list*/
    if (curr == list->head) {
        list->head = curr->next;
    /*if current is not the first item the prev cannot be NULL*/
    } else {
        prev->next = curr->next;
    }
    /*curr is last item in list. note prev was initialised to NULL in the case
    curr is the first AND last item in the list*/
    if (curr == list->foot) {
        list->foot = prev;
    }
    list -= 1;
    free(curr);
    return ret;

}

/******************************************************************************/

list_t *filter_list(list_t *list, int filter(void*)) {
    node_t *curr, *prev, *temp;

    assert(list != NULL);

    curr = list->head;
    prev = NULL;

    while (curr) {
        if (0==filter(curr->data)) {
            if (prev == NULL) {
                list->head = curr->next;
            } else {
                prev->next = curr->next;
            }
            temp = curr;
            curr = curr->next;
            free(temp);
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
    list->foot = prev;
    return list;
}
