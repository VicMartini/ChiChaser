#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "darray.h"
typedef uint32_t u32;

darray new_darray(void)
{
    darray new_darray = malloc(sizeof(struct darray_s));
    //Vamos a usar un approach inspirado en los vectores
    // de C++
    new_darray->ocupation = new_darray->size = 0;
    new_darray->elements = calloc(0, sizeof(elem_type));
    return new_darray;
};

void expand_darray(darray d)
{
    u32 new_size = GROWTH_FACTOR * d->size;
    d->size = (1 > new_size) ? 1 : new_size;
    d->elements = realloc(d->elements, d->size * sizeof(elem_type));
}
void darray_push(elem_type e, darray d)
{
    if (d->size == d->ocupation)
        expand_darray(d);
    d->elements[++d->ocupation] = e;
}