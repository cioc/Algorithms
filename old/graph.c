#include "graph.h"
#include "list.h"
#include <stdbool.h>
#include <stdlib.h>
//implements arbitrary graphs as adjacency lists
struct graph {
  listelem **vertices; 
  int n;
  bool *visited;
};

void append(void *, void *);

//creates a graph with up to n vertices
graph *
gengraph(int n) {
  graph *g = (graph *)malloc(sizeof(graph));
  g->vertices = (listelem **)malloc(sizeof(listelem *) * n);
  g->visited = (bool *)malloc(sizeof(bool) * n);
  for (int i = 0; i < n; ++i) {
    g->vertices[i] = NULL;
    g->visited[i] = false;
  }
  g->n = n;
  return g;
}

graph *
adjacency(graph *g, int v1, int v2) {
  int *t = malloc(sizeof(int));
  *t = v2;
  listelem *ne = newitem((void *)t);
  g->vertices[v1] = push(g->vertices[v1], ne);
  return g;   
}

void
append(void *v, void *q) {
  listelem **queue = (listelem **)q;
  listelem *ne = newitem(v);
  *queue = push(*queue, ne);
}

void
bfs(graph *g, int startnode, void (*fn)(int *, void *), void *args) {
  for (int i = 0; i < g->n; ++i) {
    g->visited[i] = false;
  }

  listelem *queue;
  listelem **iterqueue = (listelem **)malloc(sizeof(listelem));
  *iterqueue = NULL;
  queue = NULL;
  int t = startnode;
  listelem *fi = newitem((void *)&t); 
  queue = push(queue, fi);
  do {
    while (queue != NULL) {
      int *i = (int*)pop(&queue);
      if (!g->visited[*i]) {
        (*fn)(i, args);
        g->visited[*i] = true;
        apply(g->vertices[*i], append, (void *)iterqueue);
      }
    }
    queue = *iterqueue;
    *iterqueue = NULL;
  } while (queue != NULL);
  free(iterqueue);
} //end bfs

void
dfs(graph *g, int startnode, void (*fn)(int *, void *), void *args) {
  for (int i = 0; i < g->n; ++i) {
    g->visited[i] = false;
  }
 
  listelem *stack;
  stack = NULL;
  
  int t = startnode;
  listelem *fi = newitem((void *)&t);
  stack = push(stack, fi);
  do {
    int *i = (int *)pop(&stack);
    if (!g->visited[*i]) {
      (*fn)(i, args);
      g->visited[*i] = true;
      apply(g->vertices[*i], append, (void *)&stack);
    }
  } while (stack != NULL);
}

//wants a string like this:
//V,A,A,A... V,A,A,...
//e.g. 1,2,3 2,3,4
//is a graph where 1 is adjacent to 2 and 3
//
/*
void 
loadfromstr(graph **g, char *string) {
  
}
*/
