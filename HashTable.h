#include "List.h"
typedef uint32_t u32;
/* Usar la hashtable nos permite hacer frente al problema de que los nodos del grafos no van a ser
necesariamente enteros contiguos, lo cual hace inviable usar la implementación tradicional de una
lista de adyacencia.*/

//---------------Estructuras---------------------------
struct hash_table_s
{
    u32 size;
    u32 ocupation;
    list *buckets;
};

typedef struct hash_table_s *hash_table;

//---------------Métodos---------------------------

hash_table new_ht(u32 size);
void ht_put(u32 key, u32 val, hash_table ht);
u32 ht_get(u32 key, hash_table ht);
u32 hash(u32 nombre_real, hash_table ht);
void destroy_ht(hash_table ht);
bool in_ht(u32 key, hash_table ht);
void ht_delete(u32 key, hash_table ht);
