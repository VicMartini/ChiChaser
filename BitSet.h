#include <stdint.h>
#include <stdlib.h>

typedef uint32_t u32;

struct bitset_s
{
    u32 *bits;
    u32 logical_size;
    u32 ocupation;
};
typedef struct bitset_s *bitset;

bitset new_bs(u32 logical_size);
char bs_set(bitset set, u32 k);