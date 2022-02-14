#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

typedef struct QueueNode QueueNode;
typedef struct Queue Queue;

struct QueueNode // Allocated dynamically
{
    void *data; // For generic data
    QueueNode *next;
};

struct Queue
{
    QueueNode *head;
    QueueNode *tail;
    int size;
};

Queue queue_new();
bool is_empty(Queue queue);
void *enqueue(Queue *queue, void *data); // Returns NULL if failed, void *data otherwise
void *dequeue(Queue *queue);             // Returns NULL if failed, void *data otherwise
void *peek(Queue queue);                 // Returns NULL if failed, void *data otherwise
void queue_clear(Queue *queue);

#endif
