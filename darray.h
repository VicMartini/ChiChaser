#include <stdint.h>
#include <stdbool.h>

typedef uint32_t u32;

#define GROWTH_FACTOR 2

//Array dinamico, lo vamos a usar para guardar vecinos.
//la justificación por detrás de esta decisión de diseño es que queremos tener
//lookup O(1) por indice en el conjunto de los vecinos de un vertice.

struct darray_s
{
    u32 *elements;
    u32 ocupation;
    u32 size;
};
typedef struct darray_s *darray;

darray new_darray(void);
void expand_darray(darray d);
void darray_push(u32 e, darray d);
darray darray_copy(darray d);
u32 darray_get(u32 index, darray d);
void delete_darray(darray d);
