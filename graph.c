#include <assert.h>
#include <stdlib.h>

#define EDGE_ARRAY_GROWTH 2
#define EDGE_ARRAY_INTITAL 2

void new_edge(vertex_t *start, vertex_t *dest, void *edge_data);
void new_vertex(void *data, vertex_t *in_edge, int in_n, vertex_t *out_edge, int out_n);


void void new_vertex(void *data, vertex_t *in_edge, int in_n, vertex_t *out_edge, int out_n) {

}

void new_edge(vertex_t *start, vertex_t *dest, void *edge_data) {
    edge_t *new_edge;

    new_edge = (edge_t*)malloc(sizeof(*new_edge));
    assert(new_edge);

    new_edge->data = edge_data;
    new_edge->dest = dest;

    if (start->n_edges == start->size_edges) {
        start->size_edges *= EDGE_ARRAY_GROWTH;
        start->edges = (edge_t*)realloc(start->edges, start->size_edges*sizeof(*start->edges));
        assert(start->edges);
    }

    start->edges[start->n_edges++] = new_edge;

}
