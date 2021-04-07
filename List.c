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

list addl(u32 key, u32 val, list l)
{
  list new_head = malloc(sizeof(struct node));
  new_head->val = val;
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

u32 head(list l)
{
  assert(!is_empty(l));
  return l->val;
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

u32 search(u32 key, list l)
{

  list traverser = l;

  while (traverser && traverser->key != key)
    traverser = traverser->next;

  return traverser ? traverser->val : 0xFFFFFFFF; //Notese que si el vertice no está devolvemos 0xFFFFFFFF (incluido el caso de la lista vacia)
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

u32 *index_ith(unsigned int i, list l)
{
  assert(length(l) > i);
  list traverser = l;
  for (unsigned int j = 0; j < i; ++j)
  {
    traverser = traverser->next;
  }
  return traverser->val;
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

list copy_list(list l)
{
  if (is_empty(l))
    return NULL;
  list clone = malloc(sizeof(struct node));
  clone->val = l->val;
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
