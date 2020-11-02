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
   HashMap* distancias;// clave:ciudad, valor:int
} Ciudad;

//mapa ciudades clave: ciudades; valor: struct ciudad

typedef struct{
   char ciudad1[30];
   char ciudad2[30];
   int distancia;
} informacion;

struct Pair {
     char * key;
     void * value;
};

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
    FILE *fp = fopen("distances.txt", "r");
    char linea[200];
    informacion *info;
    Ciudad *ciudad;
    int i;
    const char *aux;
    while (fgets(linea, 199, fp) != NULL){
        info=(informacion*) malloc (sizeof(informacion));
        for(i=0;i<3;i++){
          aux = get_csv_field(linea, i);
          if(i==0) {
            strcpy(info->ciudad1, aux);                        
          }if(i==1) {
            strcpy(info->ciudad2, aux); 
          }if(i==2) {
            info->distancia=atoi(aux);
          } 
        }
        if (searchMap(ciudades, info->ciudad1) == NULL){
          ciudad=(Ciudad*) malloc (sizeof(Ciudad));
          ciudad->distancias=createMap(10);
          strcpy(ciudad->nombre,info->ciudad1);
          insertMap(ciudad->distancias,info->ciudad2,&info->distancia);
          insertMap(ciudades,info->ciudad1, ciudad);          
        }else {
          ciudad=(Ciudad*) malloc (sizeof(Ciudad));
          ciudad=searchMap(ciudades, info->ciudad1);
          insertMap(ciudad->distancias,info->ciudad2,&info->distancia);
        }
        
        if (searchMap(ciudades, info->ciudad2) == NULL){
          ciudad=(Ciudad*) malloc (sizeof(Ciudad));
          ciudad->distancias=createMap(10);
          strcpy(ciudad->nombre,info->ciudad2);
          insertMap(ciudad->distancias,info->ciudad1,&info->distancia);
          insertMap(ciudades,info->ciudad2, ciudad);          
        }else {
          ciudad=(Ciudad*) malloc (sizeof(Ciudad));
          ciudad=searchMap(ciudades, info->ciudad2);
          insertMap(ciudad->distancias,info->ciudad1,&info->distancia);
        }       
    }
    
    ciudad=(Ciudad*) malloc (sizeof(Ciudad));
    Pair *infomap = (Pair *)malloc(sizeof(Pair));
    Pair *infodistancia = (Pair *)malloc(sizeof(Pair));
    infomap=firstMap(ciudades);
    while(infomap!=NULL) {
      printf("%s \n",infomap->key);
      ciudad=infomap->value;
      infodistancia=firstMap(ciudad->distancias);
      do{
        printf("%s %d \n",infodistancia->key, *((int *)infodistancia->value));
        infodistancia=nextMap(ciudad->distancias);
      }while(infodistancia!=NULL);
      infomap=nextMap(ciudades);
    }
}

void opcion_2(HashMap *ciudades, char *ciudad) {
    int dist_menor = 1000;
    char *min_ciudad = NULL;    
    if (searchMap(ciudades, ciudad) == NULL) {
        printf("Esta ciudad no se encuentra en el mapa\n");
        return;
    }
    Ciudad *c = (Ciudad *) malloc(sizeof(Ciudad));
    c = searchMap(ciudades, ciudad);
    Pair *infomap = (Pair *)malloc(sizeof(Pair));
    infomap = firstMap(c->distancias);
    while (infomap != NULL) {
        if (*((int *)infomap->value) < dist_menor) {
            dist_menor = *((int *)infomap->value);
            min_ciudad = infomap->key;
        }
        infomap = nextMap(c->distancias);
    }
    printf("%s\n", min_ciudad);
}

void opcion_3(HashMap *ciudades) {
    /*char ciudad[20];
    int resp = 2;
    
    printf("Ingrese ciudad\n");
    scanf("%s", &ciudad);
    
    printf("¿Desea terminar su ruta?"\n);
    printf("1. Si\n");
    printf("2. No\n");
    scanf("%d", resp);
    if (resp == 2) {
        opcion_3(ciudades);
    }
    */
}

void opcion_4() {

}

void opcion_5(){

}