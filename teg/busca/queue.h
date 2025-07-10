#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

typedef struct PQueueNode {
  int vertex;
  float distance;
} PQueueNode;

typedef struct PQueue {
  PQueueNode *nodes;
  int size;
  int capacity;
} PQueue;

PQueue *createPQueue(int capacity);
void swap(PQueueNode *a, PQueueNode *b);
void heapifyUp(PQueue *queue, int index);
void heapifyUp(PQueue *queue, int index);
void heapifyDown(PQueue *queue, int index);
void enqueue(PQueue *queue, int vertex, float distance);
PQueueNode dequeue(PQueue *queue);
bool isEmpty(PQueue *pq);
void freePQueue(PQueue *pq);

#endif