#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include "GrafoSt21.h"
typedef uint32_t u32;

//Forward declarations para que no se queje gcc
u32 Nombre(u32 i, GrafoSt *G);
u32 OrdenVecino(u32 j, u32 i, GrafoSt *G);



u32 print_graph(GrafoSt *g, u32 lines)
{
    u32 M = g->num_vertices;
    vertice vert;
    vertice vecino;
    u32 longitud_lista = 0;
    if (lines > M)
        return 1;
    printf("-------------------------\n");
    for (u32 k= 0; k < lines; k++ )
    {
        printf("Nombre: %d, Orden: %d\n", Nombre(k,g),k);
    } 
    printf("-------------------------\n");
    for (u32 i = 0; i < lines; i++)
    {
        vert = g->vertices[g->orden[i]];
        printf("%u: vertice: %u c: %u -> \n", i, vert.nombre, vert.color);
        printf("  vecinos:\n");
        printf("( \n");
        longitud_lista = vert.grado;
        printf("grado: %u \n", longitud_lista);
        for (u32 j = 0; j < longitud_lista; j++)
        {
            vecino = g->vertices[darray_get(j, vert.vecinos)];
            printf("(%d >> v: %u, orden: %u, color: %u )", j, vecino.nombre, OrdenVecino(j,i,g), vecino.color);
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
