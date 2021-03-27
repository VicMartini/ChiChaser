#include <stdint.h>

typedef uint32_t u32;
typedef struct Lado Lado_st;

/*El grafo contiene los campos que necesitamos en  O(1) y un arreglo de vertices.
Si usamos un array de punteros a Vertices eliminamos la necesidad de usar un array para el orden
Como los vertices estan en un array, acceder 
a un vertice teniendo su número de orden en orden inicial también es O(1). */


typedef struct GrafoSt
{
  u32 num_vertices;
  u32 num_lados;
  u32 delta;
  vertice **vertices; /*Esto va a ser un array de punteros a vertices, como la cantidad de vertices está al principio del archivo dimacs, ya sabemos
  desde el comienzo cuanto espacio reservar para el array*/
} grafo;


struct Lado
{
  u32 v;
  u32 w;
};



