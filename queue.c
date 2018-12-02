#include <assert.h>
#include <stdlib.h>

#include "queue.h"

#define GROWTH_RATE 2

struct queue {
    void **data;
    int start;
    int end;
    int nvals;
    int size;
};

/******************************************************************************/
queue_t *make_empty_queue(int initial_size) {
    queue_t *queue;

    queue = (queue_t*)malloc(sizeof(*queue));
    assert(queue);

    queue->size = initial_size;

    queue->data = malloc(queue->size*sizeof(*queue->data));
    assert(queue->data);

    queue->nvals = 0;
    queue->start = 0;
    queue->end = 0;

    return queue;
}

/******************************************************************************/
int queue_nvals(queue_t *queue) {
    return queue->nvals;
}

/******************************************************************************/
queue_t *enqueue(queue_t *queue, void *new_item) {
    int i;

    if (queue->nvals == queue->size) {
        queue->size *= GROWTH_RATE;

        queue->data = realloc(queue->data, queue->size*sizeof(*queue->data));
        assert(queue->data);

        /*shifts items to maintain queue ordering*/
        for (i=0; i<queue->start; i++) {
            queue->data[queue->nvals + i] = queue->data[i];
        }
        queue->end = queue->start + queue->nvals;

    }

    queue->nvals += 1;

    queue->data[queue->end++] = new_item;
    if (queue->end == queue->size) {
        queue->end = 0;
    }

    return queue;
}

/******************************************************************************/
void *dequeue(queue_t *queue) {
    int return_index = queue->start;

    if (queue->nvals == 0) {
        return NULL;
    }

    queue->start += 1;
    if (queue->start == queue->size) {
        queue->start = 0;
    }

    queue->nvals -= 1;

    return queue->data[return_index];
}

/******************************************************************************/
void *queue_peek(queue_t *queue) {

    if (queue->nvals == 0) {
        return NULL;
    }

    return queue->data[queue->start];
}

/******************************************************************************/
void queue_process(queue_t *queue, void (*action)(void*)) {
    int count, i;

    i = queue->start;
    for (count=0; count < queue->nvals; count++) {
        action(queue->data[i++]);
        if (i == queue->size) {
            i = 0;
        }
    }
}

/*****************************************************************************/
void queue_free(queue_t *queue) {
    free(queue->data);
    free(queue);
}
