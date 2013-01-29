//TODO - CHECK RETURN OF MALLOC EVERYWHER
//NOTE - I HAVE NOT EVEN TRIED COMPILING THIS YET

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>

enum {
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

vertex *v
init_vertex(int v) {
  vertex *o = malloc(sizeof(vertex));
  o->v = v;
  o->next = NULL;
  return o;
}

adjacency *
init_adjacency(int endpoint, double weight) {
  adjacency *o = malloc(sizeof(adjacency));
  o->endpoint = endpoint;
  o->weight = weight;
  return o;
}

adjl_graph*
init_adjl_graph(int max_nodes) {
  adjacency *o = malloc(sizeof(adjl_graph));
  o->max = max_nodes;
  o->vertices = NULL;
  p->adjacencies = malloc(sizeof(adjacency *) * max_nodes);
  for (int i = 0; i < max_nodes; ++i) {
    o->adjacencies[i] = NULL; 
  }
  return o;
}

void 
vertex(adjl_graph *g, int v) {
  bool new = false;
  vertex *curr;
  for (curr = g->vertices; curr->next != NULL; curr = curr->next) {
    if (curr->v == v) {
      new = true;
      break;
    }
  }
  if (new) {
    vertex *v = init_vertex(v);
    curr->next = v;       
  }
}

void
edge(adjl_graph *g, int start, int end, double weight, GRAPH_TYPE type) {
  vertex(g, start);
  vertex(g, end);
  adjacency *adj = init_adjacency(end, weight);
  adjacency *curr = g->adjacencies[start];
  if (curr == NULL) {
    curr = adj;
  }
  else {
    for (; curr->next != NULL; curr = curr->next)
      ;
    curr->next = adj;
  }
  if (type == UNIDIRECTED) {
    curr = g->adjacencies[end];
    adj = init_adjacency(start, weight);
    if (curr == NULL) {
      curr = adj;
    }
    else {
      for (; curr->next != NULL; curr = curr->next)
        ;
      curr->next = adj;
    }
  }
}

//i wanted to play with memory mapping
//NOT THREAD SAFE - see strtok
graph *
load_adjl_graph(const char *path, int max_nodes, GRAPH_TYPE type) {
  int fd = open(path, O_RDONLY);
  if (fd < 2) {
    return NULL;
  } 
 
  graph *g = init_adjl_graph(max_nodes);

  struct stat statbuf;
  fstat(fd, &statbuf);
  int len = statbuf.st_size;
 
  void *t = mmap(NULL, len, PROT_READ, MAP_PRIVATE, fd, 0);
  if (t == NULL) {
    close(fd);
    return NULL;
  }
  char *str = (char *)t;
  
  char *curr;
  curr = strtok(str, "\r\n");
  while (curr != NULL) {
    int start;
    int end;
    double weight;
    sscanf(curr, "%d,%d,%Lf", &start, &end, &weight);
    edge(f, start, end, weight, type);        
    curr = strtok(NULL, "\r\n");
  }

  close(fd);
  munmap(t,len); 
  return g;
}
