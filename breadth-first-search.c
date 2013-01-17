//influenced heavily by Practice of Programming by Kernighan & Pike

#include <stdlib.h>
#include <stdio.h>

typedef struct listelem listelem;

struct listelem {
  void *value;
  listelem *next;
};

listelem *
newitem(void *value) {
  listelem *le = (listelem *)malloc(sizeof(listelem));
  le->value = value;
  le->next = NULL;
  return le;
}

//use push and pop for stacks
//use push and poplast for queues

listelem *
push(listelem *list, listelem *new) {
  new->next = list;
  return new;
}

void *
pop(listelem **list) {
  if (list == NULL || *list == NULL) {
    return NULL; 
  }
  listelem *next = (*list)->next;
  void *value = (*list)->value;
  free(*list);
  *list = NULL;
  (*list) = next; 
  return value; 
}

void *
poplast(listelem **list) {
  if (*list == NULL) {
    return NULL;
  }
  listelem *last;
  for (last = *list; (last->next != NULL) && (last->next->next != NULL) ;last = last->next) {
    ;
  }
  if (last->next == NULL) {
    void *value = last->value;
    free(*list);
    (*list) = NULL;
    return value;    
  }
  else {
    listelem *out = last->next;
    void *value = out->value;
    last->next = NULL;
    free(out);
    out = NULL; 
    return value; 
  }
}

void
apply(listelem *list, void (*fn)(listelem *, void *), void *args) {
  listelem *curr;
  for (curr = list; curr != NULL; curr = curr->next) {
    (*fn)(curr, args);
  }
}

void
printint(listelem *curr, void *args) {
  printf("value: %d\n", *((int *)curr->value)); 
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
