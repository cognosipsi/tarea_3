#ifndef OPCION_H
#define OPCION_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "list.h"
#include "opcion.h"
#include "hashmap.h"

typedef struct Node Node;

//Node *breadth_first_search(Node *, char,HashMap *);
int is_empty(List*);

void opcion_1(HashMap *);

void opcion_2(HashMap *, char *);

void opcion_3(HashMap *);

void opcion_4(HashMap *);

void opcion_5(HashMap *);


#endif