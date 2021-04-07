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
    vertice vecino;
    u32 longitud_lista = 0;
    if (lines > M)
        return 1;
    for (u32 i = 0; i < lines; i++)
    {
        vert = g->vertices[i];
        printf("%u: vertice: %u -> \n", g->orden[i], vert.nombre);
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

void insert_edge(u32 v_key, u32 w_key, Grafo g, hash_table ht)
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
    new_graph->num_lados = M;
    new_graph->vertices = calloc(N, sizeof(vertice));
    new_graph->orden = calloc(N, sizeof(u32));

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
        new_graph->orden[j] = j;
        v_degree = new_graph->vertices[j].vecinos->ocupation;
        new_graph->vertices[j].pesos = calloc(v_degree, sizeof(u32));
        new_graph->vertices[j].grado = v_degree;
        min_degree = (v_degree < min_degree) ? v_degree : min_degree;
        max_degree = (v_degree > max_degree) ? v_degree : max_degree;
    }
    new_graph->Delta = max_degree;
    new_graph->delta = min_degree;

    for (u32 i = 0; i < M; i++)
    {
        free(array[i]);
    }
    free(array);
    free(infoEdge);
    
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

u32 NumeroDeLados(Grafo G)
{
    return G->num_lados;
}

u32 NumeroDeVertices(Grafo G)
{
    return G->num_vertices;
}

u32 PesoLadoConVecino(u32 j, u32 i, Grafo G)
{
    u32 n = G->num_vertices;
    if (i < n && j < G->vertices[i].grado)
        return G->vertices[i].pesos[j];
    else
        return 0;
};
u32 OrdenVecino(u32 j, u32 i, Grafo G)
{
    if (i >= G->num_vertices || j >= G->vertices[i].grado)
        return 0;
    u32 *o = G->orden;
    return o[darray_get(j, G->vertices[i].vecinos)];
}

Grafo CopiarGrafo(Grafo G)
{
    Grafo clone = malloc(sizeof(struct GrafoSt));
    clone->Delta = G->Delta;
    clone->delta = G->delta;
    clone->num_vertices = G->num_vertices;
    clone->num_lados = G->num_lados;
    clone->vertices = calloc(G->num_vertices, sizeof(vertice));
    clone->orden = calloc(G->num_vertices, sizeof(u32));

    for (u32 j = 0; j < G->num_vertices; ++j)
    {
        clone->orden[j] = G->orden[j];
        clone->vertices[j].nombre = G->vertices[j].nombre;
        clone->vertices[j].grado = G->vertices[j].grado;
        clone->vertices[j].pesos = calloc(clone->vertices[j].grado, sizeof(u32));
        clone->vertices[j].vecinos = darray_copy(G->vertices[j].vecinos);
        memcpy(clone->vertices[j].pesos, G->vertices[j].pesos, sizeof(u32) * G->vertices[j].grado);
    }
    return clone;
}

void DestruccionDelGrafo(Grafo G)
{
    for (u32 i = 0; i < G->num_vertices; ++i)
    {
        delete_darray(G->vertices[i].vecinos);
        free(G->vertices[i].pesos);
    }
    free(G->orden);
    free(G->vertices);
    G->orden = NULL;
    G->vertices = NULL;
    free(G);
}

// Funciones para extraer información de los vertices

u32 Nombre(u32 i, Grafo G)
{
    if (i >= G->num_vertices)
        return 0;
    u32 *o = G->orden;
    return G->vertices[o[i]].nombre;
}

u32 Color(u32 i, Grafo G)
{
    if (i >= G->num_vertices)
        return 0;
    u32 *o = G->orden;
    return G->vertices[o[i]].color;
}

u32 Grado(u32 i, Grafo G)
{
    if (i >= G->num_vertices)
        return 0;
    u32 *o = G->orden;
    return G->vertices[o[i]].grado;
}

// Funciones para extraer informacion de los vecinos de un vertice
u32 ColorVecino(u32 j, u32 i, Grafo G)
{
    if (i >= G->num_vertices || j >= G->vertices[i].grado)
        return 0;
    u32 *o = G->orden;
    u32 neigh_pos = darray_get(j, G->vertices[o[i]].vecinos);
    return G->vertices[neigh_pos].color;
};
u32 NombreVecino(u32 j, u32 i, Grafo G)
{
    if (i >= G->num_vertices || j >= G->vertices[i].grado)
        return 0;
    u32 *o = G->orden;
    u32 neigh_pos = darray_get(j, G->vertices[o[i]].vecinos);
    return G->vertices[neigh_pos].nombre;
};
//Funciones para modificar datos de vertices

char FijarColor(u32 x, u32 i, Grafo G)
{
    if (i >= G->num_vertices)
        return 1;
    G->vertices[i].color = x;
    return 0;
}

char FijarOrden(u32 i, Grafo G, u32 N)
{
    if (i >= G->num_vertices || N >= G->num_vertices)
        return 1;
    G->orden[N] = i;
    return 0;
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