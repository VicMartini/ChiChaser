#include "BitSet.h"

bitset new_bs(u32 logical_size)
{
    bitset new_bitset = malloc(sizeof(struct bitset_s));
    new_bitset ->bits = calloc((logical_size / 32) + 1, sizeof(u32));
    new_bitset->logical_size = logical_size;
    new_bitset->ocupation = 0;
    return new_bitset;
}

char bs_set(bitset set, u32 k)
{
    if(k<set->logical_size)
    {
        if(!bs_in(set, k))
        {
            set->bits[k/32] |= 1 << (k%32);
            ++set->ocupation;
        }
        return 0;
    }
    else
    {
        return 1;
    }
}

char bs_clear(bitset set, u32 k)
{
    if(k<set->logical_size)
    {
        if(bs_in(set, k))
        {
            set->bits[k/32] &= ~(1 << (k%32));
            --set->ocupation;
        }
        return 0;
    }
    else
    {
        return 1;
    }   
}

char bs_in(bitset set, u32 k)
{
    if(k<set->logical_size)
    {
        return (set->bits[k/32] & (1 << (k%32))) != 0;
    }
    else
    {
        return 1;
    }      
}

void bs_clear_all(bitset set,u32 limit)
{
    memset(set->bits, 0, ((limit / 32) + 1) * sizeof(u32));
}

void bs_destroy(bitset set)
{
    free(set->bits);
    free(set);
}