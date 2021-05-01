
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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
u32 dequeue(struct queue *q);
bool queue_is_empty(struct queue *q);
typedef struct queue *queue;