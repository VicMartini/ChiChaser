#include <stdint.h>

typedef uint32_t u32;

struct GrafoSt{
  u32 num_vertices;
  u32 num_lados;
  u32 delta;
  Nodo* nodos;


};

struct Nodo{
    u32 nombre;
    u32 color;
    u32 grado;
    ListaNodos* vecinos;
};

struct ListaNodos{
    Nodo* nodo;
    ListaNodos* prox;
};