#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "list.h"
#include "opcion.h"
#include "hashmap.h"
#include "heap.h"
#include "graph.h"

typedef struct{
   char nombre[30];
   HashMap* distancias;// clave:ciudad, valor:int
} Ciudad;

struct Pair {
     char * key;
     void * value;
};

struct Node{
   char ciudad[30];
   int dist;
   Node* prev;
};

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}


List* get_adj_nodes(Node* n,HashMap *ciudades){
    int menor;
    Pair *info;
    Ciudad *c;
    Node* nuevo;
    List* L=create_list();
    c = searchMap(ciudades, n->ciudad);
    info = firstMap(c->distancias);
    do{
      nuevo=(Node*) malloc(sizeof(Node));
      strcpy(nuevo->ciudad,info->key);
      nuevo->prev=n;
      nuevo->dist=n->dist+;
      info = nextMap( c->distancias );
    }while(info != NULL);    
}

Queue *create_Queue() {
    return create_list();
}

void* top(Queue* Q){
  return first(Q);
}

void push(Queue* Q, void* data){
   push_front(Q,data);
}

Node *breadth_first_search(Node *I) {
    Node *n;
    Node *adj;
    List *L;
    Queue *Q = create_Queue();
    push_back(Q, I);
    while (!is_empty(Q)) {
        n = top(Q);
        heap_pop(Q);
        if (is_final(n)) {
            return n;
        }
        L = get_adj_nodes(n);
        adj = first(L);
        while(adj) {
            push(Q, adj);
            adj = next(L);
        }
        free(n);
    }
    return NULL;
}