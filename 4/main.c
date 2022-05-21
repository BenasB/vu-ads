#include <stdio.h>
#include <stdbool.h>
#include "queue.h"

#define NON_NODE -1 // Arbitrary number that can

struct QueueElement
{
    int node;
    int depth;
    int parent;
};

typedef struct QueueElement QueueElement;

void bfs(int nodeCount, int adjacentNodes[nodeCount][nodeCount], int startNode)
{
    bool visited[nodeCount];
    for (size_t i = 0; i < nodeCount; i++)
    {
        visited[i] = false;
    }

    int error;
    queue_t *queue = create_queue(&error);
    QueueElement startElement = {startNode, 0, NON_NODE};
    queue_push(queue, &startElement, sizeof(startElement), &error);

    while (!is_queue_empty(queue, &error))
    {
        QueueElement *currentElement = queue_pop(queue, &error);

        if (visited[currentElement->node - 1] == true)
            continue;

        visited[currentElement->node - 1] = true;

        for (size_t i = 0; i < currentElement->depth; i++)
        {
            printf("\t");
        }

        if (currentElement->parent != NON_NODE)
            printf("Node: %d, Parent: %d\n", currentElement->node, currentElement->parent);
        else
            printf("Node: %d, Parent: None\n", currentElement->node);

        // Push neighbours
        for (int i = 0; i < nodeCount; i++)
        {
            int currentNeighbour = adjacentNodes[currentElement->node - 1][i];
            if (currentNeighbour == NON_NODE)
                break;

            QueueElement neighbourElement = {currentNeighbour, currentElement->depth + 1, currentElement->node};
            queue_push(queue, &neighbourElement, sizeof(neighbourElement), &error);
        }
    }
}

int main()
{
    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        printf("Input file does not exist");
        return -1;
    }

    int nodeCount = 0;
    fscanf(file, "%d", &nodeCount);

    // First dimension represents which node
    // Second dimension represents its neighbours
    int adjacentNodes[nodeCount][nodeCount];

    // Initialize all adjacentNodes to NON_NODE
    for (size_t i = 0; i < nodeCount; i++)
    {
        for (size_t j = 0; j < nodeCount; j++)
        {
            adjacentNodes[i][j] = NON_NODE;
        }
    }

    char nextChar = 0;
    int currentNode = NON_NODE;
    int currentNeighbour = 0;
    while (nextChar != EOF)
    {
        int nextInteger;
        fscanf(file, "%d", &nextInteger);
        nextChar = fgetc(file);

        if (currentNode == NON_NODE)
        {
            currentNode = nextInteger;
        }
        else
        {
            int adjacentNode = nextInteger;
            adjacentNodes[currentNode - 1][currentNeighbour] = adjacentNode;
            currentNeighbour++;
        }

        if (nextChar == '\n')
        {
            currentNode = NON_NODE;
            currentNeighbour = 0;
        }
    }

    bfs(nodeCount, adjacentNodes, 1);
}