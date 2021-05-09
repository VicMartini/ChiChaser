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
    params param; //parametros
    u32 a,b,c,d,e,f;

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
        // set val al struct p[0]=a, p[1]=b,...,p[5]=f
        param.p[i] = (u32) val;
    }

    a = param.p[0];
    b = param.p[1];
    c = param.p[2];
    d = param.p[3];
    e = param.p[4];
    f = param.p[5];

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
    
    // 3
    if(esBipartito){
        printf("Es Bipartito: \n");
        return 0;
    }
    t = clock();


    //5
    positionArray(g);
    u32 ordenNat = Greedy(g);
    printf("Greedy Orden natural: %d \n", ordenNat);
    // aleatorizar vertices
    u32 result = UINT_MAX;
    u32 greedy, iorden;
    for (u32 i = 0; i < a; i++)
    {
        AleatorizarVertices(g, f+i);
        
        if(greedy=Greedy(g) < result){
            printf("(5)-Colores con Greedy: %d \n", greedy);
            result = greedy;
            iorden = f+i;
        }
    }
    // salvo que sea el ultimo 
    if(iorden != f+a){
        AleatorizarVertices(g, iorden);
        result = Greedy(g);
        printf("mejor ordenamiento que da el mejor greedy:%d \n", result);
    }


    //6 
    for (u32 i = 0; i < b; i++)
    {
        //OrdenPorBloqueDeColores(g, perm);
    }
    
   
}