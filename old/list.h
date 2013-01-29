#ifndef LIST_H
#define LIST_H

typedef struct listelem listelem;

struct listelem {
  void *value;
  listelem *next;
};

listelem *newitem(void *value);
listelem *push(listelem *list, listelem *new);
void *pop(listelem **list);
void *poplast(listelem **list);
void apply(listelem *list, void (*fn)(void *, void *), void *args);

#endif 
