#include <stdint.h>
#include "dimacs.h"
#include "HashTable.h"

typedef uint32_t u32;

/*El grafo contiene los campos que necesitamos en  O(1) y un array de vertices.
También guardamos el orden natural y el orden interno usando dos arrays, cada array
de orden contiene los indices de los elementos del array de vertices de acuerdo 
con el orden correspondiente*/

struct GrafoSt
{
  u32 num_vertices;
  u32 num_lados;
  u32 Delta;
  u32 delta;
  u32 *orden_natural;
  u32 *orden;
  vertice *vertices; //Array de vertices
};
typedef struct GrafoSt GrafoSt;

void GenerarOrdenNatural(GrafoSt *G);

u32 print_graph(GrafoSt *g, u32 lines);
u32 delta(GrafoSt *g);
Lado_st parse_edge(void);
void insert_edge(u32 v_key, u32 w_key, GrafoSt *g, hash_table ht);
