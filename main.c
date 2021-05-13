#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <errno.h>
#include <time.h>
#include "RomaVictor.h"

void swap(u32 *a, u32 *b);

typedef struct params_st{
    u32 p[6]; // struct para a,b,c,d,e,f
}params;

int main(int argc, char *argv[])
{ 
    char *endptr;
    long val;
    params param; //parametros
    u32 a,b,c,d,e,f;
    u32 count_greedys = 0;

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
    printf("numero vertices n = %d, numero lados m = %d \n", n, m);
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
        greedy = Greedy(G);
        count_greedys++;
        if(greedy < result){
            printf("%d iteraciones para Greedy con AleatorizarVertices: %d \n",a , greedy);
            result = greedy;
            iorden = f+i;
        }
    }
    // salvo que sea el ultimo 
    if(iorden != f+a){
        AleatorizarVertices(G, iorden);
        result = Greedy(G);
        if(result!=UINT_MAX){
            count_greedys++;
        }
        printf("Greedy con AleatorizarVertices:%d \n", result);
    }


    //6 
    
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
        count_greedys++;
        result = result_greedy; // set nuevo valor para array_perm
        if(result_greedy < r){
            r = result_greedy;
            printf("6- greedy con orden por bloques: %d \n", r);
            
        }
        free(array_perm); // free array allocado en suff_array
        array_perm = NULL;
    }
    

    // 7
    printf("Item-7 \n");
    u32 r_colors = r; // inicializo con el ultimo coloreo de greedy en item 6
    u32 color_G = UINT_MAX;
    u32 color_H = UINT_MAX;
    u32 color_W = UINT_MAX;
    u32 res_G = UINT_MAX;
    u32 res_H = UINT_MAX;
    u32 res_W = UINT_MAX;
    Grafo H;
    Grafo W;
    for (u32 i = 0; i < c; i++) // ciclo externo 
    {  
        color_G = UINT_MAX;
        color_H = UINT_MAX;
        color_W = UINT_MAX;
        // copia el grafo G 
        H = CopiarGrafo(G); 
        W = CopiarGrafo(G);
        // ciclo interno
        for (u32 j = 0; j < d; j++)  // ciclo interno
        {   
            // rama 1  
            AleatorizarVertices(G, f+j);
            res_G = Greedy(G);
            count_greedys++; // contamos la cantidad de greedy hechos
            if(res_G < color_G)
                color_G = res_G; // color_G ,color_H , color_W seran para comparar cual es el menor
                
            
            // rama 2 
            u32 *perm2 = calloc(r_colors, sizeof(u32));
            for (u32 i = r_colors-1; i > 0 ; i--)
            {   //ordena array de mayor a menor
                perm2[r_colors-1-i] = i;
            }
            OrdenPorBloquesDeColores(H, perm2);
            res_H = Greedy(H);
            count_greedys++;
            if(res_H < color_H)
                color_H = res_H;
            
            // rama 3
            printf("debug: r_colors %d \n", r_colors);
            u32 *perm3 = calloc(r_colors, sizeof(u32));
            u32 n_random;
            for (u32 i = r_colors-1; i > 0; i--)
            {
                perm3[r_colors-1-i] = i;
            }
            for (u32 i = 0; i < r_colors; i++)
            {  
               n_random = rand() % e;
               if(n_random == 0){
                   swap(&perm3[i], &perm3[rand() % r_colors]);
               }
            
            }
            OrdenPorBloquesDeColores(W, perm3);
            res_W = Greedy(W);
            count_greedys++;
            if(res_W < color_W)
                color_W = res_W;
            
            free(perm2);
            free(perm3);
        }
        printf(" G=%d | H=%d | W=%d  \n",color_G, color_H, color_W);

        // aqui seleccionamos el grafo con menor color para
        // copiar en la proxima iteración del ciclo externa 
        if(color_W <= color_G && color_W <= color_H){
            r_colors = color_W;
            DestruccionDelGrafo(G);
            DestruccionDelGrafo(H);
            // asignamos el grafo que sobrevive
            G = W; 
        }
        else if(color_H <= color_G && color_H <= color_W){
            // asignamos r para el tamaño de perm
            r_colors = color_H;
            DestruccionDelGrafo(G);
            DestruccionDelGrafo(W);
            // asignamos el grafo que sobrevive
            G = H;
        }
        else{
            // se queda con G 
            // asignamos r para el tamaño de perm
            r_colors = color_G;
            DestruccionDelGrafo(H);
            DestruccionDelGrafo(W);
        }
    }
    t = clock() - t;
    elapsed_time = (double)t / CLOCKS_PER_SEC;
    printf("Time Finish: %f\n \n", elapsed_time);
    printf("numeros de greedy:%d \n", count_greedys);
    printf("\n");
    printf("ultimo obtenidos : G = %d | H = %d | W = %d  \n",color_G, color_H, color_W);
    
}