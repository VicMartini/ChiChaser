#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "dimacs.h"

/*
 compilar gcc test.c
 ./a.out < dimacs 

*/

/**
 * @brief chequea que la palabra este en forma correcta
 *         
 * @param str toma un string 
 * @return devuelve un string continuando luego de edge o
 *         si falla NULL.
 */
char *parse_correct_form_edge(char *str)
{
  char *r = NULL;

  r = strtok(str, "p ");
  if (strcmp(r, "edge") == 0)
  {
    r = strtok(NULL, " ");
    return r;
  }
  else
  {
    printf("error :%s \n", r);
    return NULL;
  }
}

Lado_st *parse_p_edge_n_m(void)
{
  char buffer[80];
  char *readString = NULL;
  u32 strToULong;
  char *ptr = NULL;
  bool flag = false;
  Lado_st *Data = NULL;
  
  readString = buffer;
  Data = (Lado_st *)calloc(1, sizeof(struct Lado));
  while (!flag)
  {
    if (fgets(readString, sizeof(buffer), stdin) == NULL)
      return NULL;
    if (readString[0] == 'p')
    {
      if ((readString = parse_correct_form_edge(readString)) == NULL)
      {
        return NULL;
      }
      strToULong = strtoul(readString, &ptr, 10);
      Data->v = strToULong;
      readString = strtok(NULL, " ");
      strToULong = strtoul(readString, &ptr, 10);
      Data->w = strToULong;
      flag = true;
    }
  }


  return Data;
}

Lado_st **parse_edge(Lado_st *lados)
{
  char buffer[80];
  char *readStr;
  char *token, *ptr;
  u32 a, b, M = 0;
  Lado_st **array_lados = NULL;
  readStr = buffer;
  M = lados->w;
  array_lados = (Lado_st **)calloc(M, sizeof(Lado_st));
  for (int i = 0; i < M; i++)
  {
    array_lados[i] = calloc(1, sizeof(struct Lado));
  }

  for (int i = 0; i < M; i++)
  {
    if (fgets(readStr, sizeof(buffer), stdin) == NULL)
      return NULL;
    if (readStr[0] == 'e')
    {
      token = strtok(readStr, "e ");
      a = (unsigned int)strtoul(token, &ptr, 10);
      token = strtok(NULL, " ");
      b = (unsigned int)strtoul(token, &ptr, 10);
      array_lados[i]->v = a;
      array_lados[i]->w = b;
    }
  }
  return array_lados;
}

/*
int func_insertar_vert(u32 nombre, hash_table ht){
  
    add_ht_entry(nombre, ht);

  return 0;
}
*/
/*
int insert_edge(u32 v_key, u32 w_key, hash_table ht){
  vertice *v = ht_put(v_key, ht);
  vertice *w = ht_put(w_key, ht); //Notese que put es idempotente (No genera duplicados)
  v -> vecinos = (in_list(w_key, v -> vecinos)) ? v -> vecinos : addl_ptr(w, v -> vecinos);
  w -> vecinos = (in_list(v_key, w -> vecinos)) ? w -> vecinos : addl_ptr(v, w -> vecinos);
  //Puede que eñ chequeo de si el vecino está en la lista sea inecesario. Hay que preguntarle
  // al profe si podemos asumir que no hay lados duplicados en el dimacs.
  return 0;
}

int print_graph(hash_table ht){
  int M = ht->size;
  list lista = NULL;
  vertice *vert , *vecino = NULL;
  u32 longitud_lista = 0;
  for (u32 i = 0; i < M; i++)
  {
    vert = ht_get(i, ht);
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
*/
/*
int main(int argc, char **argv)
{
  Lado_st *infoEdge = NULL;
  Lado_st **array = NULL;
  u32 M = 0;
  hash_table ht = NULL;

  infoEdge = parse_p_edge_n_m();
  M = infoEdge->w;
  array = parse_edge(infoEdge);

  for (int i = 0; i < M; i++)
  {
    printf("array de carga (%d ,%d) \n", array[i]->v, array[i]->w);
  }

  ht = new_ht(M);

  for (int i = 0; i < M; i++)
  {
    insert_edge(array[i]->v, array[i]->w, ht);
  }

  print_graph(ht);

  return 0;
}
*/