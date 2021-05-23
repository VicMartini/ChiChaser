#include <stdio.h>
#include "UnleashHell.h"

char AleatorizarVertices(Grafo G, u32 R)
{
    srand(R);
    //Vamos a usar la versión "inside-out" del
    // Fisher-Yates shuffle para inicializar
    //un arreglo con una permutación aleatoria
    //de [0:N)
    u32 *a = calloc(NumeroDeVertices(G), sizeof(u32));
    if(a == NULL)
        return 1;
    u32 r;
    for (u32 i = 0; i < NumeroDeVertices(G); ++i)
    {
        r = rand() % (i + 1);
        if (r != i)
            a[i] = a[r];
        a[r] = i;
    }
    for (u32 j = 0; j < NumeroDeVertices(G); ++j)
    {
        FijarOrden(a[j], G, j);
    }
    free(a);
    return 0;
}


char Bipartito(Grafo G)
{
    u32 k = 1;
    u32 n;
    u32 orden_vecino;
    queue q = NULL;
    u32 v = 0;
    n = NumeroDeVertices(G);
    while (k < n)
    {
        // Si k < n, tenemos asegurada la exitencia de un vertice que todavia no fué coloreado
        while (Color(v, G) != 0xFFFFFFFF)
            v++;

        FijarColor(1, v, G);
        ++k;
        q = new_queue();
        enqueue(q, v);

        while (!queue_is_empty(q))
        {
            u32 u = front(q);
            dequeue(q);
            for (u32 j = 0; j < Grado(u, G); j++)
            {

                orden_vecino = OrdenVecino(j, u, G);
                if (ColorVecino(j, u, G) == 0xFFFFFFFF)
                {

                    FijarColor(1 - Color(u, G), orden_vecino, G);
                    ++k;
                    enqueue(q, orden_vecino);
                }
                else if (ColorVecino(j, u, G) == Color(u, G)){
                    destroy_queue(q);
                    return 0;
                }
            }
        }
    }
    destroy_queue(q);
    return 1;
}

u32 Greedy(Grafo G)
{
    u32 n = NumeroDeVertices(G);
    u32 neigh_color;
    u32 degree;
    u32 min_color;
    u32 max_chosen_color = 0;
    bool *used = calloc(Delta(G)+1,sizeof(bool));
    queue q = new_queue();
    if(used == NULL)
        return 0xFFFFFFFF;
    for (u32 i = 0; i < n; ++i)
    {
        min_color = 0;
        degree = Grado(i, G);
        for (u32 j = 0; j < degree; ++j)
        {
            neigh_color = ColorVecino(j, i, G);
            if (OrdenVecino(j, i, G) < i && !used[neigh_color])
            {
                used[neigh_color] = 1;
                enqueue(q, neigh_color);
            }
        }
        while (used[min_color])
            ++min_color;
        max_chosen_color = (max_chosen_color > min_color) ? max_chosen_color : min_color;
        u32 f;
        while (!queue_is_empty(q))
        {
            f = front(q);
            dequeue(q);
            used[f] = false;
        }
        
        FijarColor(min_color, i, G);
    }
    free(used);
    destroy_queue(q);
    return max_chosen_color + 1;
}



char OrdenPorBloqueDeColores(Grafo G, u32 *perm)
{
    u32 n = NumeroDeVertices(G);
    u32 i;
    u32 max_color = 0;
    for (u32 i = 0; i < n; i++)
    {
        if(max_color < Color(i,G)) max_color = Color(i,G);
    }
    u32 r = max_color + 1;
    //Chequeamos que cada uno de los números en el rango 0..r-1 esten exactamente una vez
    // para comprobar que perm es una permutación.
    u32 *counts = calloc(r, sizeof(u32));
    for(i = 0; i < r; ++i)
    {
        if(perm[i]>r - 1)
        {
            return 1;
        }
        ++counts[perm[i]];
    }
    for(i = 0; i < r; ++i)
        if(counts[i] != 1) return 1;
    free(counts);
    //Vamos a necesitar tener acceso al orden natural, por eso primero vamos a hacer que el orden interno
    //coincida con el orden natural.
    for(i = 0; i < n; ++i)
        FijarOrden(i, G, i);
    //Cada queue va a guardar las posiciones del orden natural que tienen vertices con un determinado color.
    struct queue **bloques = calloc(r, sizeof(struct queue));
    for(i = 0; i < r; ++i)
        bloques[i] = new_queue();
    for(i = 0; i < n; ++i)
        enqueue(bloques[Color(i, G)], i);
    //Ahora vamos a usar FijarOrden() para ir ubicando los bloques de vertices del mismo color
    //en el orden dado por perm
    u32 k = 0;
    u32 p = 0;
    for(i = 0; i < r; ++i)
    {
        while(!queue_is_empty(bloques[perm[i]]))
        {
            p = front(bloques[perm[i]]); // El p-esimo vertice del orden natural es de color perm[i]
            dequeue(bloques[perm[i]]);
            FijarOrden(k, G, p);
            ++k;
        }
    }

    for (u32 i = 0; i < r; i++)
    {   
        destroy_queue(bloques[i]);
    }
    free(bloques);
    return 0;
}