// For testing

#include <stdio.h>
#include "queue.h"

void dequeueAndPrint(Queue *q)
{
    printf("Size is: %d\n", size(*q));
    for (int i = 0; !is_empty(*q); i++)
    {
        double *item = dequeue(q);
        printf("%d: %f\n", i, *item);
    }
}

int main(int argc, char const *argv[])
{
    double a = 5.77;
    double b = 42.4564;

    Queue q = queue_new();

    enqueue(&q, &a);
    enqueue(&q, &b);

    double *firstElement = peek(q);
    printf("First element is: %f\n", *firstElement);
    printf("Size is: %d\n", size(q));
    for (int i = 0; size(q) != 0; i++)
    {
        double *item = dequeue(&q);
        printf("%d: %f\n", i, *item);
    }

    dequeueAndPrint(&q);
    dequeueAndPrint(&q);

    enqueue(&q, &a);
    enqueue(&q, &a);

    queue_clear(&q);

    enqueue(&q, &b);
    enqueue(&q, &b);
    enqueue(&q, &a);
    enqueue(&q, &b);
    enqueue(&q, &a);
    double c = 123456789.0;
    enqueue(&q, &c);
    enqueue(&q, &a);

    dequeueAndPrint(&q);
}
