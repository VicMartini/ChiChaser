
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
    new_ht-> buckets = calloc(size, sizeof(list)); //Quizás deberiamos agregar un loop para inicializar
                                                            //todas las posiciones de la tabla a NULL
};

void add_ht_entry(vertice *entry, hash_table ht)
{
    //Primero hasheamos el nombre real para ver a cual bucket hay que agregar el vertice
    u32 hsh = hash(entry -> nombre, ht);
    // Y con esto ya podemos agregar el vertice al bucket correspondiente usando la interfaz de list
    ht -> buckets[hsh] = addr(entry, ht -> buckets[hsh]);
    // Me parece que quedó mucho más simple que si hubieramos usado open addressing :)
};

vertice *lookup_ht_entry(u32 key, hash_table ht)
{
    vertice *v;
    //Muy parecido a la anterior, primero hasheamos la key
    u32 hsh = hash(key, ht);
    /*Pero no tenemos un método para buscar en la lista, asi 
    que vamos a copiar la lista y hacer tail de la copia
    hasta llegar al elemento que buscamos. Esto no es muy 
    eficiente, hay que probarlo. De ocurrir pocas colisiones
    va a andar bien*/
    list c = copy_list(ht -> buckets[hsh]);
    while(c -> data -> nombre != key && c != NULL)
    {
        c = tail(c);
    }
    v = (c == NULL) ? NULL : c -> data; // Si esta función devuelve null significa que
                                        //el vertice no estaba en la lista
    destroy_list(c); // Liberamos la memoria de la copia.
    return v;
} // Tengo mis dudas sobre esta función, en particular no me gusta esto de copiar la lista
  // tengamos en cuenta que puede requerir refactorización.