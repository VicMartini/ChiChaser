#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "darray.h"
typedef uint32_t u32;

typedef struct vertice_st
{
    u32 nombre;
    u32 color;
    u32 grado;
    u32 orden;
    u32 *pesos;
    darray vecinos;
} vertice;
vertice Vertice(u32 nombre);