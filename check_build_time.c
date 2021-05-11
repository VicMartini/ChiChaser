#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "RomaVictor.h"

int main(void)
{
    double elapsed_time;
    clock_t t = clock();
    Grafo g = ConstruccionDelGrafo();
    t = clock() - t;
    for(u32 i = 0; i < g->num_vertices; ++i)
    {
        FijarOrden(i, g, i);
    }
    u32 greedy = Greedy(g);
    printf("Greedy:%d \n", greedy);
    elapsed_time = (double)t / CLOCKS_PER_SEC;
    printf("Time creating: %f\n ORIGINAL\n", elapsed_time);
    u32 perm[greedy];
    for(u32 i = 0; i < greedy; ++i)
        perm[i] = i;
    printf("Resultado orden por bloques : %d\n",OrdenPorBloquesDeColores(g,perm));
    //print_graph(g,20);
    /*
    for(u32 i = 0; i < g->num_vertices;++i)
    {
        printf("Nombre : %u, Color: %u\n", Nombre(i, g), Color(i, g));
    }
    */
    // printf("Δ = %u | δ = %u\n", g->Delta, g->delta);
    // Grafo h = CopiarGrafo(g);
    // t = clock();
    // u32 bipartite;
    // for (u32 i = 0; i < 1; ++i)
    // {
    //     /*
    //     for(int j = 0; j < h->num_vertices; ++j)
    //     {
    //         printf("%d,%d - %d\n",Nombre(j,h),j,h->vertices[h->orden[j]].orden);
    //     }
    //     */
    //     AleatorizarVertices(h, 42);
    //     /*
    //     for(int j = 0; j < h->num_vertices; ++j)
    //     {
    //         printf("%d,%d - %d\n",Nombre(j,h),j,h->vertices[h->orden[j]].orden);
    //     }
    //     */
    //     bipartite = Biartitotwo(h);
    // }

    // t = clock() - t;
    // //print_graph(h, NumeroDeLados(h)-1);
    // elapsed_time = (double)t / CLOCKS_PER_SEC;
    // printf("Used %d colors\n", bipartite);
    // printf("Time shuffling order and running Greedy: %f\n SHUFFLED\n", elapsed_time / 60);
    
    // printf("Δ = %u | δ = %u\n", h->Delta, h->delta);
    // printf("Is bipartite? %d\n", bipartite);
    // DestruccionDelGrafo(g);
    // DestruccionDelGrafo(h);
}