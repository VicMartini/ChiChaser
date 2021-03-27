#include <stdint.h>
#include "GrafoSt.h"
typedef uint32_t u32;
/* Esta estructura de datos es una implementación de una lista de adyacencia usando hash tables*/

typedef struct hash_list_s{
    int size;
    entry **entries;
} hash_list;

typedef struct entry_s{
    u32 *key;
    list *vertice; //Lista enlazada de vertices que tienen el mismo hash
} entry;

typedef struct list_s{ //Vamos a usar la lista para guardar los vecinos de un vertice y también para  manejar colisiones en la hashtable.
    vertice* vertice;
    list* next;
} list;

/*Los vertices contienen la información que necesitamos en O(1) + una linked list  que tiene punteros a sus vecinos 
Todo es O(1) salvo buscar un vecino que O(n) en el peor de los casos*/
typedef struct vertice_st
{
  u32 nombre;
  u32 color;
  u32 grado;
  list *vecinos; // Esto necesita ser una Linked List porque no sabemos el grado del vertice hasta terminar de construir el grafo.
} vertice;
