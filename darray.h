#include <stdint.h>
#include <stdbool.h>

typedef uint32_t u32;
typedef struct vertice_st *elem_type; //Forwad declaration.

#define GROWTH_FACTOR 2

//Array dinamico de punteros a vertices, lo vamos a usar para guardar vencios.
//la justificación por detrás de esta desición de diseño es que queremos tener
//lookup O(1) por indice en el conjunto de los vecinos de un vertice.

struct darray_s
{
    elem_type *elements;
    u32 ocupation;
    u32 size;
};
typedef struct darray_s *darray;

darray new_darray(void);
void expand_darray(darray d);
void darray_push(elem_type e, darray d);
darray darray_copy(darray d);
void delete_darray(darray d);
