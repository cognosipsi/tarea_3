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
List *get_adj_nodes(Node *);
Queue *create_Queue();
void *top(Queue *);

void push(Queue *, void *);

#endif