#include <stdint.h>

typedef uint32_t u32;

/*El grafo contiene los campos que necesitamos en  O(1) y un arreglo de nodos.
Si usamos un array de punteros a nodos eliminamos la necesidad de usar un array para el orden
Como los nodos estan en un array, acceder 
a un nodo teniendo su número de orden en orden inicial también es O(1). */

struct GrafoSt{
  u32 num_vertices;
  u32 num_lados;
  u32 delta;
  Nodo** nodos; /*Esto va a ser un array de punteros nodos, como la cantidad de nodos está al principio del archivo dimacs, ya sabemos
  desde el comienzo cuanto espacio reservar para el array*/


};
/*Los nodos contienen la información que necesitamos en O(1) + una linked list  que tiene punteros a sus vecinos 
Todo es O(1) salvo buscar un vecino que O(n) en el peor de los casos*/
struct Nodo{
    u32 nombre;
    u32 color;
    u32 grado;
    ListaNodos* vecinos; // No puede ser una Linked List, porque  necesitamos acceder a los vecinos en O(1). Pero al principio no sabemos el grado del vertice. Cómo podemos hacer? Quizas un dynamic array, hay que ver cómo se implementa.
};

// Struct para la linked list.
struct ListaNodos{ 
    Nodo* nodo;
    ListaNodos* prox;
};
