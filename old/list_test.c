#include <stdlib.h>
#include <stdio.h>
#include "list.h"

void
printint(void *value, void *args) {
  printf("value: %d\n", *((int *)value)); 
}

int
main (int argc, char **argv) {
  listelem *list;
  int i;
 
  printf("Let's do a stack\n"); 
  for (i = 0; i < 10; ++i) {
    int *z = (int *)malloc(sizeof(int));
    *z = i;
    
    listelem *newelem = newitem((void *)z);
    if (i == 0) {
      list = push(NULL, newelem);
    }
    else {
      list = push(list, newelem); 
    }
  } 
  apply(list, printint, NULL);


  void *b;
  for (; (b = pop(&list)) != NULL;) {
    printf("value: %d\n", *((int *)b)); 
    free(b);
  }

  printf("let's do a queue\n");
  for (i = 0; i < 10; ++i) {
    int *z = (int *)malloc(sizeof(int));
    *z = i;
    
    listelem *newelem = newitem((void *)z);
    if (i == 0) {
      list = push(NULL, newelem);
    }
    else {
      list = push(list, newelem); 
    }
  } 
  apply(list, printint, NULL);


  for (; (b = poplast(&list)) != NULL;) {
    printf("value: %d\n", *((int *)b)); 
    free(b);
  }
  exit(0);
}
