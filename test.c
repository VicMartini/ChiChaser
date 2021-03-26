#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
/*
 compilar gcc test.c
 ./a.out < dimacs 

*/ 
char* parse_correct_form_edge(char *str);
int parse_p_edge_n_m(void);
int parse_edge(void);
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


int parse_p_edge_n_m(void){
char *readString = NULL; 
unsigned int strToULong;
char *ptr = NULL;
bool flag = false;

readString = (char *)calloc(1, sizeof(char));

  while (!flag) {
    if(fgets(readString, 1024, stdin) == NULL)
      return -1;
    if(readString[0] == 'p'){
      if ((readString = parse_correct_form_edge(readString)) == NULL){
        return -1;
      }
      strToULong = strtoul(readString, &ptr, 10);
      printf("1-%d\n", strToULong);
      readString = strtok(NULL, " ");
      strToULong = strtoul(readString, &ptr, 10);
      printf("2-%d\n", strToULong);
      flag = true;
    }
  }

return 0;
}


int parse_edge(void){
  bool flag = false;
  char *readStr = NULL;
  char *token, *ptr = NULL;
  unsigned int a, b = 0;
  
  readStr = (char *) calloc(1, sizeof(char));

  for (int i = 0; i < 20; i++){
    if(fgets(readStr, 1024, stdin) == NULL)
      return -1;

    if(readStr[0] = 'e'){
      token = strtok(readStr, "e ");
      a = (unsigned int) strtoul(token, &ptr, 10);
      token = strtok(NULL, " ");
      b = (unsigned int) strtoul(token, &ptr, 10);
      printf("vertice A: %d - Vertice B: %d \n", a, b);
      

    }


  }
return 0;
}


int main(int argc, char ** argv){

  parse_p_edge_n_m();
  parse_edge();
  return 0;
}