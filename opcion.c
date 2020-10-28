#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "list.h"
#include "opcion.h"
#include "hashmap.h"
#include "treemap.h"

typedef struct {
  int id;        
  char nombre[40];   
  int pc;      
  int ps;      
  char sexo[10];
}pokemon;

typedef struct {
  char nombre[40];
  char tipos[2][40];
  int almacenados;
  char previa[40];
  char posterior[40];
  int numero;
  char region[40];
}pokemon_dex;

int identificacion = 0;

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

        if(open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ','){
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

void opcion_1(HashMap *MapaNombre, HashMap *MapaNombreDex, HashMap *MapaTipo,TreeMap *ArbolDex, TreeMap *ArbolPc, TreeMap *ArbolPs, HashMap *MapaRegion) {
    int op;
    printf("seleccione que archivo quiere importar:\n");
    printf("1.- para pokemon Archivo1.csv\n");
    printf("2.- para pokemon Archivo2.csv\n");
    FILE *fp;
    scanf("%d",&op);
    if(op==1){
      fp = fopen ("pokemon Archivo1.csv", "r");
    }else if(op==2){
      fp = fopen ("pokemon Archivo2.csv", "r");
    }else {
      printf("no es valido\n");
      return;
    }
    char linea[1024];
    int i;
    int j;
    int l;
    int k=0;
    char region[40];
    pokemon *info;
    pokemon_dex *infodex,*comprobardex;
    const char *aux;
    char *tmp;
    List *ListaNombre;
    fgets (linea, 1023, fp);
    while (fgets (linea, 1023, fp) != NULL) { //cada ciclo es una linea del csv 
        info=(pokemon*)malloc(sizeof(pokemon));
        infodex=(pokemon_dex*)malloc(sizeof(pokemon_dex));
        j=0;
        l=0;
        for(i=0;i<10;i++){
            infodex->almacenados=1;
            tmp = strdup(linea);
            aux = get_csv_field(tmp, i);
            free(tmp);
            if(i==0) {//en cada una de las condiciones dependientes del valor de i se copia los valores del nuevo pokemon
              identificacion++;
              info->id=identificacion;
            }if(i==1) {
              strcpy(info->nombre, aux);
              strcpy(infodex->nombre, aux);
            }if(i==2){
                while(aux[j]!=',' && aux[j]!='\0'){
                    infodex->tipos[0][j]=aux[j];
                    j++;
                }
                infodex->tipos[0][j]='\0';
                if(aux[j]==','){
                    j+=2;
                    while(aux[j]==' ' || isalpha(aux[j])){
                        infodex->tipos[1][l]=aux[j];
                        j++;
                        l++;
                    }
                    infodex->tipos[1][l]='\0';
                }
            }if(i==3) {
              info->pc=atoi(aux); 
            }if(i==4) {
              info->ps=atoi(aux); 
            }if(i==5) {
              strcpy(info->sexo, aux);
            }if(i==6) {
              strcpy(infodex->previa, aux);
            }if(i==7) {
              strcpy(infodex->posterior, aux);
            }if(i==8) {
              infodex->numero=atoi(aux); 
            }if(i==9) {
              strcpy(infodex->region,aux);
            }
        }
        if(searchMap(MapaNombre,info->nombre)==NULL) { //Si la condicion se cumple significa que es el primer pokemon con este nombre. Todos los mapas usan el mismo procedimiento
          ListaNombre=create_list();
          push_back(ListaNombre, info);
          insertMap(MapaNombre,info->nombre, ListaNombre);
        }else {
          push_back(searchMap(MapaNombre,info->nombre), info);
        }
        
        if(searchMap(MapaTipo,infodex->tipos[0])==NULL) {
          ListaNombre=create_list();
          push_back(ListaNombre, info);
          insertMap(MapaTipo,infodex->tipos[0], ListaNombre);  
        }else {
          push_back(searchMap(MapaTipo,infodex->tipos[0]), info);
        }
        if(searchMap(MapaTipo,infodex->tipos[1])==NULL) {
          ListaNombre=create_list();
          push_back(ListaNombre, info);
          insertMap(MapaTipo,infodex->tipos[1], ListaNombre);  
        }else {
          push_back(searchMap(MapaTipo,infodex->tipos[1]), info);
        }
        comprobardex=(pokemon_dex*)malloc(sizeof(pokemon_dex));
        comprobardex=searchMap(MapaNombreDex,infodex->nombre);
        if(comprobardex==NULL) {
          insertMap(MapaNombreDex,infodex->nombre, infodex);
        }else {
          comprobardex->almacenados++;
        }
        if(searchTreeMap(ArbolPc,&info->pc)==NULL) {
          ListaNombre=create_list();
          push_back(ListaNombre,info);
          insertTreeMap(ArbolPc,&info->pc,ListaNombre);
        }else {
          push_back(searchTreeMap(ArbolPc,&info->pc),info);
        }
        if(searchTreeMap(ArbolPs,&info->ps)==NULL) {
          ListaNombre=create_list();
          push_back(ListaNombre,info);
          insertTreeMap(ArbolPs,&info->ps,ListaNombre);
        }else {
          push_back(searchTreeMap(ArbolPs,&info->ps),info);
        }
    }
    infodex=firstMap(MapaNombreDex);
    while(infodex!=NULL) { 
      insertTreeMap(ArbolDex,&infodex->numero, infodex);
      infodex=nextMap(MapaNombreDex); 
    }
    
    infodex=firstMap(MapaNombreDex);
    while(infodex!=NULL) {
      if(searchMap(MapaRegion,infodex->region)==NULL) {
        ListaNombre=create_list();
        push_back(ListaNombre, infodex);
        insertMap(MapaRegion,infodex->region, ListaNombre);
      }else {
        push_back(searchMap(MapaRegion,infodex->region), infodex);
      }
      infodex=nextMap(MapaNombreDex);
    }
    ListaNombre=firstMap(MapaRegion);
    
}

void opcion1( HashMap *MapaNombre, HashMap *MapaNombreDex){
  char vec[50];
  printf("Ingrese nombre del archivo \n");
  scanf("%s", vec);
  fflush(stdin);
  fflush(stdin);
  strcat(vec, ".csv");
  FILE * fp = fopen(vec, "w");
  List * listapoke= firstMap(MapaNombre);
  char c='"';
  while(listapoke != NULL){
      pokemon * poke = first(listapoke);
      pokemon_dex * pokedex = searchMap(MapaNombreDex, poke->nombre);
      while(poke != NULL){
          fprintf(fp, "%d,%s,", poke->id,pokedex->nombre);
          


          /*char * tipos = first(pokedex->tipos);
          if( (tipos != NULL ) && ( next(pokedex->tipos) != NULL ) ){
              prev(pokedex->tipos);
              fprintf(fp,"%c",c);      //tripledoblecomilla
              while(tipos != NULL){     // tipos[1] tipos[0] 
                  if(next(pokedex->tipos) != NULL){
                      prev(pokedex->tipos);
                      fprintf(fp, "%s, ", tipos);
                  }
                  else{
                      fprintf(fp, "%s", tipos);
                  }
                  tipo = next(pokedex->tipos);
              }
              fprintf(fp,"%c",c);    // skjdfjksdjfksdfjk         
          }
          else{
              fprintf(fp, "%s", tipo);
          }*/
          if(isalpha(pokedex->tipos[1][0])!=0) fprintf(fp,"%c",c);
          fprintf(fp, "%s", pokedex->tipos[0]);
          if(isalpha(pokedex->tipos[1][0])!=0) {
            fprintf(fp, ",%s", pokedex->tipos[1]);
            fprintf(fp,"%c",c);
          }
          fprintf(fp, ",%d,%d,%s,%s,%s,%s\n", poke->pc,poke->ps,poke->sexo,pokedex->previa, pokedex->posterior, pokedex->region);
          poke = next(listapoke);
      }
      listapoke = nextMap(MapaNombre);
  }
  fclose(fp);
  system("pause");
  system("cls");
}

void opcion_2(HashMap *MapaNombre, HashMap *MapaNombreDex, HashMap *MapaTipo,TreeMap *ArbolDex, TreeMap *ArbolPc, TreeMap *ArbolPs, HashMap *MapaRegion){
    char nombre[40];
    int n;
    char tipos[2][40];
    int PC;
    int PS;
    char sexo[10];
    char previa[40];
    char posterior[40];
    int numero;
    char region[40];
    List *L;
    pokemon_dex *comprobardex;
    pokemon *pkm = (pokemon *) malloc(sizeof(pokemon));
    pokemon_dex *dex = (pokemon_dex *) malloc(sizeof(pokemon_dex));

    identificacion++;
    pkm->id=identificacion;

    printf("Ingrese nombre\n");
    scanf("%s", nombre);
    strcpy(pkm->nombre, nombre);
    strcpy(dex->nombre, nombre);

    printf("Ingrese cantidad de tipos\n");
    scanf("%d", &n);
    printf("Ingrese un tipo\n");
    scanf("%s", tipos[0]);
    strcpy(dex->tipos[0], tipos[0]);

    if (n == 2) {
        printf("Ingrese un tipo\n");
        scanf("%s", tipos[1]);
        strcpy(dex->tipos[1], tipos[1]);
    }
    
    printf("Ingrese PC\n");  //Se guardan los datos del pokemon
    scanf("%d", &PC);
    pkm->pc = PC;

    printf("Ingrese PS\n");
    scanf("%d", &PS);
    pkm->ps = PS;

    printf("Ingrese sexo\n");
    scanf("%s", sexo);
    strcpy(pkm->sexo, sexo);
    
    printf("Ingrese evolucion previa\n");
    scanf("%s", previa);
    strcpy(dex->previa, previa);
    
    printf("Ingrese evolucion posterior\n");
    scanf("%s", posterior);
    strcpy(dex->posterior, posterior);

    printf("Ingrese numero de la pokedex\n");
    scanf("%d", &numero);
    dex->numero = numero;
    
    printf("Ingrese region\n");
    scanf("%s", region);
    strcpy(dex->region, region);
    
    if (searchMap(MapaNombre, nombre) == NULL) {
        L = create_list();
        push_back(L, pkm);
        insertMap(MapaNombre, pkm->nombre, L);
    }
    else {
        push_back(searchMap(MapaNombre,pkm->nombre), pkm);
    }

    if (searchMap(MapaTipo, dex->tipos[0]) == NULL) {
        L = create_list();
        push_back(L, pkm);
        insertMap(MapaTipo, dex->tipos[0], L);  
    }
    else {
        push_back(searchMap(MapaTipo, dex->tipos[0]), pkm);
    }

    if (searchMap(MapaTipo, dex->tipos[1]) == NULL) {
        L = create_list();
        push_back(L, pkm);
        insertMap(MapaTipo, dex->tipos[1], L);  
    }
    else {
        push_back(searchMap(MapaTipo, dex->tipos[1]), pkm);
    }
    
    comprobardex = (pokemon_dex*) malloc(sizeof(pokemon_dex));
    comprobardex = searchMap(MapaNombreDex, dex->nombre);
    if (comprobardex == NULL) {
        insertMap(MapaNombreDex, dex->nombre, dex);
        dex->almacenados = 1;
    }
    else {
        comprobardex->almacenados++;
    }

    if (searchTreeMap(ArbolPc, &pkm->pc) == NULL) {
        L = create_list();
        push_back(L, pkm);
        insertTreeMap(ArbolPc, &pkm->pc, L);
    }
    else {
        push_back(searchTreeMap(ArbolPc, &pkm->pc), pkm);
    }

    if (searchTreeMap(ArbolPs, &pkm->ps) == NULL) {
        L = create_list();
        push_back(L, pkm);
        insertTreeMap(ArbolPs, &pkm->ps, L);
    }
    else {
        push_back(searchTreeMap(ArbolPs, &pkm->ps), pkm);
    }
    
    dex = firstMap(MapaNombreDex);//ATENCION
    while (dex != NULL) { //ATENCION
      insertTreeMap(ArbolDex, &dex->numero, dex);
      dex = nextMap(MapaNombreDex); //ATENCION
    }

    dex = firstMap(MapaNombreDex);
    while(dex != NULL) {
      if (searchMap(MapaRegion, dex->region) == NULL) {
        L = create_list();
        push_back(L, dex);
        insertMap(MapaRegion, dex->region, L);
      }else {
        push_back(searchMap(MapaRegion, dex->region), dex);
      }
      dex = nextMap(MapaNombreDex);
    }
}

void opcion_3(HashMap *MapaTipo){//busca pokemones de tipo especifico
    char tipo[40];
    printf("ingrese tipo\n");
    scanf("%s", tipo);
    List *L=searchMap(MapaTipo, tipo);//se busca si el tipo existe
    if(L == NULL) {
        printf(" No se encontro \n");
        return;
    }
    pokemon *iterador = first(L);
    while (iterador != NULL) { //cada ciclo es un pokemon del mismo tipo
        printf("%d ",iterador->id);
        printf("%s ",iterador->nombre);
        printf("%d ",iterador->pc);
        printf("%d ",iterador->ps);
        printf("%s ",iterador->sexo);
        printf("\n");
        iterador = next(L);
    }
} 

void opcion_4(HashMap *MapaNombre){//busca pokemones de nombre especifico
    char nombre[40];
    printf("Ingrese nombre\n");
    scanf("%s", nombre);
    List *L=searchMap(MapaNombre, nombre); //se busca si el nombre existe
    if(L == NULL) {
        printf(" No se encontro \n");
        return;
    }
    pokemon *iterador = first(L);
    while (iterador != NULL) { //cada ciclo es un pokemon del mismo nombre
        printf("%d ",iterador->id);
        printf("%s ",iterador->nombre);
        printf("%d ",iterador->pc);
        printf("%d ",iterador->ps);
        printf("%s ",iterador->sexo);
        printf("\n");
        iterador = next(L);
    }
}

void opcion_5(HashMap *MapaNombreDex){//busca pokemones de nombre especifico
    char nombre[40];
    pokemon_dex *dex_ite=(pokemon_dex*)malloc(sizeof(pokemon_dex));
    dex_ite = firstMap(MapaNombreDex); 
    bool no_exist = true;
    printf("Ingrese el nombre \n");
    scanf("%s", nombre);
    while (dex_ite != NULL){
        if(strcmp(dex_ite->nombre, nombre) == 0){
          printf("%s ", dex_ite->nombre);
          printf("%s ", dex_ite->tipos[0]);
          if(dex_ite->tipos[1] != NULL){
            printf("%s ",dex_ite->tipos[1]);
          }
          printf("%d ", dex_ite->almacenados);
          printf("%s ", dex_ite->previa);
          printf("%s ", dex_ite->posterior);
          printf("%d ", dex_ite->numero);
          printf("%s ", dex_ite->region);
          printf("\n");
          no_exist = false;
        }
        dex_ite = nextMap(MapaNombreDex);
    }
    if (no_exist == true){
        printf (" No se encontro ningun resultado \n");
    }
}

void opcion_6 (TreeMap *ArbolDex) {//imprime todos los pokemon por orden de pokedex
  pokemon_dex *dex_ite=(pokemon_dex*)malloc(sizeof(pokemon_dex));
  dex_ite=firstTreeMap(ArbolDex);    
  while (dex_ite != NULL){//cada ciclo es un pokemon a imprimir
      printf("%s ", dex_ite->nombre);
      printf("%s ", dex_ite->tipos[0]);
      if(dex_ite->tipos[1] != NULL){
        printf("%s ",dex_ite->tipos[1]);
      }
      printf("%d ", dex_ite->almacenados);
      printf("%s ", dex_ite->previa);
      printf("%s ", dex_ite->posterior);
      printf("%d ", dex_ite->numero);
      printf("%s ", dex_ite->region);
      printf("\n");
      dex_ite = nextTreeMap(ArbolDex);
  }
}
void opcion_7(TreeMap *ArbolPc){//imprime todos los pokemon por orden de pc
  pokemon *iterador=(pokemon*)malloc(sizeof(pokemon));
  List *L = firstTreeMap(ArbolPc); //son listas en caso de que repitan pc
  while (L != NULL) {
    iterador=first(L);
    while(iterador != NULL) {
      printf("%d ",iterador->id);
      printf("%s ",iterador->nombre);
      printf("%d ",iterador->pc);
      printf("%d ",iterador->ps);
      printf("%s ",iterador->sexo);
      printf("\n");
      iterador = next(L);
    }
    L = nextTreeMap(ArbolPc);
  }
}
void opcion_8(TreeMap *ArbolPs) {//imprime todos los pokemon por orden de ps
  pokemon *iterador=(pokemon*)malloc(sizeof(pokemon));
  List *L = firstTreeMap(ArbolPs);//son listas en caso de que repitan ps
  while (L != NULL) {
    iterador=first(L);
    while(iterador != NULL) {
      printf("%d ",iterador->id);
      printf("%s ",iterador->nombre);
      printf("%d ",iterador->pc);
      printf("%d ",iterador->ps);
      printf("%s ",iterador->sexo);
      printf("\n");
      iterador = next(L);
    }
    L = nextTreeMap(ArbolPs);
  }
}
void opcion_9 (HashMap *MapaNombre,HashMap *MapaNombreDex, HashMap *MapaTipo,TreeMap *ArbolDex, TreeMap *ArbolPs, TreeMap *ArbolPc,HashMap *MapaRegion, int id){
    List *L;
    int pc;
    int ps;
    int comprobar=0; //variable que se usa como booleano
    L=firstMap(MapaNombre);
    pokemon *iterador=(pokemon*)malloc(sizeof(pokemon));
    char nombre[40];
    pokemon_dex *iterador2=(pokemon_dex*)malloc(sizeof(pokemon_dex));
    pokemon_dex *guardado2=(pokemon_dex*)malloc(sizeof(pokemon_dex));
    while(L!=NULL) { //como no hay mapa con id como llave se tiene que buscar uno por uno
      iterador=(pokemon*)malloc(sizeof(pokemon));
      iterador = first(L);
      while (iterador != NULL) {
        if(iterador->id==id) {//id encontrado
          comprobar=1;
          pop_current(searchMap(MapaNombre,iterador->nombre));
          strcpy(nombre,iterador->nombre);
          pc=iterador->pc;
          ps=iterador->ps;
          if(listCount(searchMap(MapaNombre,iterador->nombre))==0){
            eraseMap(MapaNombre,iterador->nombre);
          }
          break;
        }
        iterador = next(L);
      }
      if(comprobar==1) break;
      L=nextMap(MapaNombre);
    }
    if(comprobar==1) { //solo se buscara para eliminar en el resto de los mapas si se encontro en MapaNombre
      iterador2=searchMap(MapaNombreDex,iterador->nombre);// se busca para disminuir en uno la existencia en la pokedex
      iterador2->almacenados--;
      guardado2=iterador2;
      iterador2=(pokemon_dex*)malloc(sizeof(pokemon_dex));
      iterador=(pokemon*)malloc(sizeof(pokemon));
      //Desde aqui hacia abajo se usa el mismo metodo para eliminar que en MapaNombre
      L=searchMap(MapaTipo,guardado2->tipos[0]);
      iterador=first(L);
      while(iterador!=NULL) {
        if(id==iterador->id) {
          pop_current(L);
          if(listCount(searchMap(MapaTipo,guardado2->tipos[0]))==0){
            eraseMap(MapaTipo,guardado2->tipos[0]);
          }
          break;
        }
        iterador=next(L);
      }
      if(guardado2->tipos[1]!=NULL) {
        L=searchMap(MapaTipo,guardado2->tipos[1]);
        iterador=first(L);
        while(iterador!=NULL) {
          if(id==iterador->id) {
            pop_current(L);
            if(listCount(searchMap(MapaTipo,guardado2->tipos[1]))==0){
              eraseMap(MapaTipo,guardado2->tipos[1]);
            }
            break;
          }
          iterador=next(L);
        }        
      }
      iterador2=searchTreeMap(ArbolDex,&guardado2->numero);
      iterador2=(pokemon_dex*)malloc(sizeof(pokemon_dex));
      L=searchTreeMap(ArbolPc,&pc);
      iterador=first(L);
      while(iterador!=NULL) {
        printf("hola");
        if(id==iterador->id) {
          pop_current(L);
          if(listCount(searchTreeMap(ArbolPc,&pc))==0){
            eraseTreeMap(ArbolPc,&pc);
          }
          break;
        }
        iterador=next(L);
      }
      L=searchTreeMap(ArbolPs,&ps);
      iterador=first(L);
      while(iterador!=NULL) {
        if(id==iterador->id) {
          pop_current(L);
          if(listCount(searchTreeMap(ArbolPs,&ps))==0){
            eraseTreeMap(ArbolPs,&ps);
          }
          break;
        }
        iterador=next(L);
      }      
    }else {//solo si comprobar==0
      printf("Ese id no se encuentra");
    }
}

void opcion_10(HashMap *MapaRegion){
    char region[40];
    pokemon_dex *aux =(pokemon_dex*)malloc(sizeof(pokemon_dex));
    int total=0;
    int a=0;
    printf("Escribe la region \n");
    scanf("%s",region);
    List *L;
    L=firstMap(MapaRegion);
    while(L!=NULL) { //debido a que por alguna razon se copian caracteres invisibles en la parte de region hay que comparar caracter por caracter.
      a=0;
      aux=first(L);
      while(isalpha(region[a])!=0) {
        if(aux->region[a]!=region[a]) { //si los caracteres son distintos se pasa al siguiente elemento del mapa
          break;
        }else a++;
      }
      if(isalpha(region[a])==0) { //esta condicion se cumple solo si paso por cada una de las letras de la palabre
        break;
      } 
      L=nextMap(MapaRegion);
    }
    pokemon_dex *iterador =(pokemon_dex*)malloc(sizeof(pokemon_dex));
    if(isalpha(region[a])!=0) { //esto solo se cumple si paso por todos los elementos del mapa y no hubo concidencias
        printf("No existe ningun pokemon de la region %s\n",region);
        return;
    }
    iterador = first(L);
    while (iterador!=NULL) { //se imprimen los datos de pokedex de cada pokemon de la region buscada
        printf(" %s ",iterador->nombre);
        printf("%d ",iterador->almacenados);
        printf("%s ", iterador->tipos[0]);
        if(iterador->tipos[1] != NULL){
          printf("%s ",iterador->tipos[1]);
        }
        printf("%s ",iterador->previa);
        printf("%s ",iterador->posterior);
        printf("%d ",iterador->numero);
        printf("%s ",iterador->region);
        printf("\n");
        total=total+iterador->almacenados; //se cuentan la cantidad total de pokemones almacenados de la region
        iterador = next(L);       
    }
    printf("Pokemons totales de la region %s: %d\n",region,total);
}