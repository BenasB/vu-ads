#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/// Used for debugging purposes
extern size_t malloc_cnt;
extern size_t free_cnt;

// Node data structure for the queue
typedef struct node_t
{
    void *data;
    struct node_t *next;
} node_t;

// Queue data structure
typedef struct queue_t
{
    node_t *head;
} queue_t;

///	Create an empty queue
/// @param errnum error number
/// @return pointer to queue
queue_t *create_queue(int *errnum);

/// Determines whether the queue is empty
/// @param queue pointer to queue
/// @param errnum error number
/// @return 1 if queue is empty and 0 if it's not
uint8_t is_queue_empty(queue_t *queue, int *errnum);

/// Push an element to queue
/// @param queue pointer to queue
/// @param data data that is going to be stored
/// @param size size of data
/// @param errnum error number
/// @return nothing
void queue_push(queue_t *queue, void *data, size_t size, int *errnum);

/// Pop the element from queue
/// @param queue pointer to queue
/// @param errnum error number
/// @return data of the element (must be freed manually)
void *queue_pop(queue_t *queue, int *errnum);

/// Peek an element in a queue
/// @param queue pointer to queue
/// @param errnum error number
/// @return data of the element
void *queue_peek(queue_t *queue, int *errnum);

/// Get the number of elements in a queue
/// @param queue pointer to queue
/// @param errnum error number
/// @return number of elements
size_t queue_elem_count(queue_t *queue, int *errnum);

/// Free memory allocated by queue
/// @param queue pointer to queue
/// @param errnum error number
/// @return nothing
void free_queue(queue_t *queue, int *errnum);

// error codes
// 1 - malloc failed
// 2 - param passed as NULL
// 3 - queue is empty

#endif /* QUEUE_H */