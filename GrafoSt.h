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
  hash_table vertices; 
};
typedef struct GrafoSt *Grafo;

u32 delta(Grafo g);
u32 Delta(Grafo g);
void insert_edge(u32 v_key, u32 w_key, Grafo g);
void print_graph(Grafo g);
Grafo ConstruccionDelGrafo(void);
u32 FijarPesoLadoConVecino(u32 j,u32 i,u32 p,Grafo G);




