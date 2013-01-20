#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

void
printnode(int *v, void *arg) {
  printf("Visiting node: %d\n", *v);
}


int
main (int argc, char **argv) {
  
  graph *g = gengraph(7);
  g = adjacency(g, 0, 1);
  g = adjacency(g, 0, 2);
  g = adjacency(g, 1, 5);
  g = adjacency(g, 2, 3);
  g = adjacency(g, 2, 4);
  g = adjacency(g, 3, 6);
  
  printf("bfs\n");
  bfs(g, 0, printnode, NULL);
  printf("dfs\n");
  dfs(g, 0, printnode, NULL);
  exit(0);
}

