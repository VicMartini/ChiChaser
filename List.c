#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "List.h"
typedef uint32_t u32;

/*
list addl(u32 key, list l)
{
  vertice *nv = new_vertex(key);
  return addl_ptr(nv, l);
}
*/

list addl(u32 key, vertice *v, list l)
{
  list new_head = malloc(sizeof(struct node));
  new_head->data = v;
  new_head->key = key;
  new_head->next = l;
  return new_head;
}

list new_list(void)
{
  list new_list = NULL;
  return new_list;
}

bool is_empty(list l)
{
  return l == NULL;
}

vertice *head(list l)
{
  assert(!is_empty(l));
  return l->data;
}

list tail(list l)
{
  assert(!is_empty(l));
  list new_head;
  list old_head = l;
  new_head = old_head->next;
  free(old_head);
  return new_head;
}

list addr(vertice *e, list l)
{
  list traverser = l;
  list prev_node = NULL;
  list new_node = malloc(sizeof(struct node));

  while (traverser)
  {
    prev_node = traverser;
    traverser = traverser->next;
  }
  if (prev_node)                //Si hay un prev_node la lista no es vacia y prev_node apunta al ultimo
  {                             //elemento de la lista
    prev_node->next = new_node; //Agregamos el vertice al final de la lista
    return l;                   // En este caso el head sigue siendo el mismo
  }
  else //La lista es vacia
  {
    return new_node; //Devolvemos el puntero al nuevo nodo
  }
}

list addr_idemp_ptr(vertice *e, list l)
{
  list traverser = l;
  list prev_node = NULL;
  while (traverser && traverser->data->nombre != e->nombre)
  {
    prev_node = traverser;
    traverser = traverser->next;
  }
  // En este punto, si el vertice existe ya en la lista estamos parados en él
  // si no existe estamos parados al final de la lista
  if (traverser) //La lista no es vacia y no llegamos al final
  {              // eso significa que el vertice ya está en la lista.
    if (traverser->data != e)
      free(e); //Si nos pasaron un puntero a un nodo que ya está y no es el puntero que
               //está en la lista liberamos la memoria usada por ese nodo duplicado
    return l;  //No hacemos nada
  }
  else // La lista original es vacia o llegamos al final sin encontrar el vertice
  {
    list new_node = malloc(sizeof(struct node)); //Acá ya sabemos que necesitamos un nodo más
    new_node->data = e;
    if (prev_node)                //Si hay un prev_node la lista no es vacia y prev_node apunta al ultimo
    {                             //elemento de la lista
      prev_node->next = new_node; //Agregamos el vertice al final de la lista
      return l;                   // En este caso el head sigue siendo el mismo
    }
    else //La lista es vacia
    {
      return new_node; //Devolvemos el puntero al nuevo nodo
    }
  }
}

list addr_idemp(u32 key, list l)
{
  vertice *new_vertex = malloc(sizeof(vertice));
  new_vertex->nombre = key;             // Estamos mezclando español e inglés demasiado, eso no está bueno
  return addr_idemp_ptr(new_vertex, l); //La addr_demp_ptr va a destruir este nuevo vertice si
                                        // ya existe uno igual en la lista.
}
//Ahora con acceso a la definición completa de vertice podemos buscar un poco más eficientemente

vertice *search(u32 key, list l)
{

  list traverser = l;

  while (traverser && traverser->key != key)
    traverser = traverser->next;

  return traverser ? traverser->data : NULL; //Notese que si el vertice no está devolvemos NULL (incluido el caso de la lista vacia)
}

bool in_list(u32 key, list l)
{
  list traverser = l;
  while (traverser && traverser->key != key)
  {
    traverser = traverser->next;
  }
  // En este punto, si el vertice existe ya en la lista estamos parados en él
  // si no existe estamos parados al final de la lista
  // Si salimos del loop porque traverser == NULL significa que no encontramos el vertice
  return !(traverser == NULL);
}
unsigned int length(list l)
{
  int count = 0;
  list traverser = l;
  while (!is_empty(traverser))
  {
    traverser = traverser->next;
    ++count;
  }

  return count;
}

void concat(list l1, list l2)
{
  list traverser = l1;
  while (traverser->next != NULL)
  {
    traverser = traverser->next;
  }
  traverser->next = l2;
}

vertice *index_ith(unsigned int i, list l)
{
  assert(length(l) > i);
  list traverser = l;
  for (unsigned int j = 0; j < i; ++j)
  {
    traverser = traverser->next;
  }
  return traverser->data;
}

void take(unsigned int i, list l)
{
  assert(length(l) > i);
  list traverser = l;
  for (unsigned int j = 0; j < i; ++i)
  {
    traverser = traverser->next;
  }
  list prev_node;
  while (!is_empty(traverser->next))
  {
    prev_node = traverser;
    traverser = traverser->next;
    free(prev_node);
  }
  free(traverser);
}

list drop(unsigned int i, list l)
{
  assert(length(l) >= i);
  list traverser = l;
  list prev_node;
  for (unsigned int j = 0; j < i; j++)
  {
    prev_node = traverser;
    traverser = traverser->next;
    free(prev_node);
  }
  return traverser;
}
/*
list copy_list(list l)
{
  assert(!is_empty(l));
  list traverser = l;
  list new_node = malloc(sizeof(struct node));
  list new_list = new_node;
  new_node->data = traverser->data;
  traverser = traverser->next;
  while (!is_empty(traverser->next))
  {
    new_node->next = malloc(sizeof(struct node));
    new_node = new_node->next;
    new_node->data = traverser->data;
    traverser = traverser->next;
  }
  return new_list;
}
*/
list copy_list(list l)
{
  if (is_empty(l))
    return NULL;
  list clone = malloc(sizeof(struct node));
  clone->data = l->data;
  clone->next = copy_list(l->next);
  return clone;
}

u32 destroy_list(list l)
{
  if (is_empty(l))
    return 1;
  list traverser = l;
  list prev_node;
  while (traverser)
  {
    prev_node = traverser;
    traverser = traverser->next;
    free(prev_node);
  }
  return 0;
}
