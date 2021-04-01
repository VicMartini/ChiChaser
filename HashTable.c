
#include <stdint.h>
#include <stdlib.h>
#include "HashTable.h"

u32 hash(u32 nombre_real, hash_table ht)
{
    return nombre_real % ht->size; //Un hash modular muy sencillo que deberia servirnos por el momento
};                                 //deberiamos ver cómo se comporta y decidir si necesitamos algo más sofisticado.

void insert_edge(u32 v_key, u32 w_key, hash_table ht)
{
    vertice *v = ht_put(v_key, ht);
    vertice *w = ht_put(w_key, ht); //Notese que put es idempotente (No genera duplicados)
    /*
    Me parece que chequear por duplicados antes de añadir vecinos es inviable
    aumenta mucho el tiempo de ejecución y me parece que en las specs dice
    que no va a haber duplicados
    v->vecinos = (in_list(w_key, v->vecinos)) ? v->vecinos : addl_ptr(w, v->vecinos);
    w->vecinos = (in_list(v_key, w->vecinos)) ? w->vecinos : addl_ptr(v, w->vecinos);
    */
    v->vecinos = addl_ptr(w, v->vecinos);
    w->vecinos = addl_ptr(v, w->vecinos);
    //Puede que el chequeo de si el vecino está en la lista sea inecesario. Hay que preguntarle
    // al profe si podemos asumir que no hay lados duplicados en el dimacs.
}

//Esta función destruye la struct de la hashtable
// y nos devuelve un puntero a su iterator.
vertice *ht_extract_iterator(hash_table ht)
{
    vertice *iterator = ht->iterator;
    for (u32 i = 0; i < ht->size; ++i)
    {
        destroy_list(ht->buckets[i]);
    }
    free(ht->buckets);
    free(ht);
    return iterator;
}

hash_table new_ht(int size)
{
    hash_table new_ht = malloc(sizeof(struct hash_table_s));
    new_ht->size = size;
    new_ht->ocupation = 0;
    new_ht->iterator = calloc(size, sizeof(vertice));
    new_ht->buckets = calloc(size, sizeof(list));
    for (u32 i = 0; i < size; ++i)
    {
        new_ht->buckets[i] = new_list();
    }
    return new_ht;
};

vertice *place_in_iterator(u32 key, u32 k, hash_table ht)
{
    ht->iterator[k].nombre = key;
    ht->iterator[k].vecinos = new_list();
    return ht->iterator + k;
}

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
        vertice *nv_address = place_in_iterator(key, ht->ocupation, ht);
        ht->buckets[hsh] = addl_ptr(nv_address, ht->buckets[hsh]); //Ahora el nuevo vertice es el primero en el bucket
        ht->ocupation += 1;
        return head(ht->buckets[hsh]); // que corresponde a su orden de cargado.
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