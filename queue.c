#include "assert.h"
#include "queue.h"

struct qnode *new_qnode(u32 k)
{
    struct qnode *nq = malloc(sizeof(struct qnode));
    nq->val = k;
    nq->next = NULL;
    return nq;
}

struct queue *new_queue()
{
    struct queue *new_queue = malloc(sizeof(struct queue));
    new_queue->front = new_queue->rear = NULL;
    return new_queue;
}

void enqueue(struct queue *q, u32 k)
{
    struct qnode *nq = new_qnode(k);
    if (q->rear == NULL)
    {
        q->front = q->rear = nq;
        return;
    }
    q->rear->next = nq;
    q->rear = nq;
}

u32 dequeue(struct queue *q)
{
    u32 elem;
    assert(q->front == NULL);
    struct qnode *prev_front = q->front;
    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL; 
    elem = prev_front->val;
    free(prev_front);
    return elem;
}

bool queue_is_empty(struct queue *q)
{
    return q->front == NULL && q->front == NULL;
}