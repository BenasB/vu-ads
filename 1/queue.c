#include <stdlib.h>
#include "queue.h"

Queue queue_new()
{
    Queue newQueue = {NULL, NULL};
    return newQueue;
}

bool is_empty(Queue queue)
{
    return queue.head == NULL;
}

void enqueue(Queue *queue, void *data)
{
    QueueNode *newTail = malloc(sizeof(QueueNode));
    newTail->data = data;
    newTail->next = NULL;

    if (queue->tail == NULL)
    {
        queue->tail = newTail;
        queue->head = queue->tail;
    }
    else
    {
        queue->tail->next = newTail;
        queue->tail = newTail;
    }
}

void *dequeue(Queue *queue)
{
    if (is_empty(*queue))
        return NULL;

    QueueNode *oldHead = queue->head;
    queue->head = queue->head->next;

    if (queue->head == NULL)
        queue->tail = NULL;

    void *data = oldHead->data;

    free(oldHead);

    return data;
}