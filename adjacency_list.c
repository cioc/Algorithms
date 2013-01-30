//TODO - CHECK RETURN OF MALLOC EVERYWHER
//NOTE - I HAVE NOT EVEN TRIED COMPILING THIS YET

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "adjacency_list.h"

vertex *
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
  adjl_graph *o = malloc(sizeof(adjl_graph));
  o->max = max_nodes;
  o->vertices = NULL;
  o->adjacencies = malloc(sizeof(adjacency *) * max_nodes);
  for (int i = 0; i < max_nodes; ++i) {
    o->adjacencies[i] = NULL; 
  }
  return o;
}

void 
add_vertex(adjl_graph *g, int v) {
  bool new = false;
  vertex *curr = g->vertices;
  if (curr == NULL) {
    g->vertices = init_vertex(v);
    return;
  }
  for (curr = g->vertices; curr->next != NULL; curr = curr->next) {
    if (curr->v == v) {
      new = true;
      break;
    }
  }
  if (new) {
    vertex *vt = init_vertex(v);
    curr->next = vt;       
  }
}

void
edge(adjl_graph *g, int start, int end, double weight, GRAPH_TYPE type) {
  add_vertex(g, start);
  add_vertex(g, end);
  
  adjacency *adj = init_adjacency(end, weight);
  adjacency *curr = g->adjacencies[start];
  
  if (curr == NULL) {
    g->adjacencies[start] = adj;
  }
  else {
    for (; curr->next != NULL; curr = curr->next)
      ;
    curr->next = adj;
  }
  
  if (type == UNDIRECTED) {
    curr = g->adjacencies[end];
    adj = init_adjacency(start, weight);
    if (curr == NULL) {
      g->adjacencies[end] = adj;
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
adjl_graph *
load_adjl_graph(const char *path, int max_nodes, GRAPH_TYPE type) {
  int fd = open(path, O_RDONLY);
  if (fd < 2) {
    return NULL;
  } 
  adjl_graph *g = init_adjl_graph(max_nodes);

  struct stat statbuf;
  fstat(fd, &statbuf);
  int len = statbuf.st_size;
 
  void *t = mmap(NULL, len, PROT_WRITE, MAP_PRIVATE, fd, 0);
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
    sscanf(curr, "%d,%d,%lf", &start, &end, &weight);
    
    edge(g, start, end, weight, type);        
    
    curr = strtok(NULL, "\r\n");
    
  } 
  close(fd);
  munmap(t,len); 
  return g;
}

void
print_adjl_graph(adjl_graph *g) {
  printf("GRAPH:\n");
  for (int i = 0; i < g->max; ++i) {
    if (g->adjacencies[i] != NULL) {
      adjacency *curr = g->adjacencies[i];
      printf("%i: ", i);
      for (; curr != NULL; curr = curr->next) {
        printf("(%d, w: %lf) ", curr->endpoint, curr->weight); 
      }
      printf("\n");
    }  
  }
}
