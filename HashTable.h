#include "List.h"
typedef uint32_t u32;
/* Esta estructura de datos es una implementación de una lista de adyacencia usando hash tables.
Usar la hashtable nos permite hacer frente al problema de que los nodos del grafos no van a ser
necesariamente enteros contiguos, lo cual hace inviable usar la implementación tradicional de una
lista de adyacencia.*/


//---------------Estructuras---------------------------
struct hash_table_s
{
    int size;
    int ocupation;
    vertice** order; //Un array de punteros a vertices que podemos usar para iterar eficientemente sobre todos los elementos de la hashtable
                    //inspirado en la LinkedHashMap de Java.
    list *buckets; //Cada bucket es una lista de los vertices con el mismo hash.
};

typedef struct hash_table_s *hash_table;

//---------------Métodos---------------------------

hash_table new_ht(int size);              //Crea una hashtist vacia dado su tamaño.
vertice* ht_put(u32 key, hash_table ht);  // Añade un vertice a la hashtable, si el vertice no esta ya en la tabla.
vertice* ht_get(u32 key, hash_table ht);      //Busca un vertice en la hashtable
u32 hash(u32 nombre_real, hash_table ht); // Devuelve el hash para un vertice y una hashtist en particular.
