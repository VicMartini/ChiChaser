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
    printf("Time creating: %f\n", elapsed_time);
    printf("Δ = %u | δ = %u\n", g->Delta, g->delta);
    print_graph(g, g->num_vertices);
    t = clock();
    Grafo h = CopiarGrafo(g);
    t = clock() - t;
    elapsed_time = (double)t / CLOCKS_PER_SEC;
    //print_graph(h, 5);
    printf("Time copying: %f\n", elapsed_time);
    printf("Δ = %u | δ = %u\n", h->Delta, h->delta);
    DestruccionDelGrafo(g);
    DestruccionDelGrafo(h);
}