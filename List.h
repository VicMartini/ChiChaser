#include <stdint.h>
#include <stdbool.h>
#include "VerticeSt.h"
typedef uint32_t u32;

struct node
{
  u32 val;
  u32 key;
  struct node *next;
};
typedef struct node *list;

list addl(u32 key, u32 val, list l);
bool in_list(u32 key, list l);
list new_list(void);
bool is_empty(list l);
u32 head(list l);
list tail(list l);
u32 search(u32 key, list l);
unsigned int length(list l);
void concat(list l1, list l2);
u32 index_ith(unsigned int i, list l);
void take(unsigned int i, list l);
list drop(unsigned int i, list l);
list copy_list(list l);
u32 destroy_list(list l);
