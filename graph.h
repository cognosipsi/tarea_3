#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "list.h"
#include "opcion.h"
#include "hashmap.h"
#include "heap.h"

Node *createNode();
List *get_adj_nodes(Node *,HashMap *);
int is_final(Node *);
Queue *create_Queue();
void *top(Queue *);
void push(Queue *, void *);
void pop(Queue* Q);
Node *breadth_first_search(Node *, char, HashMap *);

#endif
