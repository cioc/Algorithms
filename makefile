cflags = -c -std=gnu99 -Werror
example_names = list_test bfs_test

all: algorithms

algorithms: list_test bfs_test

bfs_test: list.o graph.o bfs_test.o
	gcc list.o graph.o bfs_test.o -o bfs_test

bfs_test.o: bfs_test.c
	gcc $(cflags) bfs_test.c

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
