#include <stdint.h>
#include "List.h"
#include "GrafoSt.h"

typedef uint32_t u32;

/*Los vertices contienen la información que necesitamos en O(1) + una linked list  que tiene punteros a sus vecinos 
Todo es O(1) salvo buscar un vecino que O(n) en el peor de los casos*/
typedef struct vertice_st
{
    u32 nombre;
    u32 color;
    u32 grado;
    list *vecinos; // Esto necesita ser una Linked List porque no sabemos el grado del vertice hasta terminar de construir el grafo.
} vertice;
