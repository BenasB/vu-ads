#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

void queue_new();
void queue_delete();
void enqueue();
void dequeue();
unsigned int size();
bool isEmpty();
void peek();

#endif
