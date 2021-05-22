#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include "rQuickSort.h"
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


Lado_st parse_edge(void)
{
    char buffer[80];
    char *readStr;
    char *token, *ptr;
    Lado_st edge = {0xFFFFFFFF, 0xFFFFFFFF};
    u32 a, b = 0;
    readStr = buffer;

    if (fgets(readStr, sizeof(buffer), stdin) == NULL)
        return edge;
    if (readStr[0] == 'e')
    {
        token = strtok(readStr, "e ");
        a = (u32)strtoul(token, &ptr, 10);
        token = strtok(NULL, " ");
        b = (u32)strtoul(token, &ptr, 10);
        edge.v = a;
        edge.w = b;
    }

    return edge;
}

void insert_edge(u32 v_key, u32 w_key, GrafoSt *g, hash_table ht)
{
    u32 v_position = ht_get(v_key, ht);
    u32 w_position = ht_get(w_key, ht);
    if (v_position == 0xFFFFFFFF)
    {
        g->vertices[ht->ocupation] = Vertice(v_key);
        v_position = ht->ocupation;
        ht_put(v_key, v_position, ht);
    }
    if (w_position == 0xFFFFFFFF)
    {
        g->vertices[ht->ocupation] = Vertice(w_key);
        w_position = ht->ocupation;
        ht_put(w_key, w_position, ht);
    }
    darray_push(w_position, g->vertices[v_position].vecinos);
    darray_push(v_position, g->vertices[w_position].vecinos);
}

void GenerarOrdenNatural(GrafoSt *G)
{
    u32 n = G->num_vertices;
    u32 *a = calloc(n, sizeof(u32));
    u32 *b = calloc(n, sizeof(u32));
    for(u32 i = 0; i < n; ++i)
    {   
        a[i] = Nombre(i, G);
        b[i] = i;
    }
    quickSort(a, b, 0, n-1);
    for(u32 j = 0; j<n; ++j)
    {   
        G->orden_natural[j] = b[j];
    }
    free(a);
    free(b);
}


u32 delta(GrafoSt *g)
{
    return g->Delta;
}


