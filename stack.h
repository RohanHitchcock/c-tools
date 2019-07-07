typedef struct stack stack_t;

/*create a new empty stack. inital_size specifies the intial memory reserved for
data in the stack*/
stack_t *make_empty_stack(int inital_size);

/*returns the number of items in the stack*/
int stack_nvals(stack_t *stack);

/*pushes a new item onto the stack*/
stack_t *stack_push(stack_t *stack, void *new_item);

/*removes the item on top of the stack*/
void *stack_pop(stack_t *stack);

/*returns the item on top of the stack without removing it*/
void *stack_peek(stack_t *stack);

/*applies 'action' to every item in the stack (in stack order)*/
void stack_process(stack_t *stack, void (*action)(void*));

/*frees the stack structure*/
void stack_free(stack_t *stack);
