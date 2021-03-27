#include <stdint.h>
#include <stdbool.h>
typedef struct vertice vertice; //Forward declaration, si no hago esto se crea una dependencia circular con VerticeSt.
#define ELEMENT_TYPE vertice;
/*
Programé esta implementación de lista cuando estaba cursando Algoritmos II. Vamos a adaptarla para nuestras necesidades actuales.

Esta era la struct del nodo original:

struct node {
  list next;
  int data;
};

La principal diferencia es que ahora data va a ser un puntero a un vertice.
*/


struct node
{ //Vamos a usar la lista para guardar los vecinos de un vertice y también para  manejar colisiones en la hashtable.
    vertice *data;
    node *next;
};
typedef node* list;


list new_list(void);
/*{Returns a ponter to a new list}*/
bool is_empty(list l);
/*{It returns wheter the list is enpty or not}*/

/*{The list must not be empty}*/
int head(list l);
/*{It returns the list's first element}*/


/*{The list must not be empty}*/
list tail(list l);
/*{Deletes the first element of the given list}*/

list addr(int e, list l);
/*{Adds an element at the end of the list}*/

unsigned int length(list l);
/*{Returns the length of the list}*/

void concat(list l1, list l2);
/*{Adds the elements of l2, in order, to l1 }*/

/*{i < length(l)}*/
int index(unsigned int i ,list l);
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
 void destroy_list(list l);
 /*{ Frees the memory used by l }*/

#endif