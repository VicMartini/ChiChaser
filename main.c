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
    Grafo G = ConstruccionDelGrafo();
    u32 n = NumeroDeVertices(G);
    u32 m = NumeroDeLados(G);
    t = clock() - t;
    elapsed_time = (double)t / CLOCKS_PER_SEC;
    printf("Time creating: %f\n ORIGINAL\n", elapsed_time);
    printf("numero vertices, n = %d, numero lados, m = %d \n", n, m);
    printf("Δ = %u | δ = %u\n", Delta(G), G->delta);
    u32 esBipartito = Biartitotwo(G);
    
    // 3
    printf("Item-3\n");
    if(esBipartito){
        printf("Es Bipartito: \n");
        return 0;
    }
    t = clock();


    //5
    printf("Item-5\n");
    OrdenNatural(G);
    u32 ordenNat = Greedy(G);
    printf("Greedy Orden natural: %d \n", ordenNat);
    // aleatorizar vertices
    u32 result = UINT_MAX;
    u32 greedy, iorden;
    for (u32 i = 0; i < a; i++)
    {
        AleatorizarVertices(G, f+i);
        
        if((greedy = Greedy(G)) < result){
            printf("Greedy con AleatorizarVertices: %d \n", greedy);
            result = greedy;
            iorden = f+i;
        }
    }
    // salvo que sea el ultimo 
    if(iorden != f+a){
        AleatorizarVertices(G, iorden);
        result = Greedy(G);
        printf("Greedy con AleatorizarVertices:%d \n", result);
    }


    //6 
    /*
        . Luego de esto, a partir de ese coloreo que se ha obtenido, se hacen b ordenamientos 
        usando OrdenPorBloqueDeColores() con distintos ordenes pseudoaleatorios de los colores,
        y corre Greedy() luego de cada uno de ellos, imprimiendo el n´umero de colores obtenido.
        Por el teorema dado en clase, si programaron OrdenPorBloqueDeColores() y Greedy()
        bien, la cantidad de colores no puede aumentar luego de cadar orden por bloque de
        colores mas greedy, asi que no hace falta salvar al mejor coloreo porque siempre ser´a el
        ´ultimo.
    */
    
    // result tiene el n° de colores 
    u32 result_greedy;
    printf("Item-6\n");
    printf("Greedy antes de inciar orden por bloques :%d \n", result);
    u32 r = UINT_MAX;
    u32 *array_perm = NULL;
    for (u32 i = 0; i < b; i++)
    {   
        array_perm = suff_array(result); // aleatoriza perm
        OrdenPorBloquesDeColores(G, array_perm);
        result_greedy = Greedy(G);
        if(result_greedy < r){
            r = result_greedy;
            printf("6- greedy con orden por bloques: %d \n", r);
        }
        
        free(array_perm); // free array allocado en suff_array
        array_perm = NULL;
    }
    

    // 7
    printf("Item-7 \n");

    for (u32 i = 0; i < c; i++) // ciclo externo 
    {  
        u32 color_G, color_H, color_W = UINT_MAX;
        u32 res_G, res_H, res_W;
        Grafo H = CopiarGrafo(G); 
        Grafo W = CopiarGrafo(G);
        // ciclo interno
        for (u32 j = 0; i < d; j++) 
        {   
            // rama 1 
            AleatorizarVertices(G, f+j);
            res_G = Greedy(G);
            if(res_G < color_G)
                color_G = res_G;

            // rama 2 
            array_perm[r];
            for (u32 i = r-1; i > 0 ; i--)
            {   //ordena array de mayor a menor
                array_perm[i];
            }
            OrdenPorBloquesDeColores(H, array_perm);
            res_H = Greedy(H);
            if(res_H < color_H)
                color_H = res_H;

            // rama 3


        }
        if(color_W < color_G && color_W < color_H){
            G = W; // asigo a G el grafo W para correr en la otra iteración        
            DestruccionDelGrafo(G);
            DestruccionDelGrafo(H);
        }
        else if(color_H < color_G && color_H < color_W){
            G = H;
            DestruccionDelGrafo(G);
            DestruccionDelGrafo(W);
        }
        else{
            // me quedo con G 
            DestruccionDelGrafo(H);
            DestruccionDelGrafo(W);
        }
    }
    

}



