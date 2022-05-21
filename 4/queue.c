#include "queue.h"

size_t malloc_cnt = 0;
size_t free_cnt = 0;

node_t *create_node(void *data, size_t size, int *errnum)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    ++malloc_cnt;

    if (node == NULL)
    {
        if (errnum != NULL)
            *errnum = 1;
        return NULL;
    }

    node->data = malloc(size);
    ++malloc_cnt;

    if (node->data == NULL)
    {
        if (errnum != NULL)
            *errnum = 1;
        return NULL;
    }

    memcpy(node->data, data, size);

    node->next = NULL;

    return node;
}

void free_node(node_t **node, int *errnum)
{
    if ((node == NULL) || (*node == NULL))
    {
        if (errnum != NULL)
            *errnum = 2;
        return;
    }
    if ((*node)->data != NULL)
    {
        free((*node)->data);
        ++free_cnt;
    }
    free(*node);
    ++free_cnt;

    *node = NULL;
}

queue_t *create_queue(int *errnum)
{
    queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
    ++malloc_cnt;

    if (queue == NULL)
    {
        if (errnum != NULL)
            *errnum = 1;
        return NULL;
    }
    queue->head = NULL;
    return queue;
}

uint8_t is_queue_empty(queue_t *queue, int *errnum)
{
    if (queue == NULL)
    {
        if (errnum != NULL)
            *errnum = 2;
        return 0;
    }
    return (queue->head == NULL);
}

void queue_push(queue_t *queue, void *data, size_t size, int *errnum)
{
    if (queue == NULL)
    {
        if (errnum != NULL)
            *errnum = 2;
        return;
    }

    if (queue->head == NULL)
    {
        node_t *temp = queue->head;
        queue->head = create_node(data, size, errnum);
        queue->head->next = temp;
        return;
    }

    node_t *iter = queue->head;
    while (iter->next)
    {
        iter = iter->next;
    }
    node_t *node = create_node(data, size, errnum);
    if (node == NULL)
        return;
    node_t *temp = iter->next;
    iter->next = node;
    node->next = temp;
}

void *queue_pop(queue_t *queue, int *errnum)
{
    if (queue == NULL)
    {
        if (errnum != NULL)
            *errnum = 2;
        return NULL;
    }
    if (queue->head == NULL)
    {
        if (errnum != NULL)
            *errnum = 3;
        return NULL;
    }

    node_t *temp = queue->head;
    void *data = temp->data;
    queue->head = queue->head->next;
    free(temp);
    ++free_cnt;
    return data;
}

void *queue_peek(queue_t *queue, int *errnum)
{
    if (queue == NULL)
    {
        if (errnum != NULL)
            *errnum = 2;
        return NULL;
    }
    if (queue->head == NULL)
    {
        if (errnum != NULL)
            *errnum = 3;
        return NULL;
    }
    return queue->head->data;
}

size_t queue_elem_count(queue_t *queue, int *errnum)
{
    if (queue == NULL)
    {
        if (errnum != NULL)
            *errnum = 2;
        return 0;
    }
    size_t i;
    node_t *iter = queue->head;
    for (i = 0; iter; ++i)
    {
        iter = iter->next;
    }
    return i;
}

void free_queue(queue_t *queue, int *errnum)
{
    if (queue == NULL)
    {
        if (errnum != NULL)
            *errnum = 2;
        return;
    }
    node_t *iter = queue->head;
    while (iter)
    {
        node_t *temp = iter;
        iter = iter->next;
        free_node(&temp, errnum);
    }
    free(queue);
    ++free_cnt;
}