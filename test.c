#include <stdlib.h>
#include "adjacency_list.h" 

int
main (int argc, char **argv) {
  adjl_graph *g1 = load_adjl_graph("graph.gr",10, DIRECTED);
  print_adjl_graph(g1); 
  
  adjl_graph *g2 = load_adjl_graph("graph.gr",10, UNDIRECTED);
  print_adjl_graph(g2);
  
  exit(0); 
}
