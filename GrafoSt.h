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
typedef struct GrafoSt *Grafo;

u32 delta(Grafo g);
u32 Delta(Grafo g);
u32 print_graph(Grafo g, u32 lines);
Grafo ConstruccionDelGrafo(void);
u32 FijarPesoLadoConVecino(u32 j, u32 i, u32 p, Grafo G);
Grafo CopiarGrafo(Grafo G);
void DestruccionDelGrafo(Grafo G);
char FijarOrden(u32 i, Grafo G, u32 N);
char FijarColor(u32 x, u32 i, Grafo G);
u32 PesoLadoConVecino(u32 j, u32 i, Grafo G);
u32 NombreVecino(u32 j, u32 i, Grafo G);
u32 ColorVecino(u32 j, u32 i, Grafo G);
u32 Grado(u32 i, Grafo G);
u32 Color(u32 i, Grafo G);
u32 Nombre(u32 i, Grafo G);
u32 NumeroDeLados(Grafo G);
u32 NumeroDeVertices(Grafo G);
