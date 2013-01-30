#ifndef ADJACENCY_LIST_H
#define ADJACENCY_LIST_H

typedef enum {
  UNDIRECTED = 0,
  DIRECTED = 1
} GRAPH_TYPE;

typedef struct adjacency adjacency;

struct adjacency {
  int endpoint;
  double weight;
  adjacency *next; //for lists
};

typedef struct vertex vertex;

struct vertex {
  int v;
  vertex *next;
};

typedef struct adjl_graph adjl_graph;

struct adjl_graph {
  vertex *vertices;
  adjacency **adjacencies;
  int max;
};

vertex *init_vertex(int);
adjacency *init_adjacency(int, double);
adjl_graph *init_adjl_graph(int);
void add_vertex(adjl_graph *, int);
void edge(adjl_graph *, int, int, double, GRAPH_TYPE);
adjl_graph *load_adjl_graph(const char *, int, GRAPH_TYPE);
void print_adjl_graph(adjl_graph *);
void free_adjl_graph(adjl_graph *g);

#endif
