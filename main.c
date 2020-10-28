#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"
#include "list.h"
#include "opcion.h"
#include "treemap.h"
//gcc -g main.c hashmap-answer.c list.c opcion.c treemap.c -o tarea_2
/*int lower_than_string(void* key1, void* key2){
    char* k1=(char*) key1;
    char* k2=(char*) key2;
    if(strcmp(k1,k2)<0) return 1;
    return 0;
}*/
/*int lower_than_string(void* key1, void* key2){
    int k1=atoi((char*) key1);
    int k2=atoi((char*) key2);
    if(k1<k2) return 1;
    return 0;
}*/
int lower_than_int(void* key1, void* key2){
    int k1 = *((int*) (key1));
    int k2 = *((int*) (key2));
    return k1<k2;
}
int higher_than_int(void* key1, void* key2){
    int k1 = *((int*) (key1));
    int k2 = *((int*) (key2));
    return k1>k2;
}
int main (void) {
  int op;

  while (op != 6) {
      /* MENU */ 
        printf("1.- Importar archivo de ciudades y distancias\n");
        printf("2.- Ciudad más cercana\n");
        printf("3.- Crear ruta\n");
        printf("4.- Ruta más corta entre ciudades\n");
        printf("5.- Mejor circuito\n");
        printf("6.- Salir\n");
        printf("\nIndica la opcion: ");
        scanf("%d", &op);
      if (op == 1) {
          opcion_1();
      }
      if (op == 2) {
          opcion_2(); 
      }
      if (op == 3) {
          printf("Ingrese el tipo\n");
          opcion_3();
      }
      if (op == 4) {
          printf("Ingrese el nombre\n");
          opcion_4();
      }
      if (op == 5) {
          printf("Ingrese el nombre\n");
          opcion_5();
      }
  }
  return 0;
}
