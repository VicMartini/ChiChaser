
#include <stdint.h>
#include <stdlib.h>
#include "HashTable.h"


u32 hash(u32 nombre_real, hash_table ht){
    return nombre_real % ht -> size; //Un hash modular muy sencillo que deberia servirnos por el momento
};                                     //deberiamos ver cómo se comporta y decidir si necesitamos algo más sofisticado.

hash_table new_ht(int size)
{
    hash_table new_ht = malloc(sizeof(struct hash_table_s));
    new_ht -> size = size;
    new_ht -> ocupation = 0;
    new_ht-> buckets = calloc(size, sizeof(list)); 
    for (u32 i = 0; i < size; ++i)
    {
        new_ht -> buckets[i] = new_list();
    }       
    return new_ht;                                                 
};

void add_ht_entry(u32 key, hash_table ht)
{
    //Primero hasheamos el nombre real para ver a cual bucket hay que agregar el vertice
    u32 hsh = hash(key);
    // Y con esto ya podemos agregar el vertice al bucket correspondiente usando la interfaz de list
    // gracias a addr_idemp podemos agregar sin crear duplicados, osea esta función también es idempotente
    ht -> buckets[hsh] = addr_idemp(key, ht -> buckets[hsh]);
    // Me parece que quedó mucho más simple que si hubieramos usado open addressing :)
};

vertice *lookup_ht_entry(u32 key, hash_table ht)
{
    vertice *v;
    //Muy parecido a la anterior, primero hasheamos la key
    u32 hsh = hash(key, ht);
    /*Gracias al nuevo metodo search de la lista solo tenemos que hacer una llamada acá*/
    return search(key, ht -> buckets[hsh]);
};