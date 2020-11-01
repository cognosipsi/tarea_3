#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "list.h"
#include "opcion.h"
#include "hashmap.h"

typedef struct{
   char nombre[30];
   HashMap* distancias;// clave:ciudad, valor:(ciudad,int)
}Ciudad;

const char *get_csv_field (char * tmp, int k) {
    int open_mark = 0;
    char* ret=(char*) malloc (100*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    while(tmp[i+1]!='\0'){

        if(tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if(open_mark || tmp[i]!= ' '){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ' '){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }
        i++;
    }

    if(k==j) {
       ret[i-ini_i] = 0;
       return ret;
    }


    return NULL;
}

char *strdup(const char *str) {
    char *aux = (char*) malloc(strlen(str)+1);
    strcpy(aux, str);
    return aux;
}

void opcion_1(HashMap *ciudades) {
    FILE *fp;
    char linea[200];
    fgets(linea, 199, fp);
    Ciudad *ptr; 
    while (fgets(linea, 199, fp) != NULL){
      ptr = (Ciudad*) malloc (sizeof(Ciudad));
      
    }
}

void opcion_2(HashMap *ciudades, char *ciudad) {
    
}

void opcion_3(HashMap *ciudades) {

} 

void opcion_4() {

}

void opcion_5(){

}