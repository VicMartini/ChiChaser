
#include <stdint.h>
#include <stdlib.h>
#include "HashTable.h"

u32 hash(u32 nombre_real, hash_table ht)
{
    return nombre_real % ht->size; //Un hash modular muy sencillo que deberia servirnos por el momento
};                                 //deberiamos ver cómo se comporta y decidir si necesitamos algo más sofisticado.

hash_table new_ht(int size)
{
    hash_table new_ht = malloc(sizeof(struct hash_table_s));
    new_ht->size = size;
    new_ht->ocupation = 0;
    new_ht->order = calloc(size, sizeof(vertice *));
    new_ht->buckets = calloc(size, sizeof(list));
    for (u32 i = 0; i < size; ++i)
    {
        new_ht->buckets[i] = new_list();
    }
    return new_ht;
};

bool in_ht(u32 key, hash_table ht)
{
    return in_list(key, ht->buckets[hash(key, ht)]);
}

vertice *ht_put(u32 key, hash_table ht) // Si el vertice no está lo agregamos y devolvemos un puntero hacia él. Si el vertice está funciona como get.
{
    //Primero hasheamos el nombre real para ver a cual bucket hay que agregar el vertice
    u32 hsh = hash(key, ht);
    // Verificamos si el vertice está en la hashtable
    vertice *v = search(key, ht->buckets[hsh]); //Esto es NULL si el vertice no está
    if (!v)                                     //No está el vertice vamos a agregarlo a la tabla y al array de orden.
    {
        ht->buckets[hsh] = addl(key, ht->buckets[hsh]);    //Ahora el nuevo vertice es el primero en el bucket
        ht->order[ht->ocupation] = head(ht->buckets[hsh]); // Agregamos el puntero al nuevo vertice a la lista en la posición
        ht->ocupation += 1;
        return head(ht->buckets[hsh]);                    // que corresponde a su orden de cargado.
    }
    else // El vertice ya estaba, devolvemos el puntero hacia él.
    {
        return v;
    }
    // Me parece que quedó mucho más simple que si hubieramos usado open addressing :)
};

vertice *ht_get(u32 key, hash_table ht)
{
    u32 hsh = hash(key, ht);
    /*Gracias al nuevo metodo search de la lista solo tenemos que hacer una llamada acá*/
    return search(key, ht->buckets[hsh]);
};