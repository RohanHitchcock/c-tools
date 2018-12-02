typedef struct queue queue_t;

/*creates a new empty queue*/
queue_t *make_empty_queue(int initial_size);

/*returns the number of items in the queue*/
int queue_nvals(queue_t *queue);

/*adds a new item to the queue*/
queue_t *enqueue(queue_t *queue, void *new_item);

/*removes the item at the front of the queue*/
void *dequeue(queue_t *queue);

/*returns the item at the front of the queue without removing it*/
void *queue_peek(queue_t *queue);

/*processes every item in the queue in queue ordering*/
void queue_process(queue_t *queue, void (*action)(void*));

/*frees the queue structure*/
void queue_free(queue_t *queue);
