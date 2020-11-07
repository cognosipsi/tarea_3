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

typedef struct nodo{
   void* data;
   int priority;
}heapElem;

typedef struct Heap{
  heapElem* heapArray;
  int size;
  int capac;
} Heap;

/*typedef struct{
 int* data; //arreglo dinámico
 int head; int tail;
 int c; //tamaño actual del arreglo
} Queue;*/


void* heap_top(Heap* pq){
    if(pq->size==0) return NULL;
    return pq->heapArray[0].data;
}



void heap_push(Heap* pq, void* data, int priority){
    if (pq->size == pq->capac) {
        pq->capac = pq->capac * 2 + 1;
        pq->heapArray = realloc(pq->heapArray, pq->capac * sizeof(heapElem));
    }
    int actual = pq->size;
    while (actual > 0 && pq->heapArray[(actual-1)/2].priority < priority) {
        pq->heapArray[actual] = pq->heapArray[(actual-1)/2];
        actual = (actual-1)/2;
    }
    pq->heapArray[actual].priority = priority;
    pq->heapArray[actual].data = data;
    pq->size++;
}

void heap_pop(Heap* pq){
    int actual;
    heapElem aux;

    pq->heapArray[0].priority = pq->heapArray[pq->size-1].priority;
    pq->heapArray[0].data = pq->heapArray[pq->size-1].data;
    pq->size--;
    actual = 0;
    while ((pq->heapArray[actual].priority < pq->heapArray[2 * actual + 1].priority) || (pq->heapArray[actual].priority < pq->heapArray[2 * actual + 2].priority)) {
        if (2 * actual + 1 == pq->size || 2 * actual + 2 == pq->size) return;
        if (pq->heapArray[2 * actual + 2].priority > pq->heapArray[2 * actual + 1].priority) {
            aux = pq->heapArray[actual];
            pq->heapArray[actual].priority = pq->heapArray[2 * actual + 2].priority;
            pq->heapArray[actual].data = pq->heapArray[2 * actual + 2].data;
            pq->heapArray[2 * actual + 2].priority = aux.priority;
            pq->heapArray[2 * actual + 2].data = aux.data;
            actual = 2 * actual + 2;
        }
        else {
            aux = pq->heapArray[actual];
            pq->heapArray[actual].priority = pq->heapArray[2 * actual + 1].priority;
            pq->heapArray[actual].data = pq->heapArray[2 * actual + 1].data;
            pq->heapArray[2 * actual + 1].priority = aux.priority;
            pq->heapArray[2 * actual + 1].data = aux.data;
            actual = 2 * actual + 1;
        }
    }
}

Heap* createHeap(){
    Heap *h = (Heap*) malloc (sizeof(Heap));
    h->size = 0;
    h->capac = 3;
    h->heapArray = (heapElem*) calloc (3,sizeof(heapElem));
    h->heapArray[h->size].priority = 1;
    h->heapArray[h->size].data = NULL;

    return h;
}

/*Queue *push_queue() {
    Heap *heap = createHeap();
    int i;
    char j[3];
    for (i = 0 ; i < 10 ; i++){
        int p = rand() % 100;
        itoa(p, j, 10); //se convierte el número en string j
        heap_push(heap, strdup(j), p);  //se guarda el string con prioridad p
    }
    return 
}*/