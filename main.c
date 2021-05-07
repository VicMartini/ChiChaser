#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <errno.h>
#include <time.h>
#include "RomaVictor.h"

typedef struct params_st{
    u32 p[6]; // struct para a,b,c,d,e,f
}params;

int main(int argc, char *argv[])
{ 
    char *endptr;
    long val;
    params param;// parametros 

    if(argc != 7){
        printf("Error Arguments \n");
        return -1;
    }
    
    errno = 0;
    for (int i = 0; i < argc-1; i++)
    {
        val = strtol(argv[i+1], &endptr, 10);

        /* check posibles errores de entrada*/
        if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
                || (errno != 0 && val == 0)) {
            perror("strtol");
            exit(EXIT_FAILURE);
        }

        if (endptr == argv[i]) {
            fprintf(stderr, "No digits were found\n");
            exit(EXIT_FAILURE);
        }

        if (val < 0 || val >= UINT_MAX){
            fprintf(stderr, "range out of u32 \n");
            exit(EXIT_FAILURE);
        }
        // set val al struct
        param.p[i] = (u32) val;
    }
     
    double elapsed_time;
    clock_t t = clock();
    Grafo g = ConstruccionDelGrafo();
    u32 n = NumeroDeVertices(g);
    u32 m = NumeroDeLados(g);
    t = clock() - t;
    elapsed_time = (double)t / CLOCKS_PER_SEC;
    printf("Time creating: %f\n ORIGINAL\n", elapsed_time);
    printf("numero vertices, n = %d, numero lados, m = %d", n, m);
    printf("Δ = %u | δ = %u\n", g->Delta, g->delta);
    u32 esBipartito = Biartitotwo(g);
    
    if(esBipartito){
        printf("Es Bipartito: \n");
        return 0;
    }
    t = clock();

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