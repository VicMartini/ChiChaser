#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include "GrafoSt.h"
typedef uint32_t u32;

u32 print_graph(Grafo g, u32 lines)
{
    u32 M = g->num_vertices;
    vertice vert;
    vertice *vecino = NULL;
    u32 longitud_lista = 0;
    if (lines > M)
        return 1;
    for (u32 i = 0; i < lines; i++)
    {
        vert = g->vertices[i];
        printf("%u: vertice: %u -> \n", i, vert.nombre);
        printf("  vecinos:\n");
        printf("( \n");
        longitud_lista = vert.grado;
        printf("grado: %u \n", longitud_lista);
        for (u32 i = 0; i < longitud_lista; i++)
        {
            vecino = vert.vecinos->elements[i];
            if (vecino != NULL)
            {
                printf("(v: %u, peso: %u )", vecino->nombre, vert.pesos[i]);
            }
        }
        printf("\n ) \n");
        printf("\n");
    }
    return 0;
}

void insert_edge(u32 v_key, u32 w_key, Grafo g, hash_table ht)
{
    vertice *v_addr = ht_get(v_key, ht);
    vertice *w_addr = ht_get(w_key, ht);
    if (!v_addr)
    {
        g->vertices[ht->ocupation] = Vertice(v_key);
        v_addr = g->vertices + ht->ocupation;
        ht_put(v_key, v_addr, ht);
    }
    if (!w_addr)
    {
        g->vertices[ht->ocupation] = Vertice(w_key);
        w_addr = g->vertices + ht->ocupation;
        ht_put(w_key, w_addr, ht);
    }
    darray_push(w_addr, v_addr->vecinos);
    darray_push(v_addr, w_addr->vecinos);
}

Grafo ConstruccionDelGrafo(void)
{
    Grafo new_graph = malloc(sizeof(struct GrafoSt));
    Lado_st *infoEdge = NULL;
    Lado_st **array = NULL;
    u32 N = 0;
    u32 M = 0;
    u32 v_degree = 0;
    u32 max_degree = 0;
    u32 min_degree = 0xFFFFFFFF;

    infoEdge = parse_p_edge_n_m();
    N = infoEdge->v;
    M = infoEdge->w;
    array = parse_edge(infoEdge);
    new_graph->num_vertices = N;
    new_graph->vertices = calloc(N, sizeof(vertice));

    hash_table index = new_ht(N); //La hashtable va a servir como un indice para la
                                  //construcción del grafo.

    for (u32 i = 0; i < M; i++)
    {
        insert_edge(array[i]->v, array[i]->w, new_graph, index);
    }
    //Ya no necesitamos la hashtable.
    destroy_ht(index);
    for (u32 j = 0; j < N; ++j)
    {
        v_degree = new_graph->vertices[j].vecinos->ocupation;
        new_graph->vertices[j].pesos = calloc(v_degree, sizeof(u32));
        new_graph->vertices[j].grado = v_degree;
        min_degree = (v_degree < min_degree) ? v_degree : min_degree;
        max_degree = (v_degree > max_degree) ? v_degree : max_degree;
    }
    new_graph->Delta = max_degree;
    new_graph->delta = min_degree;
    return new_graph;
}

u32 Delta(Grafo g)
{
    return g->Delta;
}

u32 delta(Grafo g)
{
    return g->Delta;
}

u32 FijarPesoLadoConVecino(u32 j, u32 i, u32 p, Grafo G)
{
    ;
    u32 n = G->num_vertices;
    if (i < n && j < G->vertices[i].grado)
    {
        G->vertices[i].pesos[j] = p;
        return 0;
    }
    else
    {
        return 1;
    }
};
u32 PesoLadoConVecino(u32 j, u32 i, Grafo G)
{
    u32 n = G->num_vertices;
    if (i < n && j < G->vertices[i].grado)
        return G->vertices[i].pesos[j];
    else
        return 0;
};

Grafo CopiarGrafo(Grafo G)
{
    vertice *new_addr;
    u32 relative_pos;
    Grafo clone = malloc(sizeof(struct GrafoSt));
    clone->Delta = G->Delta;
    clone->delta = G->delta;
    clone->num_vertices = G->num_vertices;
    clone->num_lados = G->num_lados;
    clone->vertices = calloc(G->num_vertices, sizeof(vertice));

    for (u32 j = 0; j < G->num_vertices; ++j)
    {
        clone->vertices[j].nombre = G->vertices[j].nombre;
        clone->vertices[j].grado = G->vertices[j].grado;
        clone->vertices[j].pesos = calloc(clone->vertices[j].grado, sizeof(u32));
        clone->vertices[j].vecinos = new_darray();
        for (u32 i = 0; i < G->vertices[j].grado; ++i)
        {
            clone->vertices[j].pesos[i] = G->vertices[j].pesos[i];
            relative_pos = (vertice *)G->vertices[j].vecinos->elements[i] - G->vertices;
            new_addr = (vertice *)clone->vertices + relative_pos;
            darray_push(new_addr, clone->vertices[j].vecinos);
            /*
        */
        }
    }
    return clone;
}
