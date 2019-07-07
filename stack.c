#include <assert.h>
#include <stdlib.h>

#include "stack.h"

#define GROWTH_RATE 2

struct stack {
    void **data;
    int nvals;
    int size;
};

/******************************************************************************/
stack_t *make_empty_stack(int initial_size) {
    stack_t *new_stack;

    new_stack = (stack_t*)malloc(sizeof(*new_stack));
    assert(new_stack);

    new_stack->size = initial_size;

    new_stack->data = malloc(new_stack->size*sizeof(*new_stack->data));
    assert(new_stack->data);

    new_stack->nvals = 0;

    return new_stack;
}

/******************************************************************************/
int stack_nvals(stack_t *stack) {
    return stack->nvals;
}

/******************************************************************************/
stack_t *stack_push(stack_t *stack, void *new_item) {
    if (stack->size == stack->nvals) {
        stack->size *= GROWTH_RATE;
        stack->data = realloc(stack->data, stack->size*sizeof(*stack->data));
        assert(stack->data);
    }

    stack->data[stack->nvals++] = new_item;

    return stack;
}

/******************************************************************************/
void *stack_pop(stack_t *stack) {
    if (stack->nvals == 0) {
        return NULL;
    }

    stack->nvals -= 1;

    return stack->data[stack->nvals];
}

/******************************************************************************/

void *stack_peek(stack_t *stack) {
    if (stack->nvals == 0) {
        return NULL;
    }

    return stack->data[stack->nvals-1];
}

/******************************************************************************/
void stack_process(stack_t *stack, void (*action)(void*)) {
    int i;

    for (i = stack->nvals - 1; i >= 0; i--) {
        action(stack->data[i]);
    }
}

/******************************************************************************/
void stack_free(stack_t *stack) {
    free(stack->data);
    free(stack);
}
