#include <stdint.h>

typedef uint32_t u32;
typedef struct Lado Lado_st;

/*El grafo contiene los campos que necesitamos en  O(1) y un arreglo de vertices.
Si usamos un array de punteros a Vertices eliminamos la necesidad de usar un array para el orden
Como los vertices estan en un array, acceder 
a un vertice teniendo su número de orden en orden inicial también es O(1). */

/*
struct GrafoSt
{
  u32 num_vertices;
  u32 num_lados;
  u32 delta;
  Vertice **Vertices; /*Esto va a ser un array de punteros a vertices, como la cantidad de vertices está al principio del archivo dimacs, ya sabemos
  desde el comienzo cuanto espacio reservar para el array
};

*/
struct Lado
{
  u32 v;
  u32 w;
};

/*Los vertices contienen la información que necesitamos en O(1) + una linked list  que tiene punteros a sus vecinos 
Todo es O(1) salvo buscar un vecino que O(n) en el peor de los casos*
struct Vertice
{
  u32 nombre;
  u32 color;
  u32 grado;
  ListaVertices *vecinos; // Esto necesita ser una Linked List porque no sabemos el grado del vertice hasta terminar de construir el grafo.
};

// Struct para la linked list.
struct ListaVertices
{
  Vertice *Vertice;
  ListaVertices *prox;
};
*/