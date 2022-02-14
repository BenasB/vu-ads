// 2110541

#include <stdlib.h>
#include "queue.h"

Queue queue_new()
{
    Queue newQueue = {NULL, NULL, 0};
    return newQueue;
}

bool is_empty(Queue queue)
{
    return queue.size == 0;
}

void *enqueue(Queue *queue, void *data)
{
    QueueNode *newTail = malloc(sizeof(QueueNode));

    if (newTail == NULL)
        return NULL;

    newTail->data = data;
    newTail->next = NULL;
    queue->size++;

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

    return data;
}

void *dequeue(Queue *queue)
{
    if (is_empty(*queue))
        return NULL;

    QueueNode *oldHead = queue->head;
    queue->head = queue->head->next;

    queue->size--;

    if (queue->head == NULL) // Removed the last item
        queue->tail = NULL;

    void *data = oldHead->data;

    free(oldHead);

    return data;
}

void *peek(Queue queue)
{
    if (is_empty(queue))
        return NULL;

    return queue.head->data;
}

void queue_clear(Queue *queue)
{
    while (!is_empty(*queue))
    {
        dequeue(queue);
    }
}