#include <stdio.h>
#include "queue.h"

void dequeueAndPrint(Queue *q)
{
    for (int i = 0; !is_empty(*q); i++)
    {
        int *item = dequeue(q);
        printf("%d: %d\n", i, *item);
    }
}

int main(int argc, char const *argv[])
{
    int a = 5;
    int b = 42;
    Queue q = queue_new();
    enqueue(&q, &a);
    enqueue(&q, &b);
    dequeueAndPrint(&q);
    dequeueAndPrint(&q);

    enqueue(&q, &a);
    enqueue(&q, &a);
    enqueue(&q, &b);
    enqueue(&q, &b);
    enqueue(&q, &a);
    enqueue(&q, &b);
    enqueue(&q, &a);
    dequeueAndPrint(&q);
}
