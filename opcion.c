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

struct Node{
   char ciudad[30];
   int dist;
   Node* prev;
};

struct List {
    /*! Puntero al incio (cabeza) de la lista */
    Node * head;
    
    /*! Puntero al final (cola) de la lista */
    Node * tail;
    
    /*! Punteor para poder recorrer la lista */
    Node * current;
    
    /*! Cantidad de elemento en la lista */
    long count;
};

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

int is_empty(List* list){
    return (list->head==NULL);
}

List* get_adj_nodes(Node* n,HashMap *ciudades) {
    int menor;
    Pair *info;
    Ciudad *c;
    Node* nuevo;
    List* L = create_list(); //almacena los nodos adyacentes
    c = searchMap(ciudades, n->ciudad);
    info = firstMap(c->distancias);
    do { //recorre el mapa de la ciudad
      nuevo = (Node*) malloc(sizeof(Node));
      strcpy(nuevo->ciudad, info->key);
      nuevo->prev = n;
      nuevo->dist = n->dist + *(int *)info->value;
      if (nuevo->prev->prev == NULL) { //evita error de segmentacion
          push_back(L, nuevo);
      } else if(/*is_valid(n)*/strcmp(nuevo->ciudad,nuevo->prev->prev->ciudad) != 0) { //valida que no sea la misma
        push_back(L, nuevo);             //ciudad que hace dos nodos
      }
      info = nextMap(c->distancias);
    } while(info != NULL);
    return L;    
}

int is_final(Node *n,char destino[30]) {//Si la ciudad actual es la misma que la del destino es 1 si no 0
  if(strcmp(n->ciudad,destino)==0) return 1;
  return 0;
}

//funciones cola:

Queue *create_Queue() {
    return create_list();
}

void* top(Queue* Q){
  return first(Q);
}

void push(Queue* Q, void* data){
   push_back(Q,data);
}

void pop(Queue* Q){
  pop_front(Q);
}

Node *breadth_first_search(Node *I, char destino[30], HashMap *ciudades) {
    Node *n;
    Node *mejor;
    int min = 10000;
    Node *adj;
    List *L; //guarda los nodos adyacentes
    Queue *Q = create_Queue();
    push_back(Q, I);
    while(!is_empty(Q)) {
        n = top(Q);
        pop(Q);
        if(min < n->dist) continue;
            if (is_final(n, destino)) { //valida que sea el ultimo nodo
                if (min > n->dist) { //valida que sea la ruta mas corta
                  mejor = n; //almacena la ciudad mas cercana
                  min = n->dist; //almacena la distancia
                  continue;
                }
            }
        L = get_adj_nodes(n, ciudades); //crea  una lista con los nodos
        adj = first(L); //adyacentes
        while(adj) { //añade los nodos (ciudades) adyacentes a una cola
            push(Q, adj); //recorriendo la lista
            adj = next(L);
        }
    }
    return mejor;
}

const char *get_csv_field (char * tmp, int k) { //lee cada linea de un
    int open_mark = 0;                          //archivo txt
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
    while (fgets(linea, 199, fp) != NULL){ //se lee cada linea del  
        info=(informacion*) malloc (sizeof(informacion)); //archivo en un
                                                        //ciclo iterativo
        for(i=0;i<3;i++){ //se separa con i las palabras de cada linea
          aux = get_csv_field(linea, i);
          if(i==0) {
            strcpy(info->ciudad1, aux);                        
          }if(i == 1) {
            strcpy(info->ciudad2, aux); 
          }if(i == 2) {
            info->distancia = atoi(aux);
          }
        }
        //Se llena el mapa ciudades con las ciudades y su respectiva informacion y se crea su respectivo mapa distancias en caso de no existir
        if (searchMap(ciudades, info->ciudad1) == NULL){ //En caso de que la primera ciudad exista en el mapa
          ciudad = (Ciudad*) malloc (sizeof(Ciudad));
          ciudad->distancias = createMap(10);
          strcpy(ciudad->nombre, info->ciudad1);
          insertMap(ciudad->distancias, info->ciudad2, &info->distancia);
          insertMap(ciudades, info->ciudad1, ciudad);          
        } else { //En caso de que la primera ciudad no exista en el mapa
          ciudad = (Ciudad*) malloc (sizeof(Ciudad));
          ciudad = searchMap(ciudades, info->ciudad1);
          insertMap(ciudad->distancias, info->ciudad2, &info->distancia);
        }
        
        if (searchMap(ciudades, info->ciudad2) == NULL){ //En caso de que la segunda ciudad exista en el mapa
          ciudad = (Ciudad*) malloc (sizeof(Ciudad));
          ciudad->distancias = createMap(10);
          strcpy(ciudad->nombre, info->ciudad2);
          insertMap(ciudad->distancias, info->ciudad1, &info->distancia);
          insertMap(ciudades, info->ciudad2, ciudad);          
        } else { //En caso de que la segunda ciudad no exista en el mapa
          ciudad = (Ciudad*) malloc (sizeof(Ciudad));
          ciudad = searchMap(ciudades, info->ciudad2);
          insertMap(ciudad->distancias, info->ciudad1, &info->distancia);
        }
    }
}

void opcion_2(HashMap *ciudades, char *ciudad) {
    int dist_menor = 1000;
    char *min_ciudad = NULL;    
    if (searchMap(ciudades, ciudad) == NULL) { //se valida que exista la
        printf("Esta ciudad no se encuentra en el mapa\n"); //ciudad
        return;
    }
    Ciudad *c = (Ciudad *) malloc(sizeof(Ciudad));
    c = searchMap(ciudades, ciudad); //busca la ciudad en el mapa y a
    Pair *infomap = (Pair *)malloc(sizeof(Pair)); //través de esta 
    infomap = firstMap(c->distancias);
    while (infomap != NULL) { //busca la ciudad adyacente a menor
        if (*((int *)infomap->value) < dist_menor) { //distancia
            dist_menor = *((int *)infomap->value);
            min_ciudad = infomap->key;
        }
        infomap = nextMap(c->distancias);
    }
    printf("%s\n", min_ciudad);
}

void opcion_3(HashMap *ciudades) {
    char ciudad[30];
    int distancia = 0;
    Pair *info;
    int primera = 1; // necesario para comprobar si ya se paso por la primera ciudad
    Pair *infodistancia;
    List *L = create_list(); // lista que guardara la ruta creada
    Ciudad *c;
    void *i;
    printf("Ingrese ciudad\n");
    scanf("%s", ciudad);
    c = searchMap(ciudades, ciudad);
    if ( !c ) { //valida que exista la ciudad
      printf("No existe la ciudad \n");
      return;
    }
    do {
      push_back(L, c); // existe la ciudad y se almacena en la lista de ruta
      if (primera == 0) { 
        distancia = distancia + *(int *)i; // suma las distancias de la ruta
      }
      printf("\n");
      info = firstMap(c->distancias);
      do {           // se muestran las ciudades adyacentes para continuar la ruta
        printf("%s \n", info->key);
        info = nextMap( c->distancias );
      } while(info != NULL);
      printf("\nIngrese la siguiente ciudad entre las opciones disponibles.\nEn caso que quiera terminar la ruta ingrese cualquier texto.\n");
      scanf("%s", ciudad);
      i = searchMap(c->distancias, ciudad); 
      c = searchMap(ciudades, ciudad);  
      primera = 0;
    } while ( i != NULL);
    c = first(L);
    printf("\n");
    while (c != NULL) {                    // se imprimen las ciudades de la ruta creada
      printf("%s \n", c->nombre);
      c = next(L);
    }
    printf("%d kilometros\n\n", distancia);// se imprimen los kilometros totales de 
                                           // la ruta creada
}    
void opcion_4(HashMap *ciudades) { //se utiliza el algoritmo de Dijkstra
    char partida[30], destino[30];
    List *L = create_list(); //guarda la ruta
    Node *n = createNode();
    Node *ultimo = createNode();
    printf("Escriba ciudad de partida\n");
    do {
      scanf("%s", partida);
    } while(searchMap(ciudades, partida) == NULL);
    printf("Escriba ciudad de destino\n");
    do { //valida que exista el destino
      scanf("%s", destino);
    } while(searchMap(ciudades, destino) == NULL);
    n->prev = NULL; 
    strcpy(n->ciudad, partida);
    n->dist = 0;
    //busca la ruta más corta con la busqueda en anchura
    ultimo = breadth_first_search(n, destino, ciudades);
    printf("%d \n", ultimo->dist);
    while(ultimo != NULL) { //imprime la ruta en el orden "correcto"
        push_front(L, ultimo); //(desde la ciudad de de partida hasta su
        if(strcmp(ultimo->ciudad, partida) == 0) { //destino usando una
            n = first(L);                          //lista
            while(n != NULL) {
                printf("%s \n", n->ciudad);
                n = next(L);
            }
            return;
        }
        ultimo = ultimo->prev;
    }
}

void opcion_5(HashMap *ciudades){
    char ciudad1[30], ciudad2[30], ciudad3[30];
    //se crean los nodos donde se guardan los recorridos
    Node *n1 = createNode(); 
    Node *n2 = createNode();
    Node *n3 = createNode();
    int total;
    //Pide los destinos y valida su existencia
    printf("Escriba ciudad 1\n");
    do{
      scanf("%s", ciudad1);
    }while(searchMap(ciudades,ciudad1)==NULL);
    printf("Escriba ciudad 2\n");
    do{
      scanf("%s", ciudad2);
    }while(searchMap(ciudades,ciudad2)==NULL);
    printf("Escriba ciudad 3\n");
    do{
      scanf("%s", ciudad3);
    }while(searchMap(ciudades,ciudad3)==NULL);
    //Da los valores iniciales a los nodos
    n1->prev=NULL; 
    strcpy(n1-> ciudad, ciudad1);
    n1-> dist = 0;
    n2->prev=NULL; 
    strcpy(n2-> ciudad, ciudad2);
    n2-> dist = 0;
    n3->prev=NULL; 
    strcpy(n3-> ciudad, ciudad3);
    n3-> dist = 0;
    //Con busqueda de anchura se busca la menor distancia entre los 3 puntos(ciudades)
    n1=breadth_first_search(n1,ciudad2,ciudades);
    n2=breadth_first_search(n2,ciudad3,ciudades);
    n3=breadth_first_search(n3,ciudad1,ciudades);
    printf("\n");
    total=n1->dist+n2->dist+n3->dist;
    //se usan ciclos iterativos para escribir el recorrido de 1 a 3 de 3 a 2 y de 2 a 1
    while (n3!= NULL) {
        printf("%s \n",n3->ciudad);
        n3= n3->prev;
    }
    n2= n2->prev; 
    while (n2!= NULL) {
        printf("%s \n",n2->ciudad);
        n2= n2->prev;
    }
    n1= n1->prev;
    while (n1!= NULL) {
        printf("%s \n",n1->ciudad);
        n1= n1->prev;
    }
    printf("%d kilometros de recorrido total\n",total);
}