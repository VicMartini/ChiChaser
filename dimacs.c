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

Lado_st **parse_edge_from_dimacs(Lado_st *lados)
{
  char buffer[80];
  char *readStr;
  char *token, *ptr;
  u32 a, b, M = 0;
  Lado_st **array_lados = NULL;
  readStr = buffer;
  M = lados->w;
  array_lados = (Lado_st **)calloc(M, sizeof(Lado_st));
  for (u32 i = 0; i < M; i++)
  {
    array_lados[i] = calloc(1, sizeof(struct Lado));
  }

  for (u32 i = 0; i < M; i++)
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
