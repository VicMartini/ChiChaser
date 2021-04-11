#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "RomaVictor.h"

int main(void)
{
    Grafo g = ConstruccionDelGrafo();
    vertice **iterator = g->vertices->iterator;
    for (u32 i = 0; i < g->num_vertices; ++i)
    {
        for (u32 j = 0; j < iterator[i]->grado; ++j)
        {
            FijarPesoLadoConVecino(j, i, j + i, g);
        }
    }
    print_graph(g);
    printf("Δ = %d | δ = %d\n", g->Delta, g->delta);
}