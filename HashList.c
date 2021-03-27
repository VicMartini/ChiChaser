
#include <stdint.h>
#include <stdlib.h>
#include "HashList.h"

hash_list new_hl(int size)
{
    hash_list new_hash_list = malloc(sizeof(struct hash_list_s));
    new_hash_list -> size = size;
    new_hash_list -> ocupation = 0;
    new_hash_list -> buckets = calloc(size, sizeof(list)); //Quizás deberiamos agregar un loop para inicializar
                                                            //todas las posiciones de la tabla a NULL
};

u32 hash(u32 nombre_real, hash_list hl){
    return nombre_real % hl -> size; //Un hash modular muy sencillo que deberia servirnos por el momento
};                                     //deberiamos ver cómo se comporta y decidir si necesitamos algo más sofisticado.
