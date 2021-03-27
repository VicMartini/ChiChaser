
#include <stdint.h>
#include <stdlib.h>
#include "HashTable.h"

hash_table new_ht(int size)
{
    hash_table new_ht = malloc(sizeof(struct hash_table_s));
    new_ht -> size = size;
    new_ht -> ocupation = 0;
    new_ht-> buckets = calloc(size, sizeof(list)); //Quizás deberiamos agregar un loop para inicializar
                                                            //todas las posiciones de la tabla a NULL
};

u32 hash(u32 nombre_real, hash_table ht){
    return nombre_real % ht -> size; //Un hash modular muy sencillo que deberia servirnos por el momento
};                                     //deberiamos ver cómo se comporta y decidir si necesitamos algo más sofisticado.

