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
    new_queue->ocupation=0;
    return new_queue;
}

void enqueue(struct queue *q, u32 k)
{
    struct qnode *nq = new_qnode(k);
    q->ocupation+=1;
    if (q->rear == NULL)
    {
        q->front = q->rear = nq;
        return;
    }
    q->rear->next = nq;
    q->rear = nq;
}

struct queue *dequeue(struct queue *q)
{
    if(q->front == NULL)
        return q;
    struct qnode *prev_front = q->front;
    q->front = q->front->next;
    q->ocupation-=1;
    if (q->front == NULL)
        q->rear = NULL; 
    free(prev_front);
    return q;
}


u32 front(struct queue *q)
{
    return q->front->val;
}

bool queue_is_empty(struct queue *q)
{
    return (q->front == NULL && q->rear == NULL);
}

void print_queue(struct queue *q)
{
    struct qnode *t = q->front;
    while(t != NULL)
    {
        printf("%d -> ", t->val);
        t = t->next;
    }
    printf("[Ocupation: %d]\n",q->ocupation);
}

void destroy_queue(struct queue *q){

    while (!queue_is_empty(q))
    {
        q = dequeue(q);
    }
    free(q);
}