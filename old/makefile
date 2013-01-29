cflags = -c -g -std=gnu99 -Werror
example_names = list_test graph_search_test

all: algorithms

algorithms: list_test graph_search_test

graph_search_test: list.o graph.o graph_search.o
	gcc list.o graph.o graph_search.o -o graph_search_test

graph_search.o: graph_search.c
	gcc $(cflags) graph_search.c

graph.o: graph.c
	gcc $(cflags) graph.c

list_test: list.o list_test.o
	gcc list.o list_test.o -o list_test

list.o: list.c
	gcc $(cflags) list.c

list_test.o: list_test.c
	gcc $(cflags) list_test.c
	
clean:
	rm -rf *.o $(example_names) 
