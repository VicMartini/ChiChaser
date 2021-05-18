#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "RomaVictor.h"
typedef uint32_t u32;

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
    u32 N = 0;
    u32 M = 0;
    u32 v_degree = 0;
    u32 max_degree = 0;
    u32 min_degree = 0xFFFFFFFF;
    Lado_st edge;
    infoEdge = parse_p_edge_n_m();
    N = infoEdge->v;
    M = infoEdge->w;
    new_graph->num_vertices = N;
    new_graph->num_lados = M;
    new_graph->vertices = calloc(N, sizeof(vertice));
    new_graph->orden = calloc(N, sizeof(u32));
    new_graph->orden_natural = calloc(N, sizeof(u32));

    hash_table index = new_ht(N); //La hashtable va a servir como un indice para la
                                  //construcción del grafo.
    for (u32 i = 0; i < M; ++i)
    {
        edge = parse_edge();
        insert_edge(edge.v, edge.w, new_graph, index);
    }

    //Ya no necesitamos la hashtable.
    destroy_ht(index);
    for (u32 j = 0; j < N; ++j)
    {
        new_graph->orden[j] = j;
        new_graph->vertices[j].orden = j;
        v_degree = new_graph->vertices[j].vecinos->ocupation;
        new_graph->vertices[j].pesos = calloc(v_degree, sizeof(u32));
        new_graph->vertices[j].grado = v_degree;
        min_degree = (v_degree < min_degree) ? v_degree : min_degree;
        max_degree = (v_degree > max_degree) ? v_degree : max_degree;
    }
    OrdenNatural(new_graph);
    new_graph->Delta = max_degree;
    new_graph->delta = min_degree;

    free(infoEdge);

    return new_graph;
}

u32 Delta(Grafo g)
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

Grafo CopiarGrafo(Grafo G)
{
    Grafo clone = malloc(sizeof(struct GrafoSt));
    clone->Delta = G->Delta;
    clone->delta = G->delta;
    clone->num_vertices = G->num_vertices;
    clone->num_lados = G->num_lados;
    clone->vertices = calloc(G->num_vertices, sizeof(vertice));
    clone->orden = calloc(G->num_vertices, sizeof(u32));
    clone->orden_natural = calloc(G->num_vertices, sizeof(u32));

    for (u32 j = 0; j < G->num_vertices; ++j)
    {
        clone->orden[j] = G->orden[j];
        clone->orden_natural[j] = G->orden_natural[j];
        clone->vertices[j].nombre = G->vertices[j].nombre;
        clone->vertices[j].grado = G->vertices[j].grado;
        clone->vertices[j].color = G->vertices[j].color;
        clone->vertices[j].orden = G->vertices[j].orden;
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
    free(G->orden_natural);
    G->orden_natural = NULL;
    G->orden = NULL;
    G->vertices = NULL;
    free(G);
    G = NULL;
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
    u32 *o = G->orden;
    if (i >= G->num_vertices || j >= G->vertices[o[i]].grado)
        return 0;
    u32 neigh_pos = darray_get(j, G->vertices[o[i]].vecinos);
    return G->vertices[neigh_pos].color;
};
u32 NombreVecino(u32 j, u32 i, Grafo G)
{
    u32 *o = G->orden;
    if (i >= G->num_vertices || j >= G->vertices[o[i]].grado)
        return 0;
    u32 neigh_pos = darray_get(j, G->vertices[o[i]].vecinos);
    return G->vertices[neigh_pos].nombre;
};

u32 PesoLadoConVecino(u32 j, u32 i, Grafo G)
{
    u32 n = G->num_vertices;
    u32 *o = G->orden;
    if (i < n && j < G->vertices[i].grado)
        return G->vertices[o[i]].pesos[j];
    else
        return 0;
};
u32 OrdenVecino(u32 j, u32 i, Grafo G)
{
    u32 *o = G->orden;
    if (i >= G->num_vertices || j >= G->vertices[o[i]].grado)
    {
        return 0;
    }
    u32 neigh_index = darray_get(j, G->vertices[o[i]].vecinos);

    return G->vertices[neigh_index].orden;
}

//Funciones para modificar datos de vertices

char FijarColor(u32 x, u32 i, Grafo G)
{
    u32 *o = G->orden;
    if (i >= G->num_vertices)
        return 1;
    G->vertices[o[i]].color = x;
    return 0;
}

char FijarOrden(u32 i, Grafo G, u32 N)
{
    if (i >= G->num_vertices || N >= G->num_vertices)
        return 1;
    u32 *oN = G->orden_natural;
    G->orden[i] = oN[N];
    G->vertices[oN[N]].orden = i;
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



void swap(u32 *a, u32 *b) {
  u32 t = *a;
  *a = *b;
  *b = t;
}

u32 partition(u32 array[], u32 b[], int low, int high) {
  
  int pivotIndex = rand() % (high - low + 1) + low; //(high - low) / 2;
  u32 pivot = array[pivotIndex];
  
  int i = (low - 1);

  swap(&array[pivotIndex], &array[high]);
  swap(&b[pivotIndex], &b[high]);
  pivotIndex = high;
  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {
        
      i++;
      
      swap(&array[i], &array[j]);
      swap(&b[i], &b[j]);

    }
  }

  swap(&array[i + 1], &array[pivotIndex]);
  swap(&b[i + 1], &b[pivotIndex]);
  return (i + 1);
}

void quickSort(u32 array[],u32 b[], int low, int high) {
    if (low < high) {
        u32 pi = partition(array,b, low, high);
        quickSort(array,b, low, pi - 1);
        quickSort(array,b, pi + 1, high);
  }
}

void OrdenNatural(Grafo G)
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



/*
  toma el tamaño de arreglo
  crea un array , lo inicializa y luego aleatoriza los valores.
  se debe liberar memoria
*/
u32* suff_array(u32 ncolor){
    u32 *array_perm = calloc(ncolor, sizeof(u32));
    for (u32 i = 0; i < ncolor; i++)
    {
        array_perm[i] = i;
    }
    srand(time(NULL));
    for (u32 i = 0; i < ncolor; i++)
    {
        u32 temp = array_perm[i];
        u32 randomIndex = rand()%ncolor;
        array_perm[i] = array_perm[randomIndex];
        array_perm[randomIndex] = temp;
    }
    
    return array_perm;
}