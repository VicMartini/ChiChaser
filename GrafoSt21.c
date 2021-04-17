#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include "GrafoSt21.h"
typedef uint32_t u32;

u32 print_graph(GrafoSt *g, u32 lines)
{
    u32 M = g->num_vertices;
    vertice vert;
    vertice vecino;
    u32 longitud_lista = 0;
    if (lines > M)
        return 1;
    for (u32 i = 0; i < lines; i++)
    {
        vert = g->vertices[g->orden[i]];
        printf("%u: vertice: %u -> \n", i, vert.nombre);
        printf("  vecinos:\n");
        printf("( \n");
        longitud_lista = vert.grado;
        printf("grado: %u \n", longitud_lista);
        for (u32 i = 0; i < longitud_lista; i++)
        {
            vecino = g->vertices[darray_get(i, vert.vecinos)];
            printf("(v: %u, peso: %u )", vecino.nombre, vert.pesos[i]);
        }
        printf("\n ) \n");
        printf("\n");
    }
    return 0;
}

u32 delta(GrafoSt *g)
{
    return g->Delta;
}
