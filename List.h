#include <stdint.h>
#include <stdbool.h>
typedef uint32_t u32;

/*
Programé esta implementación de lista cuando estaba cursando Algoritmos II. Vamos a adaptarla para nuestras necesidades actuales.

Esta era la struct del nodo original:

struct node {
  list next;
  int data;
};

La principal diferencia es que ahora data va a ser un puntero a un vertice.
Hasta donde puedo ver las unicas moddificaciones que son necesarias son:
  - addr necesita tomar un puntero a vertice en vez de un entero
  - head e index van a devolver punteros a vertices.

!!!!****Necesitamos tests para esto****!!!!
*/
/*Voy a poner esta  vertice acá porque hay mucho acoplamiento entre vertice y lista 
(se referencian mutuamente),y no vamos a tener listas de cosas que no sean vertices.
No vamos a necesitar usar forward declaration y la busqueda va a poder ser más eficiente
teniendo la definición completa de vertice*/

/*Los vertices contienen la información que necesitamos en O(1) + una linked list  que tiene punteros a sus vecinos 
Todo es O(1) salvo buscar un vecino que O(n) en el peor de los casos*/
typedef struct vertice_st
{
  u32 nombre;
  u32 color;
  u32 grado;
  u32 *pesos;
  struct node *vecinos;
} vertice;

struct node
{ //Vamos a usar la lista para guardar los vecinos de un vertice y también para  manejar colisiones en la hashtable.
  vertice *data;
  struct node *next;
};
typedef struct node *list;

list addl(u32 key, list l);
//{Creates a new vertex at the begining of the list given its name}
list addl_ptr(vertice *v, list l);
//{Adds a vertex to the begining of the list}
bool in_list(u32 key, list l);
//{Returns true if and only if the vertex is in the list}
vertice *new_vertex(u32 nombre);
//{Creates a new vertex}
list new_list(void);
/*{Returns a ponter to a new list}*/
bool is_empty(list l);
/*{It returns wheter the list is enpty or not}*/

/*{The list must not be empty}*/
vertice *head(list l);
/*{It returns the list's first element}*/

/*{The list must not be empty}*/
list tail(list l);
/*{Deletes the first element of the given list}*/

list addr(vertice *e, list l);
/*{Adds an element at the end of the list}*/

/*Nuevo operador sobre la lista, nos va a permitir
recorrer el array de lados agregando los vertices
que ocurren en cada lado sin crear duplicados.
Si no tendriamos que checkear si el vertice está
antes de agregarlo con search y después agregarlo
con addr. Esto seria un poco menos eficiente*/
list addr_idemp_ptr(vertice *e, list l);
/*{Adds a vertex to the end of the list
if it is not already there, given a pointer to it}*/
list addr_idemp(u32 key, list l);
/*{It creates a vertex and it adds it to the end of the list
if the vertex with that key is not in the list}*/
vertice *search(u32 key, list l);
/*{Returns a pointer to the vertex with the given key
NOTE: It returns a NULL pointer if the vertex isn't there}*/
//Estos comentarios capaz que es bueno pasarlos todos a español

unsigned int length(list l);
/*{Returns the length of the list}*/

void concat(list l1, list l2);
/*{Adds the elements of l2, in order, to l1 }*/

/*{i < length(l)}*/
vertice *index_ith(unsigned int i, list l);
/*{Returns the list's ith element}*/

/*{i < length(l)}*/
void take(unsigned int i, list l);
/*{Deletes all the elements of l1
 whose indexes are greather or equal than i}*/

/*{i <= length(l)}*/
list drop(unsigned int i, list l);
/*{Deletes all the elements of l1
 whose indexes are less than i and 
 returns the new head}*/

/*{The list must not be empty}*/
list copy_list(list l);
/*{Deletes all the elements of l1
 whose indexes are less than i}*/

/*{The list must not be empty}*/
u32 destroy_list(list l);
/*{ Frees the memory used by l }*/
