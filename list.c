//influenced heavily by Practice of Programming by Kernighan & Pike
#include "list.h"
#include <stdlib.h>

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
apply(listelem *list, void (*fn)(void *, void *), void *args) {
  listelem *curr;
  for (curr = list; curr != NULL; curr = curr->next) {
    (*fn)(curr->value, args);
  }
}
