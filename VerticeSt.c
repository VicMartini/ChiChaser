#include "VerticeSt.h"

vertice Vertice(u32 nombre)
{
    vertice new_vertex = {nombre, 0, 0xFFFFFFFF, 0, NULL, new_darray()};
    return new_vertex;
}