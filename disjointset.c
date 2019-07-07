#include <stdlib.h>
#include <assert.h>

struct disjoint_set {
    void *data;
    int rank;
    djset_t *next;
};

/*****************************************************************************/
djset_t *make_set(void *data) {
    djset_t *set;

    set = malloc(sizeof(*set));
    assert(set);

    set->next = NULL;
    set->data = data;
    set->rank = 0;

    return set;
}

/*****************************************************************************/
void *set_find(djset_t *set) {
    while (set->next) {
        set = set->next;
    }
    return set->data;
}

/*****************************************************************************/
void set_union(djset_t *set1, djset_t *set2) {
    while (set1->next) {
        set1 = set1->next;
    }
    while (set2->next) {
        set2 = set2->next;
    }

    /*already in the same set*/
    if (set1->data == set2->data) {
        return;
    }

    if (set1->rank < set2->rank) {
        set1->next = set2;
    } else if (set1->rank > set2->rank) {
        set2->next = set1;
    } else { /*ranks are equal*/
        set1->next = set2;
        set2->rank += 1;
    }
}
