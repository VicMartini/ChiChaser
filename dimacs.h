#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

typedef uint32_t u32;

struct Lado
{
  u32 v;
  u32 w;
};
typedef struct Lado Lado_st;

char *parse_correct_form_edge(char *str);
Lado_st *parse_p_edge_n_m(void);
Lado_st **parse_edge_from_dimacs(Lado_st *lados);
