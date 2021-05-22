#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <errno.h>
#include <time.h>
#include "rQuickSort.h"
#include "UnleashHell.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

//void swap(u32 *a, u32 *b);

typedef struct params_st{
    u32 p[6]; // struct para a,b,c,d,e,f
}params;

//Algunas funciones que solo usamos en el main y no corresponden a ninguna estructura.

void print_ascii_art(FILE *fptr)
{
    char read_string[128];
 
    while(fgets(read_string,sizeof(read_string),fptr) != NULL)
        printf(ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET,read_string);
}

//Inicializa un array con una permutación aleatoria de [0:n-1]
//se debe liberar memoria.
u32 *shuffle_array(u32 n)
{
    u32 *a = calloc(n, sizeof(u32));
    u32 r;
    for (u32 i = 0; i < n; ++i)
    {
        r = rand() % (i + 1);
        if (r != i)
            a[i] = a[r];
        a[r] = i;
    }

    return a;
}

int main(int argc, char *argv[])
{ 
    char *filename = "logo.txt";
    FILE *fptr = NULL;
 
    if((fptr = fopen(filename,"r")) == NULL)
    {
        fprintf(stderr,"error opening %s\n",filename);
        return 1;
    }
 
    print_ascii_art(fptr);
 
    fclose(fptr);
    printf("\n");
    char *endptr;
    long val;
    params param; //parametros
    u32 a,b,c,d,e,f;
    u32 count_greedies = 0;

    if(argc != 7){
        printf("Bad arguments \n");
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
            fprintf(stderr, "Some argument is out of range,\n");
            fprintf(stderr, "the maximum allowed is : %u\n",UINT_MAX);

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

    u32 total_greedies = a+b+(c*d*3)+1;
    printf("Building graph...\n");
    double elapsed_time;
    clock_t t = clock();
    double total_time;
    Grafo G = ConstruccionDelGrafo();
    u32 n = NumeroDeVertices(G);
    u32 m = NumeroDeLados(G);
    t = clock() - t;
    elapsed_time = (double)t / CLOCKS_PER_SEC;
    printf("Time creating: %f\n", elapsed_time);
    printf(ANSI_COLOR_GREEN "\n ─────────────────────────── Graph specs ────────────────────────────\n\n" ANSI_COLOR_RESET);
    printf(                 "  N = %d | M = %d \n", n, m);
    printf(                 "  Δ = %u | δ = %u\n", Delta(G), G->delta);

    //Comieza a correr el tiempo
    t = clock();

    u32 esBipartito = Bipartito(G);  
    // 3
    printf(ANSI_COLOR_GREEN"\n┌────────────────────────────────────────────────────────────────────┐"ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN"\n│                                                                    │"ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN"\n│                    Is the graph bipartite?                         │"ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN"\n│                                                                    │"ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN"\n└────────────────────────────────────────────────────────────────────┘\n\n"ANSI_COLOR_RESET);   
    if(esBipartito){
        printf("  Yes, this graph's chromatic number is two, halting execution... \n");
        return 0;
    }
    else
    {
        printf("  No, proceeding... \n");        
    }
    
    //5
    printf(ANSI_COLOR_GREEN"\n┌────────────────────────────────────────────────────────────────────┐"ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN"\n│                                                                    │"ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN"\n│                         Random orders                              │"ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN"\n│                                                                    │"ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN"\n└────────────────────────────────────────────────────────────────────┘\n\n"ANSI_COLOR_RESET);        
    
    //Hacer que el orden interno coincida con el orden natural
    for (u32 i = 0; i < NumeroDeVertices(G); i++)
    {
        FijarOrden(i, G, i);
    }
    u32 ordenNat = Greedy(G);
    printf("  Result using natural order: %d \n\n", ordenNat);
    // Aleatorizar vertices
    u32 br_random_orders = UINT_MAX;
    u32 greedy, best_seed;
    greedy = best_seed = 0;
    for (u32 i = 0; i < a; i++)
    {
        AleatorizarVertices(G, f+i);      
        greedy = Greedy(G);
        count_greedies++;
        printf("\r  Latest result : %u [Progress : %u/%u]",greedy,i+1,a);
        fflush(stdout);
        if(greedy < br_random_orders){
            br_random_orders = greedy;
            best_seed = f+i;
        }
    }
    elapsed_time = ((clock() - t) / CLOCKS_PER_SEC) / 60.0;
    printf("  Running time : %f\n", elapsed_time);
    if(count_greedies != 0)
    {
        total_time = (double)(elapsed_time / count_greedies) * total_greedies;
        printf("  Estimated remaining time : %f\n",total_time - elapsed_time);
        printf("  Estimated total time : %f\n",total_time);
    }
    printf("  Greedy runs : %u/%u\n",count_greedies, total_greedies);

    // Salvo que sea el ultimo 
    if(best_seed != f+a){
        printf("  Restoring best order...\n");
        AleatorizarVertices(G, best_seed);
        br_random_orders = Greedy(G);
        if(br_random_orders!=UINT_MAX){
            count_greedies++;
        }
    }


    printf(ANSI_COLOR_GREEN"\n┌────────────────────────────────────────────────────────────────────┐"ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN"\n│                                                                    │"ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN"\n│               Random orders by block of colors                     │"ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN"\n│                                                                    │"ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN"\n└────────────────────────────────────────────────────────────────────┘\n\n"ANSI_COLOR_RESET);  
    u32 new_result = br_random_orders; // La primera iteracion se hace usando el mejor orden obtenido anteriormente.
    u32 *array_perm = NULL;
    for (u32 i = 0; i < b; i++)
    {   
        array_perm = shuffle_array(new_result); // aleatoriza perm
        OrdenPorBloqueDeColores(G, array_perm);
        new_result = Greedy(G);
        count_greedies++;
        printf("\r  Latest result : %u [Progress : %u/%u]",new_result,i+1,b);
        fflush(stdout);           
        free(array_perm); // free array allocado en suff_array
    }
    printf(ANSI_COLOR_CYAN"\n\n  Result after running Greedy %u times, grouping vertices that have \n  the same color and shuffling the order of the groups : %u\n\n"ANSI_COLOR_RESET, b, new_result);
    elapsed_time = ((clock() - t) / CLOCKS_PER_SEC) / 60.0;
    printf("  Running time : %f\n", elapsed_time);
    if(count_greedies != 0)
    {
        total_time = (double)(elapsed_time / count_greedies) * total_greedies ;
        printf("  Estimated remaining time : %f\n",total_time - elapsed_time);
        printf("  Estimated total time : %f\n",total_time);
    }
    printf("  Greedy runs : %u/%u\n",count_greedies, total_greedies);

    // 7
    
    printf(ANSI_COLOR_GREEN"\n┌────────────────────────────────────────────────────────────────────┐"ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN"\n│                                                                    │"ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN"\n│                         Genetic strategy                           │"ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN"\n│                                                                    │"ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN"\n└────────────────────────────────────────────────────────────────────┘\n\n"ANSI_COLOR_RESET);  
    Grafo grafos[3];
    u32 greedy_results[3];
    u32 *perms[3];
    grafos[0] = G;
    grafos[1] = CopiarGrafo(G);
    grafos[2] = CopiarGrafo(G);
    greedy_results[0] = greedy_results[1] = greedy_results[2] = new_result;
    u32 best_branch = 0;
    for (u32 k = 0; k < c; k++)
    {   printf(ANSI_COLOR_GREEN"\n───────── Beginning round number  %u of independent evolution ───────── \n\n"ANSI_COLOR_RESET,k+1);
        for (u32 i = 0; i < d; i++)
        {   
            // Permutacion acendente para la rama 0
            perms[0] = shuffle_array(greedy_results[0]);
            // Permutaciones con orden acendente para las ramas 1 y 2
            for (u32 j = 1; j < 3; j++)
            {
                perms[j] = calloc(greedy_results[j],sizeof(u32));
                for (u32 i = 0; i < greedy_results[j]; i++)
                {
                    perms[j][i] = (greedy_results[j] - 1) - i;
                }
            }
            //Para la permutacion de la rama 2 cada elemento tiene
            //una probabilidad de 1/e de ser intercambiado con otro
            //elemento que sera elegido aleatoriamente
            for (u32 i = 0; i < greedy_results[2]; i++)
            {
                if((rand() % e) == 0)
                    swap(&perms[2][i],&perms[2][rand() % greedy_results[2]]);
            }
            

            for (u32 h = 0; h < 3; h++)
            {
                OrdenPorBloqueDeColores(grafos[h], perms[h]);
                free(perms[h]);
                greedy_results[h] = Greedy(grafos[h]);
                ++count_greedies;
            }

            printf("\r Branch 0 : %u Branch 1 : %u, Branch 2 : %u [Progress : %u/%u]",greedy_results[0],greedy_results[1], greedy_results[2],i+1,d);
            fflush(stdout);            
        }
        for (u32 i = 0; i < 3; i++)
        {
            if(greedy_results[i] < greedy_results[best_branch]) best_branch = i;
        }
        printf(ANSI_COLOR_CYAN"\n\n  Round %u of independent evolution has finished, branch %u has been\n  chosen as the fittest branch\n\n"ANSI_COLOR_RESET,k+1,best_branch);
        for (u32 i = 0; i < 3; i++)
        {
            if(i != best_branch)
            {
                DestruccionDelGrafo(grafos[i]);
                grafos[i] = CopiarGrafo(grafos[best_branch]);
                greedy_results[i] = greedy_results[best_branch];
                printf("  Branch %u is now a clone of the fittest branch\n",i);
            }
        }
        elapsed_time = ((clock() - t) / CLOCKS_PER_SEC) / 60.0;
        printf("  Running time : %f\n", elapsed_time);
        if(count_greedies != 0)
        {
            total_time = (double)(elapsed_time / count_greedies) * total_greedies ;
            printf("  Estimated remaining time : %f\n",total_time - elapsed_time);
            printf("  Estimated total time : %f\n",total_time);
        }
        printf("  Greedy runs : %u/%u\n",count_greedies, total_greedies);         
        printf("  Proceeding to the next cycle...\n");
        
        
        
    }
    for (u32 i = 0; i < 3; i++)
    {
        DestruccionDelGrafo(grafos[i]);
    }
    
    t = clock() - t;
    elapsed_time = (double)t / CLOCKS_PER_SEC;
    printf("Time to finish: %f\n \n", elapsed_time / 60);
    printf("\n");
    printf(ANSI_COLOR_CYAN"\n ─────────── The search for the best coloring has finished! ───────────────"ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN"\n                                                                       "ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN"\n  The best coloring we could find uses "ANSI_COLOR_MAGENTA"%u"ANSI_COLOR_CYAN" colors                  "ANSI_COLOR_RESET,greedy_results[best_branch]);
    printf(ANSI_COLOR_CYAN"\n                                                                       "ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN"\n  Total running time : "ANSI_COLOR_MAGENTA"%f"ANSI_COLOR_CYAN" minutes                                 "ANSI_COLOR_RESET,elapsed_time / 60);
    printf(ANSI_COLOR_CYAN"\n                                                                       "ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN"\n ──────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET);   
    
}


