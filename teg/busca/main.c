#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "graph.h"
#include "queue.h"

void dijkstra(Graph *graph, Vertex *vertices, float *dist) {
  int n = graph->numVertices;
  float globalMinDist = INFINITY;
  int bestSrc = -1, bestDst = -1;

  for (int src = 0; src < n; src++) {
    bool visited[MAX_VERTICES] = {false};
    for (int i = 0; i < n; i++) dist[i] = INFINITY;
    dist[src] = 0.0f;

    PQueue *pq = createPQueue(n);
    enqueue(pq, src, 0.0f);

    while (!isEmpty(pq)) {
      PQueueNode node = dequeue(pq);
      int u = node.vertex;
      if (visited[u]) continue;
      visited[u] = true;

      for (int v = 0; v < n; v++) {
        float weight = graph->adjMatrix[u][v];
        if (weight > 0.0f && !visited[v]) {
          float alt = dist[u] + weight;
          if (alt < dist[v]) {
            dist[v] = alt;
            enqueue(pq, v, alt);
          }
        }
      }
    }

    for (int dst = 0; dst < n; dst++) {
      if (src != dst && vertices[src].species != vertices[dst].species) {
        if (dist[dst] < globalMinDist) {
          globalMinDist = dist[dst];
          bestSrc = src;
          bestDst = dst;
        }
      }
    }

    freePQueue(pq);
  }

  if (bestSrc != -1 && bestDst != -1) {
    printf("Dijkstra (global): Menor distância entre espécies diferentes: %f\n",
           globalMinDist);
    printf("Pinguins: [%d] (%c) -> [%d] (%c)\n", bestSrc,
           vertices[bestSrc].species, bestDst, vertices[bestDst].species);
  }
}

void prim(Graph *graph, Vertex *vertices, int startVertex) {
  int n = graph->numVertices, minU = -1, minV = -1, parent[MAX_VERTICES];
  float minDistance = INFINITY, key[MAX_VERTICES];
  bool inMST[MAX_VERTICES];

  for (int i = 0; i < n; i++) {
    key[i] = INFINITY;
    parent[i] = -1;
    inMST[i] = false;
  }

  key[startVertex] = 0.0f;

  PQueue *pq = createPQueue(n);
  enqueue(pq, startVertex, 0.0f);

  while (!isEmpty(pq)) {
    PQueueNode node = dequeue(pq);
    int u = node.vertex;

    if (inMST[u]) continue;
    inMST[u] = true;

    for (int v = 0; v < n; v++) {
      float weight = graph->adjMatrix[u][v];
      if (weight > 0.0f && !inMST[v] && weight < key[v]) {
        key[v] = weight;
        parent[v] = u;
        enqueue(pq, v, weight);
      }
    }
  }

  for (int v = 0; v < n; v++) {
    int u = parent[v];
    if (u != -1 && vertices[u].species != vertices[v].species) {
      float weight = graph->adjMatrix[u][v];
      if (weight < minDistance) {
        minDistance = weight;
        minU = u;
        minV = v;
      }
    }
  }

  if (minU != -1 && minV != -1) {
    printf("Prim: Menor distância entre espécies diferentes na MST: %f\n",
           minDistance);
    printf("Pinguins: [%d] (%c) <-> [%d] (%c)\n", minU, vertices[minU].species,
           minV, vertices[minV].species);
  }

  freePQueue(pq);
}

void printFormattedTime(double seconds) {
  if (seconds >= 1.0) {
    printf("%.3f s", seconds);
  } else if (seconds >= 1e-3) {
    printf("%.3f ms", seconds * 1e3);
  } else if (seconds >= 1e-6) {
    printf("%.3f µs", seconds * 1e6);
  } else {
    printf("%.3f ns", seconds * 1e9);
  }
  printf("\n");
}

int main() {
  Vertex vertices[MAX_VERTICES];
  float dist[MAX_VERTICES];

  int num_vertices = loadVertices("db_204x3_v1.csv", vertices);
  if (num_vertices <= 0) {
    fprintf(stderr, "Erro ao carregar vértices. n = %d\n", num_vertices);
    return 1;
  }

  Graph *graph = createGraph(num_vertices);
  if (!graph) {
    fprintf(stderr, "Erro ao criar grafo.\n");
    return 1;
  }

  DistanceMatrix *dm = buildDistanceMatrix(num_vertices, vertices);
  if (!dm) {
    fprintf(stderr, "Erro ao construir matriz de distâncias.\n");
    freeGraph(graph);
    return 1;
  }

  buildEdges(graph, dm);

  double totalPrim = 0.0;
  double totalDijkstra = 0.0;

  printf("Executando %d vezes cada algoritmo...\n\n", 10);

  for (int i = 0; i < 10; i++) {
    printf("Execução %d:\n", i + 1);

    clock_t p1 = clock();
    prim(graph, vertices, 0);
    clock_t p2 = clock();
    double timePrim = (double)(p2 - p1) / CLOCKS_PER_SEC;

    printf("Tempo PRIM: ");
    printFormattedTime(timePrim);
    printf("\n");
    totalPrim += timePrim;

    clock_t d1 = clock();
    dijkstra(graph, vertices, dist);
    clock_t d2 = clock();
    double timeDijkstra = (double)(d2 - d1) / CLOCKS_PER_SEC;

    printf("Tempo Dijkstra: ");
    printFormattedTime(timeDijkstra);
    printf("\n\n");
    totalDijkstra += timeDijkstra;
  }

  printf("=== RESULTADO MÉDIO (%d execuções) ===\n", 10);
  printf("Tempo médio PRIM: ");
  printFormattedTime(totalPrim / 10);

  printf("Tempo médio Dijkstra: ");
  printFormattedTime(totalDijkstra / 10);

  freeGraph(graph);
  free(dm);
  return 0;
}
