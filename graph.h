typedef struct {
    void *data;
    void *temp;
    int n_edges;
    int size_edges;
    edge_t *edges;
} vertex_t;

typedef struct {
    void *data;
    vertex_t *dest;
} edge_t;

typedef struct {
    int size;
    int n_v;
    vertex_t *v;
} graph_t;
