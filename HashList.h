#include "GrafoSt.h"
#include "List.h"
#include "VerticeSt.h"
typedef uint32_t u32;
/* Esta estructura de datos es una implementación de una lista de adyacencia usando hash tables.
Usar la hashtable nos permite hacer frente al problema de que los nodos del grafos no van a ser
necesariamente enteros contiguos, lo cual hace inviable usar la implementación tradicional de una
lista de adyacencia.*/

#define ENTRY_TYPE vertice;

//---------------Estructuras---------------------------
struct hash_list_s
{
    int size;
    int ocupation;
    list *buckets; //Cada bucket es una lista de los vertices con el mismo hash.
};

typedef struct hash_list_s *hash_list;

//---------------Métodos---------------------------

hash_list new_hl(int size);              //Crea una hashlist vacia dado su tamaño.
void add_hl_entry(vertice *entry);  // Añade unn vertice a la hashtable
vertice* lookup_hl_entry(u32 key);      //Busca un vertice en la hashtable
u32 hash(u32 nombre_real, hash_list hl); // Devuelve el hash para un vertice y una hashlist en particular.
