#include "graph.h"

#include <stdio.h>
#include <stdlib.h>

DistanceMatrix *createDistanceMatrix(int n) {
  DistanceMatrix *matrix = (DistanceMatrix *)malloc(sizeof(DistanceMatrix));

  // Inicializa valores para comparacao
  matrix->deMin = INFINITY;
  matrix->deMax = -INFINITY;

  // Inicializa matriz com valores neutros
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      matrix->matrix[i][j] = 0;
    }
  }

  return matrix;
}

DistanceMatrix *buildDistanceMatrix(int n, Vertex *vertices) {
  DistanceMatrix *distanceMatrix = createDistanceMatrix(n);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      float de = euclideanDistance(vertices[i], vertices[j]);

      // Atualiza matriz auxiliar com distancia entre vertices
      distanceMatrix->matrix[i][j] = de;

      // Nao considera auto-relacionamento (Distancia 0)
      if (i != j) {
        // Atualiza DE min e max
        if (de < distanceMatrix->deMin) {
          distanceMatrix->deMin = de;
        }
        if (de > distanceMatrix->deMax) {
          distanceMatrix->deMax = de;
        }
      }
    }
  }

  return distanceMatrix;
}

void buildEdges(Graph *graph, DistanceMatrix *deMatrix) {
  for (int i = 0; i < graph->numVertices; i++) {
    for (int j = i + 1; j < graph->numVertices; j++) {
      float den = normalizedEuclideanDistance(deMatrix->matrix[i][j],
                                              deMatrix->deMin, deMatrix->deMax);

      addEdge(graph, i, j, den);
    }
  }
}

int loadVertices(const char *filename, Vertex *vertices) {
  int count = 0;
  char line[256];

  FILE *file = fopen(filename, "r");
  if (!file) {
    return -1;
  }

  fgets(line, sizeof(line), file);

  while (fgets(line, sizeof(line), file)) {
    char s;
    float x, y, z;
    if (sscanf(line, "%c,%f,%f,%f", &s, &x, &y, &z) == 4) {
      vertices[count].species = s;
      vertices[count].x = x;
      vertices[count].y = y;
      vertices[count].z = z;
      count++;
    }
  }

  fclose(file);

  return count;
}

// Determina distancia euclidiana entre dois vertices
float euclideanDistance(Vertex a, Vertex b) {
  return sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) +
               (a.z - b.z) * (a.z - b.z));
}

// Utiliza deMin e deMax para normalizar valor
float normalizedEuclideanDistance(float de, float deMin, float deMax) {
  if (deMax - deMin == 0.0) return 0.0;
  return (de - deMin) / (deMax - deMin);
}

Graph *createGraph(int n) {
  if (n > MAX_VERTICES || n <= 0) {
    return NULL;
  }

  Graph *graph = (Graph *)malloc(sizeof(Graph));

  if (graph == NULL) {
    return NULL;
  }

  graph->numVertices = n;

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j) graph->adjMatrix[i][j] = 0.0;

  return graph;
}

// Verifica se vertice ta entre limites validos
bool isValidVertex(Graph *graph, int n) {
  return (n < graph->numVertices && n >= 0);
}

// Adiciona aresta no grafo
void addEdge(Graph *graph, int source, int dest, float weight) {
  if (!isValidVertex(graph, source) || !isValidVertex(graph, dest)) {
    return;
  }

  graph->adjMatrix[source][dest] = weight;
  graph->adjMatrix[dest][source] = weight;
}

// Navega o grafo verificando tamanho de cada componente
void DFS(Graph *graph, int v, bool *visited, int *componentSize) {
  visited[v] = true;
  (*componentSize)++;

  for (int i = 0; i < graph->numVertices; i++) {
    if (graph->adjMatrix[v][i] != 0.0f && !visited[i]) {
      DFS(graph, i, visited, componentSize);
    }
  }
}

void freeGraph(Graph *graph) {
  if (graph != NULL) free(graph);
}
