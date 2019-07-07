/*Array-based polymorphic heap module

written by Rohan Hitchcock <rhitchcock@student.unimelb.edu.au>
made with reference to
    Programing, Problem Solving, and Abstraction with C 2nd edition
    Alistair Moffat
    IBSN: 9781486010974
*/

typedef struct {
    /*array of pointers to data*/
    void **data;
    /*number of valid pointer values in the array*/
    int nvals;
    /*size of the array (not all values may be valid)*/
    int size;
    /*comparison function that defines how the heap is ordered*/
    int (*cmp)(void*, void*);
} heap_t;

/*creat a new new empty heap, returning a pointer to it*/
heap_t *make_empty_heap(int (*cmp)(void*,void*), int initial_size);

/*inserts a new item into a heap*/
heap_t *heap_insert(heap_t *h, void *data);

/*removes item at the top of the heap and returns a pointer to its data
returns NULL if heap is empty*/
void *heap_pull(heap_t *h);

/*looks at the data of the item on the top of the heap, without removing it
returns NULL if heap is empty*/
void *heap_peek(heap_t *h);

/*frees the heap structure, but not the stored data*/
void free_heap(heap_t *h);

/*updates heap by swapping a parent with one of its children, and recurses
until the ordering is correct*/
void sift_down(heap_t *h, int p);

/*updates heap by swapping a child with its parent, and recurses until ordering
is correct*/
void sift_up(heap_t *h, int child);

/*builds the data stored in h into a heap.
Enforces heap property*/
void build_heap(heap_t *h);

/*sorts the data stored in h (as defined by cmp(void*,void*)).
Breaks heap property*/
void heap_sort(heap_t *h);

/*performs the function 'action' on every data element in the heap*/
void process_heap(heap_t *heap, void (*action)(void*));

/*replaces the root of the heap with new_root. returns a pointer to the data
of the old root. will cause an error if used on an empty heap*/
void *heap_swap_root(heap_t *h, void *new_root);
