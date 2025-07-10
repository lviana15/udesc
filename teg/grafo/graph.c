#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

Header *startHeader() {
  Header *header = (Header *)malloc(sizeof(Header));

  // Inicializa valores para comparacao
  header->minDEN.value = INFINITY;
  header->minDE.value = INFINITY;

  header->maxDEN.value = -INFINITY;
  header->maxDE.value = -INFINITY;

  return header;
}

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

DistanceMatrix *buildDistanceMatrix(int n, Vertex *vertices, Header *header) {
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
          if (header) {
            header->minDE.value = de;
            header->minDE.vi = vertices[i];
            header->minDE.vj = vertices[j];
          }
        }
        if (de > distanceMatrix->deMax) {
          distanceMatrix->deMax = de;
          if (header) {
            header->maxDE.value = de;
            header->maxDE.vi = vertices[i];
            header->maxDE.vj = vertices[j];
          }
        }
      }
    }
  }

  return distanceMatrix;
}

void buildEdges(Graph *graph, DistanceMatrix *deMatrix, float threshold,
                Vertex *vertices, Header *header) {
  for (int i = 0; i < graph->numVertices; i++) {
    for (int j = i + 1; j < graph->numVertices; j++) {
      float den = normalizedEuclideanDistance(deMatrix->matrix[i][j],
                                              deMatrix->deMin, deMatrix->deMax);
      
      // Se DEN estiver dentro do limiar, cria aresta entre vertices
      if (den <= threshold) {
        addEdge(graph, i, j);

        // Atualiza estrutura para gerar o cabecalho
        if (header) {
          if (den < header->minDEN.value) {
            header->minDEN.value = den;
            header->minDEN.vi = vertices[i];
            header->minDEN.vj = vertices[j];
          }
          if (den > header->maxDEN.value) {
            header->maxDEN.value = den;
            header->maxDEN.vi = vertices[i];
            header->maxDEN.vj = vertices[j];
          }
        }
      }
    }
  }
}

int loadVertices(const char *filename, Vertex *vertices) {
  int count = 0;

  FILE *file = fopen(filename, "r");
  if (!file) {
    return -1;
  }

  while (fscanf(file, "%f,%f,%f\n", &vertices[count].x, &vertices[count].y,
                &vertices[count].z) == 3) {
    count++;
    if (count >= MAX_VERTICES)
      break;
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
  if (deMax - deMin == 0.0)
    return 0.0;
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
    for (int j = 0; j < n; ++j)
      graph->adjMatrix[i][j] = 0.0;

  return graph;
}

// Verifica se vertice ta entre limites validos
bool isValidVertex(Graph *graph, int n) {
  return (n < graph->numVertices && n >= 0);
}

// Adiciona aresta no grafo
void addEdge(Graph *graph, int source, int dest) {
  if (!isValidVertex(graph, source) && !isValidVertex(graph, dest)) {
    return;
  }

  graph->adjMatrix[source][dest] = true;
  graph->adjMatrix[dest][source] = true;
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

// Utiliza DFS incrementando contagem de componentes desconexos
void computeConnectedComponents(Graph *graph, Header *header) {
  bool visited[MAX_VERTICES] = {false};
  int count = 0;

  for (int i = 0; i < graph->numVertices; i++) {
    if (!visited[i]) {
      int size = 0;
      DFS(graph, i, visited, &size);
      header->componentSizes[count++] = size;
    }
  }

  header->numComponents = count;
}

void freeGraph(Graph *graph) {
  if (graph != NULL)
    free(graph);
}
