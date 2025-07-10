#ifndef GRAPH_H
#define GRAPH_H

#include <math.h>
#include <stdbool.h>
#define MAX_VERTICES 250

// struct para Vertice
typedef struct Vertex {
  float x;
  float y;
  float z;
} Vertex;

// structs auxiliares para geracao do cabecalho
typedef struct HeaderItem {
  float value;
  Vertex vi;
  Vertex vj;
} HeaderItem;

typedef struct Header {
  HeaderItem maxDE;
  HeaderItem minDE;
  HeaderItem maxDEN;
  HeaderItem minDEN;
  int numComponents;
  int componentSizes[MAX_VERTICES];
} Header;

// Matriz intermediaria para geracao das arestas
// Distancia Euclidiana entre cada vertice
// Guarda DEs min/max para utilizar na normalizacao
typedef struct DistanceMatrix {
  float matrix[MAX_VERTICES][MAX_VERTICES];
  float deMin;
  float deMax;
} DistanceMatrix;

// struct para grafo utilizando matriz de adjacencia
typedef struct Graph {
  int numVertices;
  bool adjMatrix[MAX_VERTICES][MAX_VERTICES];
} Graph;

Header *startHeader();

DistanceMatrix *createDistanceMatrix(int n);
DistanceMatrix *buildDistanceMatrix(int n, Vertex *vertices, Header *header);

// Gera arestas do grafo
// Utilizando limiar(threshold) definido para DEN entre vertices
void buildEdges(Graph *graph, DistanceMatrix *deMatrix, float threshold,
                Vertex *vertices, Header *header);

// Carrega arquivo base e gera um vetor de vertices
int loadVertices(const char *file, Vertex *vertices);

// Funcoes auxiliares para determinar DE e DEN entre vertices
float euclideanDistance(Vertex a, Vertex b);
float normalizedEuclideanDistance(float de, float deMin, float deMax);

// Funcoes para manipulacao do grafo
Graph *createGraph(int n);

bool isValidVertex(Graph *graph, int n);
void addEdge(Graph *graph, int source, int dest);
void DFS(Graph *graph, int v, bool *visited, int *componentSize);
void computeConnectedComponents(Graph *graph, Header *header);
void freeGraph(Graph *graph);
#endif
