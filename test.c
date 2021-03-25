#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 compilar gcc test.c
 ./a.out < dimacs 

*/ 
char* parse_correct_form_edge(char *str);
int parse_p_edge_n_m(void);

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


readString = (char *)calloc(1, sizeof(char));

  while (fgets(readString, 1024, stdin)!= NULL) {
    if(readString[0]=='p'){
      if ((readString = parse_correct_form_edge(readString)) == NULL){
        return -1;
      }
      strToULong = strtoul(readString, &ptr, 10);
      printf("1-%d\n", strToULong);
      readString = strtok(NULL, " ");
      strToULong = strtoul(readString, &ptr, 10);
      printf("2-%d\n", strToULong);
    }
  }

return 0;
}

int main(int argc, char ** argv){

  parse_p_edge_n_m();
  return 0;
}