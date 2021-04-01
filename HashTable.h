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
    vertice *iterator; //Un array de  vertices que podemos usar para iterar eficientemente sobre todos los elementos de la hashtable
                       //inspirado en la LinkedHashMap de Java.
    list *buckets;     //Cada bucket es una lista de los vertices con el mismo hash.
    //Idea: Después de terminada la construccion del grafo podriamos liberar la hashtable y quedarnos solo con el iterator.
};

typedef struct hash_table_s *hash_table;

//---------------Métodos---------------------------

hash_table new_ht(int size);                 //Crea una hashtist vacia dado su tamaño.
vertice *ht_put(u32 key, hash_table ht);     // Añade un vertice a la hashtable, si el vertice no esta ya en la tabla.
vertice *ht_get(u32 key, hash_table ht);     //Busca un vertice en la hashtable
u32 hash(u32 nombre_real, hash_table ht);    // Devuelve el hash para un vertice y una hashtist en particular.
vertice *ht_extract_iterator(hash_table ht); //Destruye la hashtable y devuelve una referencia a su iterator.
void insert_edge(u32 v_key, u32 w_key, hash_table ht);
