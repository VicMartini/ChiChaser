#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "GrafoSt.h"



int main(void)
{
    Grafo g = ConstruccionDelGrafo();
    print_graph(g);
    printf("Δ = %d | δ = %d\n", g->Delta, g->delta);
}