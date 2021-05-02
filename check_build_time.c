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
    elapsed_time = (double)t / CLOCKS_PER_SEC;
    printf("Time creating: %f\n ORIGINAL\n", elapsed_time);
    //print_graph(g, g->num_vertices);
    printf("Δ = %u | δ = %u\n", g->Delta, g->delta);
    Grafo h = CopiarGrafo(g);
    t = clock();
    u32 colors;
    for (u32 i = 0; i < 1; ++i)
    {
        AleatorizarVertices(h, time(0));
        colors = Bipartito(h);
    }
    t = clock() - t;
    elapsed_time = (double)t / CLOCKS_PER_SEC;
    printf("Used %d colors\n", colors);
    printf("Time shuffling order and running Greedy: %f\n SHUFFLED\n", elapsed_time / 60);
    print_graph(h, 4);
    printf("Δ = %u | δ = %u\n", h->Delta, h->delta);
    printf("Used %d colors\n", colors);
    DestruccionDelGrafo(g);
    DestruccionDelGrafo(h);
}