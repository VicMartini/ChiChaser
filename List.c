#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "List.h"


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
  return l -> data;
}

list tail(list l)
{
  assert(!is_empty(l));
  list new_head;
  list old_head = l;
  new_head = old_head -> next;
  free(old_head);
  return new_head;
}

list addr(vertice *e, list l)
{
  list new_node = malloc(sizeof(struct node));
  new_node -> data = e;
  list traverser = l;
  if(!is_empty(traverser) )
  {
    while (traverser -> next != NULL)
    {
      traverser = traverser -> next;
    }
      traverser -> next = new_node;
      return l;
  }
  else
  {
    return new_node;
  }
  
}
unsigned int length(list l)
{
  int count = 0;
  list traverser = l;
  while (!is_empty(traverser))
  { 
    traverser = traverser -> next;
    ++count;
  }

  
  return count;
}

void concat(list l1, list l2){
  list traverser = l1;
  while (traverser -> next != NULL)
  {
    traverser = traverser -> next;
  }
  traverser -> next  = l2;
}

vertice *index(unsigned int i, list l)
{
  assert(length(l) > i);
  list traverser = l;
  for(unsigned int j = 0; j < i; ++j)
  {
    traverser = traverser -> next;
  } 
  return traverser -> data;
}

void take(unsigned int i, list l)
{
  assert(length(l) > i);
  list traverser = l;
  for(unsigned int j = 0; j < i; ++i)
  {
    traverser = traverser -> next;
  }
  list prev_node;
  while (!is_empty(traverser -> next))
  {
    prev_node = traverser;
    traverser = traverser -> next;
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
   traverser = traverser -> next;
   free(prev_node);
  }
  return traverser;  
}

list copy_list(list l){
  assert(!is_empty(l));
  list traverser = l;
  list new_node = malloc(sizeof(struct node));
  list new_list = new_node;
  new_node -> data = traverser -> data;
  traverser = traverser -> next;
  while (!is_empty(traverser -> next))
  {
    new_node -> next = malloc(sizeof(struct node));
    new_node = new_node -> next;
    new_node -> data = traverser -> data; 
    traverser = traverser -> next;
  }
  return new_list;  
}

void destroy_list(list l)
{
  assert(!is_empty(l));
  list traverser = l;
  list prev_node;
  while (traverser -> next != NULL)
  { 
    prev_node = traverser;
    traverser = traverser -> next;
    free(prev_node);
  }
  free(traverser);
}














