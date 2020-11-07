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
// gcc -g main.c hashmap-answer.c list.c opcion.c -o tarea_3


int main (void) {
  int op;
  char *ciudad;
  HashMap *ciudades = createMap(50);
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
          opcion_1(ciudades);
      }
      if (op == 2) {
          printf("Ingrese la ciudad\n");
          scanf("%s", ciudad);
          opcion_2(ciudades, ciudad);
      }
      if (op == 3) {
          opcion_3(ciudades);
      }
      if (op == 4) {
          opcion_4(ciudades);
      }
      if (op == 5) {
          opcion_5();
      }
  }
  return 0;
}
