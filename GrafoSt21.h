#include <stdint.h>
#include "HashTable.h"
#include "dimacs.h"
typedef uint32_t u32;

/*El grafo contiene los campos que necesitamos en  O(1) y una hashtable de vertices.
Si usamos un array de punteros a Vertices eliminamos la necesidad de usar un array para el orden
Como los vertices estan en un array, acceder 
a un vertice teniendo su número de orden en orden inicial también es O(1). */

struct GrafoSt
{
  u32 num_vertices;
  u32 num_lados;
  u32 Delta;
  u32 delta;
  u32 *orden;
  vertice *vertices; //Array de vertices
};
typedef struct GrafoSt GrafoSt;

u32 print_graph(GrafoSt *g, u32 lines);
u32 delta(GrafoSt *g);
