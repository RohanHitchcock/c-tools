/*Array-based polymorphic heap module

written by Rohan Hitchcock <rhitchcock@student.unimelb.edu.au>
made with reference to
    Programing, Problem Solving, and Abstraction with C 2nd edition
    Alistair Moffat
    IBSN: 9781486010974
*/

#include <assert.h>
#include <stdlib.h>
#include "heap.h"

/*the multiplicitive rate the data array grows by*/
#define GROWTH_RATE 2

/*swaps two pointers in an array*/
static void voidswap(void **p1, void **p2);

/*****************************************************************************/
/*makes an empty heap*/
heap_t *make_empty_heap(int (*cmp)(void*,void*), int initial_size) {
    heap_t *h;

    /*make space for the heap*/
    h = (heap_t*)malloc(sizeof(*h));
    assert(h != NULL);

    h->nvals = 0;
    h->size = initial_size;
    h->cmp = cmp;

    /*make space for the data*/
    h->data = (void**)malloc(h->size*sizeof(*(h->data)));
    assert(h->data != NULL);

    return h;
}

/*****************************************************************************/
/*inserts a new item into the heap*/
heap_t *heap_insert(heap_t *h, void *data) {

    /*grows the heap if there is no space avalible*/
    if (h->nvals == h->size) {
        h->size *= GROWTH_RATE;
        h->data = (void**)realloc(h->data, h->size*sizeof(*h));
        assert(h->data != NULL);
    }

    /*inserts the data at the end of heap and sifts up*/
    h->data[h->nvals++] = data;
    sift_up(h, h->nvals - 1);
    return h;
}
/*****************************************************************************/
/*gets the first item on the heap without changing the heap, returns NULL if
the heap is empty*/
void *heap_peek(heap_t *h) {
    if (h->nvals == 0) {
        return NULL;
    } else {
        return h->data[0];
    }
}
/*****************************************************************************/
/*removes the first item from the heap and returns a pointer to it, returns
null if the heap is empty*/
void *heap_pull(heap_t *h) {
    void *ret;

    if (h->nvals == 0) {
        return NULL;
    }
    ret = h->data[0];
    voidswap(h->data+0, h->data+h->nvals-1);
    h->nvals -= 1;
    sift_down(h, 0);

    return ret;
}

/*****************************************************************************/
/*frees the heap structure, but not the stored data*/
void free_heap(heap_t *h) {
    /*frees array*/
    free(h->data);
    /*frees remainder of heap structure*/
    free(h);
}


/*****************************************************************************/
/*updates heap by swapping a parent with one of its children, and recurses
until the ordering is correct*/
void sift_down(heap_t *h, int p) {
    int child;

    /*children are at 2p+1 and 2p+2*/
    if ((child = 2*p + 1) < h->nvals) {

        /*if the other child exists and is bigger*/
        if (child + 1 < h->nvals && h->cmp(h->data[child], h->data[child + 1]) < 0) {
            child += 1;
        /*child is now the largest of the two children, if it its bigger than
        the parent then swap the two and sift down on the swapped element*/
        }

        if (h->cmp(h->data[p], h->data[child]) < 0) {
            voidswap(h->data + p, h->data + child);
            sift_down(h, child);
        }

    }
}

/******************************************************************************/
/*updates heap by swapping a child with its parent, and recurses until ordering
is correct*/
void sift_up(heap_t *h, int child) {
    /*the parent is at (c-1)/2 (floor division)*/
    int p=(child-1)/2;

    if (p < 0) {
        return;
    }
    /*swaps data and sifts up again if the child is greater than its parent*/
    if(h->cmp(h->data[child], h->data[p]) > 0) {
        voidswap(h->data+child, h->data+p);
        sift_up(h, p);
    }
}

/******************************************************************************/
/*builds the data stored in h into a heap.
Enforces heap property*/
void build_heap(heap_t *h) {
    int i;

    /*starting from the parent node farthest from the root, sift down on
    each node*/
    for (i=h->nvals/2-1; i>=0; i--) {
        sift_down(h, i);
    }
}

/*****************************************************************************/
/*sorts the data stored in h (as defined by cmp(void*,void*)).
Breaks heap property and assumes the data is currently a heap*/
void heap_sort(heap_t *h) {
    int i, temp;

    /*preserves the number of valid items as it will be overwritten*/
    temp = h->nvals;

    for (i=h->nvals - 1; i>0; i--) {
        /*swaps root of heap into last position then restores heap property
        on remainder of data*/
        voidswap(h->data + i, h->data);
        h->nvals -= 1;
        sift_down(h, 0);
    }
    h->nvals = temp;
}

/*****************************************************************************/
/*performs the function 'action' on every data element in the heap*/
void process_heap(heap_t *h, void (*action)(void*)) {
    int i;
    for (i=0; i < h->nvals; i++) {
        action(h->data[i]);
    }
}

/*****************************************************************************/
void *heap_swap_root(heap_t *h, void *new_root) {
    void *old_root;
    /*ensures heap has a root to swap*/
    assert(h->nvals > 0);
    old_root = h->data[0];
    h->data[0] = new_root;
    sift_down(h, 0);
    return old_root;
}

/*****************************************************************************/
/*swaps the values at p1 and p2, which are each anonymous pointers*/
static void voidswap(void **p1, void **p2) {
    void *temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}
