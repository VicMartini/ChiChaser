
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef uint32_t u32;

struct qnode
{
    u32 val;
    struct qnode *next;
};

struct queue
{
    struct qnode *front, *rear;
};

struct qnode *new_qnode(u32 k);
struct queue *new_queue();
void enqueue(struct queue *q, u32 k);
void dequeue(struct queue *q);

