#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "HashTable.h"

u32 hash(u32 nombre_real, hash_table ht)
{
    return nombre_real % ht->size;
};

hash_table new_ht(u32 size)
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

void ht_put(u32 key, u32 val, hash_table ht)
{
    u32 hsh = hash(key, ht);
    ht->buckets[hsh] = addl(key, val, ht->buckets[hsh]);
    ht->ocupation += 1;
}

void ht_delete_bucket(u32 key, hash_table ht)
{
    destroy_list(ht->buckets[key]);
    ht->buckets[key] = new_list();
}

u32 ht_get(u32 key, hash_table ht)
{
    u32 hsh = hash(key, ht);
    return search(key, ht->buckets[hsh]);
};