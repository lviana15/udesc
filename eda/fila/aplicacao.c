#include "info.h"
#include "refMovel.h"
#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define your data structures and functions here
int readFile(struct refMovel *queue) {
  info data;
  int result;
  int iterations = 0; // Initialize the iterations variable

  FILE *file = fopen("dataset_v1.csv", "r");
  if (file == NULL) {
    printf("Falha ao abrir arquivo.\n");
    return 0;
  }

  char line[256]; // Adjust this buffer size based on your data
  while (fgets(line, sizeof(line), file) != NULL) {
    if (sscanf(line, "%29[^,], %29[^,], %d, %29[^\n]", data.nome,
               data.matricula, &data.ranking, data.curso) == 4) {
      result = insere_(&data, queue);
      if (result) {
        iterations += result;
      } else {
        printf("Falha ao inserir: %s %s %d %s\n", data.nome,
               data.matricula, data.ranking, data.curso);
      }
    }
  }

  fclose(file);
  return iterations; // Return the total iterations
}

int displayMenu(struct refMovel *queue) {
  info data;
  int choice;
  int result;
  int iterations = 0; // Initialize the iterations variable

  while (1) {
    printf("\nFila Prioridade com Referencia Movel\n");
    printf("1. Inserir item\n");
    printf("2. Remover item\n");
    printf("3. Verificar fila vazia\n");
    printf("4. Verificar tamanho da fila\n");
    printf("5. Item na frente\n");
    printf("6. Item na cauda\n");
    printf("7. Reiniciar fila\n");
    printf("8. Sair\n");
    printf("Digite uma opcao: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      printf("Digite dados (Nome, Matricula, Ranking, Curso): ");
      scanf("%s %s %d %s", data.nome, data.matricula, &data.ranking,
            data.curso);
      result = insere_(&data, queue);
      if (result) {
        printf("Item inserido com sucesso\n");
        iterations += result; // Accumulate iterations
      } else {
        printf("Falha ao inserir\n");
      }
      break;

    case 2:
      result = remove_(&data, queue);
      if (result) {
        printf("Item removido: %s %s %d %s\n", data.nome, data.matricula,
               data.ranking, data.curso);
      } else {
        printf("Falha ao remover item\n");
      }
      break;

    case 3:
      if (testaVazia_(queue)) {
        printf("Fila vazia\n");
      } else {
        printf("Fila não vazia\n");
      }
      break;

    case 4:
      printf("Tamanho da fila: %d\n", tamanhoDaFila_(queue));
      break;

    case 5:
      result = buscaNaFrente_(&data, queue);
      if (result) {
        printf("Item na frente: %s %s %d %s\n", data.nome, data.matricula,
               data.ranking, data.curso);
      } else {
        printf("Fila vazia.\n");
      }
      break;

    case 6:
      result = buscaNaCauda_(&data, queue);
      if (result) {
        printf("Item na cauda: %s %s %d %s\n", data.nome, data.matricula,
               data.ranking, data.curso);
      } else {
        printf("Fila vazia.\n");
      }
      break;

    case 7:
      reinicia_(queue);
      printf("Fila reiniciada.\n");
      break;

    case 8:
      destroi_(queue);
      printf("Fila destruída.\n");
      return iterations; // Return the total iterations when you exit

    default:
      printf("Escolha inválida. Tente novamente\n");
    }
  }
}

int main() {
  struct refMovel *queue = NULL;
  int tamInfo = sizeof(info); // Update this with your info struct size

  queue = cria_(tamInfo);

  if (queue == NULL) {
    printf("Erro criando a fila\n");
    return 1;
  }

  int totalIterations = 0; // Initialize the total iterations

  int choice;
  printf("Escolha uma aplicação:\n");
  printf("1. Ler dados de um arquivo CSV\n");
  printf("2. Realizar operações manuais\n");
  printf("Digite sua escolha: ");
  scanf("%d", &choice);

  if (choice == 1) {
    totalIterations = readFile(queue);
  } else if (choice == 2) {
    totalIterations = displayMenu(queue);
  } else {
    printf("Escolha inválida. Saindo...\n");
  }

  destroi_(queue);
  printf("Fila destruída.\n");

  if (choice == 1 || choice == 2) {
    printf("Total de Iterações: %d\n", totalIterations);
  }

  return 0;
}
