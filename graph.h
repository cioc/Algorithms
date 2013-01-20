#ifndef GRAPH_H
#define GRAPH_H

#include "list.h"
typedef struct graph graph;

graph *gengraph(int n);
graph *adjacency(graph *g, int v1, int v2);
void bfs(graph *g, int startnode, void (*fn)(int *, void *), void *args); 
void dfs(graph *g, int startnode, void (*fn)(int *, void *), void *args);
#endif
