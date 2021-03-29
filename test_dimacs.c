#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "GrafoSt.h"

/*
 compilar gcc test.c
 ./a.out < dimacs 

*/ 
char* parse_correct_form_edge(char *str);
Lado_st* parse_p_edge_n_m(void);
Lado_st** parse_edge(Lado_st *lados);

int func_insertar_vert(u32 nombre, hash_table ht);
int func_insert_neighbour(u32 nombre, u32 vecino, hash_table ht);
int print_graph(hash_table ht);

/**
 * @brief chequea que la palabra este en forma correcta
 *         
 * @param str toma un string 
 * @return devuelve un string continuando luego de edge o
 *         si falla NULL.
 */
char* parse_correct_form_edge(char *str){
  char *r = NULL;

  r = strtok(str, "p ");
  if (strcmp(r, "edge") == 0){
    r = strtok(NULL," ");
    return r;
  }else{
    printf("error :%s \n", r);
    return NULL;
  }
}


Lado_st* parse_p_edge_n_m(void){
char *readString = NULL; 
u32 strToULong;
char *ptr = NULL;
bool flag = false;
Lado_st *Data = NULL;

Data = (Lado_st*) calloc(1, sizeof(struct Lado));
readString = (char *)calloc(1, sizeof(char));

  while (!flag) {
    if(fgets(readString, 1024, stdin) == NULL)
      return NULL;
    if(readString[0] == 'p'){
      if ((readString = parse_correct_form_edge(readString)) == NULL){
        return NULL;
      }
      strToULong = strtoul(readString, &ptr, 10);
      printf("1-%d\n", strToULong);
      Data->v = strToULong;
      readString = strtok(NULL, " ");
      strToULong = strtoul(readString, &ptr, 10);
      Data->w = strToULong;
      printf("2-%d\n", strToULong);
      flag = true;
    }
  }

return Data;
}


Lado_st** parse_edge(Lado_st *lados){
  bool flag = false;
  char *token, *ptr ,*readStr = NULL;
  u32 a, b, M = 0;
  Lado_st **array_lados = NULL;
  
  M = lados->w;
  readStr = (char *) calloc(1, sizeof(char));
  array_lados = (Lado_st **) calloc(M, sizeof(Lado_st));
  for (int i = 0; i < M; i++)
  {
    array_lados[i] = calloc(1, sizeof(struct Lado));
  }
  

  for (int i = 0; i < M; i++){
    if(fgets(readStr, 1024, stdin) == NULL)
      return NULL;
    if(readStr[0] = 'e'){
      token = strtok(readStr, "e ");
      a = (unsigned int) strtoul(token, &ptr, 10);
      token = strtok(NULL, " ");
      b = (unsigned int) strtoul(token, &ptr, 10);
      array_lados[i]->v = a;
      array_lados[i]->w = b;

    }


  }
return array_lados;
}


int func_insertar_vert(u32 nombre, hash_table ht){
  
    add_ht_entry(nombre, ht);

  return 0;
}

int func_insert_neighbour(u32 nombre, u32 vecino, hash_table ht){
  vertice *vert = NULL;
  printf("nombre: %d \n", nombre);
  vert = lookup_ht_entry(nombre, ht);
  if(vert != NULL){
    vert -> vecinos = addr_idemp(vecino, vert->vecinos);
  }
return 0;
}

int print_graph(hash_table ht){
  int M = ht->size;
  list lista = NULL;
  vertice *vert , *vecino = NULL;
  u32 longitud_lista = 0;
  for (u32 i = 0; i < M; i++)
  {
    vert = lookup_ht_entry(i, ht);
    if(vert != NULL){
          printf("vertice: %d -> \n", vert->nombre);
          printf("  vecinos:\n");
          printf("( \n");
          longitud_lista = length(vert->vecinos);
          printf("longitud_lista: %d \n", longitud_lista);
          for (u32 i=0; i < longitud_lista; i++)
          {
            vecino = index_ith(i , vert->vecinos); 
            if(vecino!=NULL){
              printf("%d ", vecino->nombre);
            }

          }
          printf("\n ) \n");
          printf("\n");     
    } 
  }
}

int main(int argc, char ** argv){
  Lado_st *infoEdge = NULL;
  Lado_st **array = NULL;
  u32 M = 0;
  hash_table ht = NULL;

  infoEdge = parse_p_edge_n_m();
  M = infoEdge->w;
  array = parse_edge(infoEdge);

  for (int i = 0; i < M; i++)
  {
    printf("array de carga (%d ,%d) \n",array[i]->v, array[i]->w);
  }
  
  ht = new_ht(M);

  for (int i = 0; i < M; i++)
  {
    func_insertar_vert(array[i]->v, ht);
    func_insertar_vert(array[i]->w, ht);
    func_insert_neighbour(array[i]->v, array[i]->w , ht);
    func_insert_neighbour(array[i]->w, array[i]->v , ht);
  }

  print_graph(ht);
  
  
  return 0;
}