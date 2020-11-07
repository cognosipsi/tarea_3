#ifndef __defined_arraylist_h
#define __defined_arraylist_h

#include <stdlib.h>
#include <stdio.h>


typedef struct List List;
typedef List Queue;

List* create_list();

void push_back(List *, void *);

void push_front(List *, void *);

void pop_front(List *);

void pop_back(List *);

void pop_current(List *);

int is_empty(List *);

//int size(List* L);
long listCount(List *);

void* first(List *);

void* next(List *);

void clear(List *);



#endif /* __defined_arraylist_h */
