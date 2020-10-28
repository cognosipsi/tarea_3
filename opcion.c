#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "list.h"
#include "opcion.h"
#include "hashmap.h"
#include "treemap.h"

typedef struct{
   char nombre[30];
   Map* distancias;// clave:ciudad, valor:(ciudad,int)
}Ciudad;



char *strdup(const char *str) {
    char *aux = (char*) malloc(strlen(str)+1);
    strcpy(aux, str);
    return aux;
}

void opcion_1() {
    
}

void opcion_2() {
    
}

void opcion_3() {

} 

void opcion_4() {

}

void opcion_5(){

}