#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
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

    for (u32 j = 0; j < G->num_vertices; ++j)
    {
        clone->orden[j] = G->orden[j];
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
        //printf("\nNumero de vertices : %u, i: %u, j: %u\n",G->num_vertices,i,j);
        return 0;
    }
    u32 neigh_index = darray_get(j, G->vertices[o[i]].vecinos);
    //printf("\n| %d %d |\n",j, i);
    //printf("\nNombreVecino: %d, Orden: %d\n", NombreVecino(j,i, G), G->vertices[neigh_index].orden);
    return G->vertices[neigh_index].orden;

}

//Funciones para modificar datos de vertices

char FijarColor(u32 x, u32 i, Grafo G)
{   
    u32 *o= G->orden;
    if (i >= G->num_vertices)
        return 1;
    G->vertices[o[i]].color = x;
    return 0;
}

char FijarOrden(u32 i, Grafo G, u32 N)
{
    if (i >= G->num_vertices || N >= G->num_vertices)
        return 1;
    G->orden[N] = i;
    G->vertices[i].orden = N;
    //printf(" %d : %d\n",N, i);
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

char AleatorizarVertices(Grafo G, u32 R)
{
    srand(R);
    //Vamos a usar la versión "inside-out" del
    // Fisher-Yates shuffle para inicializar
    //un arreglo con una permutación aleatoria
    //de [0:N)
    u32 *a = calloc(G->num_vertices, sizeof(u32));
    u32 r;
    for (u32 i = 0; i < G->num_vertices; ++i)
    {
        r = rand() % (i + 1);
        if (r != i)
            a[i] = a[r];
        a[r] = i;
    }
    for (u32 j = 0; j < G->num_vertices; ++j)
    {
        FijarOrden(a[j], G, j);
    }
    free(a);
    return 0;
}

u32 Greedy(Grafo G)
{
    u32 n = G->num_vertices;
    hash_table ht; //Vamos a usar la ht para calcular
                   //eficientemente el minimo color que ocurre en los vecinos
    u32 neigh_color;
    u32 degree;
    u32 min_color;
    u32 max_chosen_color = 0;
    for (u32 i = 0; i < n; ++i)
    {   
        min_color = 0;
        degree = Grado(i, G);
        ht = new_ht((degree > i + 1) ? i + 1 : degree);
        //printf("%d: Coloring vertex: %d\n", i, Nombre(i, G));
        for (u32 j = 0; j < degree; ++j)
        {
            neigh_color = ColorVecino(j, i, G);
            if (OrdenVecino(j, i, G) < i && !in_ht(neigh_color, ht))
            {
                ht_put(neigh_color, 0, ht);
                //printf("%d ", neigh_color);
            }
        }
        while (in_ht(min_color, ht))
            ++min_color;
        max_chosen_color = (max_chosen_color > min_color) ? max_chosen_color : min_color;
        //printf("\n Chose color %d\n", min_color);
        destroy_ht(ht);
        FijarColor(min_color, i, G);
    }
    return max_chosen_color + 1;
}

char Bipartito(Grafo G) //Corre BFS en G creando un arbol
{
    u32 j = 1;
    u32 n = NumeroDeVertices(G);
    u32 k, p, orden_vecino;
    // vertice p;
    queue q;
    while(j < n)
    {
        u32 v = j;
        //Encontramos un vertice x no coloreado.
        while(Color(v, G) /*G->vertices[v].color */ != 0xFFFFFFFF && v < n - 1)
        {
            v++;
        }
        FijarColor(1, v, G);
        // G->vertices[v].color = 1; // v es el indice de x en el orden de guardado
        q = new_queue();
        enqueue(q, v); // q es una cola con el indice de x como unico elemento
        while(!queue_is_empty(q))
        {   
            // p = G->vertices[dequeue(q)];
            p = front(q); 
            dequeue(q);
            for(u32 h = 0; h < Grado(p, G); ++h)
            {   
                //k = p.vecinos->elements[h]; // Indice del vecino en el orden interno
                orden_vecino = OrdenVecino(h, p, G);
                if( Color(orden_vecino, G) == 0xFFFFFFFF)
                {
                    enqueue(q, orden_vecino);
                    FijarColor(3-Color(p, G), orden_vecino, G);
                    //G->vertices[k].color = 3 - p.color;
                    ++j;
                }
            }
        }
    }
    vertice x;
    vertice w;
    for (u32 i = 0; i < n; ++i)
    {
        //x = G->vertices[i];
        for (u32 j=0; j < Grado(i, G) /*G->vertices[i].grado*/; ++j)
        {   
            //w = G->vertices[x.vecinos->elements[j]];
            
            if (Color(i, G) == ColorVecino(j, i, G))
                return 0;
        }

    }
    return 1;
}
char Biartitotwo(Grafo G){
    u32 k = 1;
    u32 n;
    u32 orden_vecino;
    queue q;
    u32 v = 0;
    n = NumeroDeVertices(G);
    while(k < n)
    {
        // Si k < n, tenemos asegurada la exitencia de un vertice que todavia no fué coloreado
        while(Color(v, G) != 0xFFFFFFFF)
            v++;


        //asigno el primer color 
        FijarColor(1, v, G);
        //printf("Color: %u\n",Color(v, G));
        ++k;
        // creo la cola
        q = new_queue();
        enqueue(q, v);

        // corro bfs(x) 
        while(!queue_is_empty(q)){        
            u32 u = front(q);
            //print_queue(q);
            dequeue(q);
            //print_queue(q);
            for(u32 j=0; j < Grado(u, G); j++){
                
                orden_vecino = OrdenVecino(j, u, G);
                //printf("u:%u, orden_vecino:%u ,color(%u,%u) \n", G->orden[u] , orden_vecino, Color(u, G), ColorVecino(j, u, G));
                if(ColorVecino(j, u, G) == 0xFFFFFFFF){
                    
                    FijarColor(1-Color(u, G), orden_vecino, G);
                    //printf("FijarColor(%u,%u,Grafo)\n",1-Color(u, G),orden_vecino, G);
                    ++k;
                    enqueue(q, orden_vecino);
                }
                else if(ColorVecino(j, u, G) == Color(u, G))
                    return 0;
            }

        }
        return 1;
    }
}

void positionArray(Grafo G)
{

    u32 n = NumeroDeVertices(G);
    u32 *array = calloc(n, sizeof(u32));

    for (u32 i = 0; i < n; i++)
    {
        array[i] = Nombre(i, G);
    }

    u32 result=-1;

    for (u32 i = 0; i < n; i++)
    {    
        result = getIndexInSortedArray(array, n, i);
        FijarOrden(i, G, result);
    }
    
    free(array);   
    
}

u32 getIndexInSortedArray(u32 *arr, u32 n, u32 idx)
{
    /* Count of elements smaller than current
        element plus the equal element occurring
        before given index*/
    u32 result = 0;
    for (u32 i = 0; i < n; i++) {
        // If element is smaller then increase
        // the smaller count
        if (arr[i] < arr[idx])
            result++;
 
        // If element is equal then increase count
        // only if it occurs before
        if (arr[i] == arr[idx] && i < idx)
            result++;
    }
    return result;
}