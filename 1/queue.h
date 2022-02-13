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

Queue *queue_new();
bool isEmpty(Queue queue);
void enqueue(void *data);
void dequeue(void *data);
void peek(Queue queue);
unsigned int size(Queue queue);
void queue_delete(Queue queue);

#endif
