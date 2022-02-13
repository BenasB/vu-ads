#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

typedef struct QueueNode QueueNode;
typedef struct Queue Queue;

struct QueueNode
{
    void *data; // For generic data
    QueueNode *next;
};

struct Queue
{
    QueueNode *head;
    QueueNode *tail;
};

Queue queue_new();
bool is_empty(Queue queue);
void enqueue(Queue *queue, void *data);
void *dequeue(Queue *queue);
void *peek(Queue queue);
int size(Queue queue);
void queue_delete(Queue *queue);

#endif
