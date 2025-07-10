#include "queue.h"

#include <stdlib.h>

// Cria e inicializa uma fila de prioridade com capacidade fixa
PQueue *createPQueue(int capacity) {
  PQueue *pq = (PQueue *)malloc(sizeof(PQueue));
  pq->nodes = (PQueueNode *)malloc(sizeof(PQueueNode) * capacity);
  pq->size = 0;
  pq->capacity = capacity;
  return pq;
}

// Troca dois nós da fila de prioridade
void swap(PQueueNode *a, PQueueNode *b) {
  PQueueNode temp = *a;
  *a = *b;
  *b = temp;
}

// Reorganiza heap de baixo para cima
void heapifyUp(PQueue *pq, int index) {
  while (index > 0) {
    int parent = (index - 1) / 2;

    if (pq->nodes[parent].distance > pq->nodes[index].distance) {
      swap(&pq->nodes[parent], &pq->nodes[index]);
      index = parent;
    } else {
      break;
    }
  }
}

// Reorganiza heap de cima para baixo
void heapifyDown(PQueue *pq, int index) {
  int smallest = index;
  int left = index * 2 + 1;
  int right = index * 2 + 2;

  if (left < pq->size &&
      pq->nodes[left].distance < pq->nodes[smallest].distance)
    smallest = left;

  if (right < pq->size &&
      pq->nodes[right].distance < pq->nodes[smallest].distance)
    smallest = right;

  if (smallest != index) {
    swap(&pq->nodes[index], &pq->nodes[smallest]);
    heapifyDown(pq, smallest);
  }
}

// Insere um novo nó na fila de prioridade
void enqueue(PQueue *pq, int vertex, float distance) {
  if (pq->size >= pq->capacity) return;

  pq->nodes[pq->size].vertex = vertex;
  pq->nodes[pq->size].distance = distance;

  heapifyUp(pq, pq->size);
  pq->size++;
}

// Remove o nó de menor distância da fila
PQueueNode dequeue(PQueue *pq) {
  PQueueNode min = pq->nodes[0];
  pq->nodes[0] = pq->nodes[--pq->size];

  heapifyDown(pq, 0);
  return min;
}

// Verifica se a fila de prioridade está vazia
bool isEmpty(PQueue *pq) { return pq->size == 0; }

// Libera memória alocada da fila
void freePQueue(PQueue *pq) {
  if (pq != NULL) {
    free(pq->nodes);
    free(pq);
  }
}
