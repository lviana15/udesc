#include "graph.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void saveGraphToTXT(const char *filename, Graph *graph) {
  FILE *file = fopen(filename, "w");
  if (!file) {
    perror("Erro ao abrir o arquivo");
    return;
  }

  for (int i = 0; i < graph->numVertices; i++) {
    for (int j = i + 1; j < graph->numVertices; j++) {
      if (graph->adjMatrix[i][j] != 0.0f) {
        fprintf(file, "%d %d\n", i, j);
      }
    }
  }

  fclose(file);
}

void saveGraphToCSV(const char *filename, Graph *graph, Header *header) {
  FILE *file = fopen(filename, "w");
  if (!file) {
    perror("Erro ao abrir o arquivo CSV para escrita");
    return;
  }

  // Cabeçalho com estatísticas
  fprintf(file, "# Total de vértices,%d\n", graph->numVertices);
  fprintf(file, "# Maior DE,%.4f,(%.2f,%.2f,%.2f)-(%.2f,%.2f,%.2f)\n",
          header->maxDE.value, header->maxDE.vi.x, header->maxDE.vi.y,
          header->maxDE.vi.z, header->maxDE.vj.x, header->maxDE.vj.y,
          header->maxDE.vj.z);
  fprintf(file, "# Menor DE,%.4f,(%.2f,%.2f,%.2f)-(%.2f,%.2f,%.2f)\n",
          header->minDE.value, header->minDE.vi.x, header->minDE.vi.y,
          header->minDE.vi.z, header->minDE.vj.x, header->minDE.vj.y,
          header->minDE.vj.z);
  fprintf(file, "# Maior DEN,%.4f,(%.2f,%.2f,%.2f)-(%.2f,%.2f,%.2f)\n",
          header->maxDEN.value, header->maxDEN.vi.x, header->maxDEN.vi.y,
          header->maxDEN.vi.z, header->maxDEN.vj.x, header->maxDEN.vj.y,
          header->maxDEN.vj.z);
  fprintf(file, "# Menor DEN,%.4f,(%.2f,%.2f,%.2f)-(%.2f,%.2f,%.2f)\n",
          header->minDEN.value, header->minDEN.vi.x, header->minDEN.vi.y,
          header->minDEN.vi.z, header->minDEN.vj.x, header->minDEN.vj.y,
          header->minDEN.vj.z);
  fprintf(file, "# Componentes conexos,%d\n", header->numComponents);
  fprintf(file, "# Tamanhos dos componentes");

  for (int i = 0; i < header->numComponents; i++) {
    fprintf(file, "%s%d", i == 0 ? "," : ";", header->componentSizes[i]);
  }

  fprintf(file, "\n");

  // Cabeçalho de colunas de arestas
  fprintf(file, "origem,destino\n");

  // Para grafos não direcionados, consideramos apenas i < j
  for (int i = 0; i < graph->numVertices; i++) {
    for (int j = i + 1; j < graph->numVertices; j++) {
      if (graph->adjMatrix[i][j] == true) {
        fprintf(file, "%d,%d\n", i, j);
      }
    }
  }

  fclose(file);
  printf("Grafo salvo com sucesso em: %s\n", filename);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Uso: %s <arquivo_vertices>\n", argv[0]);
    return 1;
  }

  Header *header = startHeader();

  // Gerando vetor de vertices carregando do arquivo
  Vertex vertices[MAX_VERTICES];
  int numVertices = loadVertices(argv[1], vertices);
  if (numVertices <= 0) {
    return 1;
  }

  // Matriz auxiliar com distancia entre vertices
  Graph *graph = createGraph(numVertices);
  DistanceMatrix *dm = buildDistanceMatrix(numVertices, vertices, header);

  // Utiliza matriz auxiliar e limiar definido pra gerar as arestas do grafo
  float threshold = 0.3f;
  buildEdges(graph, dm, threshold, vertices, header);
  computeConnectedComponents(graph, header);

  saveGraphToCSV("output.csv", graph, header);
  saveGraphToTXT("grafo.txt", graph);

  free(header);
  free(dm);
  freeGraph(graph);
  return 0;
}
