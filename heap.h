#ifndef Heap_h
#define Heap_h

typedef struct Heap Heap;

Heap* createHeap();
void* heap_top(Heap*);
void heap_push(Heap*, void*, int);
void heap_pop(Heap*);


#endif /* HashMap_h */

