#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "GrafoSt.h"



int main(void)
{   
    double elapsed_time;
    clock_t t = clock();
    Grafo g = ConstruccionDelGrafo();
    t = clock() - t;
    elapsed_time = (double)t / CLOCKS_PER_SEC;
    printf("Elapsed time: %f\n", elapsed_time);
    printf("Δ = %d | δ = %d\n", g->Delta, g->delta);
}