
#include <stdint.h>
#include <stdlib.h>
#include "HashList.h"

hash_list new_hash_list(int size)
{
    hash_list new_hash_list = malloc(sizeof(struct hash_list_s));
    new_hash_list -> size = size;
    new_hash_list -> ocupation = 0;
    new_hash_list -> entries = calloc(size, sizeof())
};