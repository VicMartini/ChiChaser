#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "HashTable.h"

u32 hash(u32 nombre_real, hash_table ht)
{
    return nombre_real % ht->size; //Un hash modular muy sencillo que deberia servirnos por el momento
};                                 //deberiamos ver cómo se comporta y decidir si necesitamos algo más sofisticado.

//Esta función destruye la struct de la hashtable
// y nos devuelve un puntero a su iterator.

hash_table new_ht(int size)
{
    hash_table new_ht = malloc(sizeof(struct hash_table_s));
    new_ht->size = size;
    new_ht->ocupation = 0;
    new_ht->buckets = calloc(size, sizeof(list));
    for (u32 i = 0; i < size; ++i)
    {
        new_ht->buckets[i] = new_list();
    }
    return new_ht;
};

void destroy_ht(hash_table ht)
{
    for (u32 i = 0; i < ht->size; ++i)
        destroy_list(ht->buckets[i]);
    free(ht->buckets);
    free(ht);
}

bool in_ht(u32 key, hash_table ht)
{
    return in_list(key, ht->buckets[hash(key, ht)]);
}

void ht_put(u32 key, vertice *addr, hash_table ht) // Si el vertice no está lo agregamos y devolvemos un puntero hacia él. Si el vertice está funciona como get.
{
    //Primero hasheamos el nombre real para ver a cual bucket hay que agregar el vertice
    u32 hsh = hash(key, ht);
    ht->buckets[hsh] = addl(key, addr, ht->buckets[hsh]); //Ahora el nuevo vertice es el primero en el bucket
                                                          // que corresponde a su orden de cargado.
                                                          //  printf("-> %d\n");
    ht->ocupation += 1;
}

vertice *ht_get(u32 key, hash_table ht)
{
    u32 hsh = hash(key, ht);
    /*Gracias al nuevo metodo search de la lista solo tenemos que hacer una llamada acá*/
    return search(key, ht->buckets[hsh]);
};