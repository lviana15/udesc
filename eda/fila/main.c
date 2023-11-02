#include "fila.h"
#include "info.h"
#include "refMovel.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int readFile(struct refMovel *queue) {
  info data;
  int result;
  int iterations = 0;

  // Insere linhas na fila
  for (int i = 0; i < selectedCount; i++) {
    if (sscanf(selectedLines[i], "%29[^,], %29[^,], %d, %29[^\n]", data.nome,
               data.matricula, &data.ranking, data.curso) == 4) {
      result = insere_(&data, queue);
      if (result) {
        iterations += result;
      } else {
        printf("Falha ao inserir: %s %s %d %s\n", data.nome, data.matricula,
               data.ranking, data.curso);
      }
    }
  }

  return iterations;
}

int displayMenu(struct refMovel *queue) {
  info data;
  int choice, result;

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

    default:
      printf("Escolha inválida. Tente novamente\n");
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Execução correta: %s <arquivo> <numero para teste>\n", argv[0]);
    printf("Exemplo:\n");
    printf("./%s dataset_v1 500\n", argv[0]);
  }

  struct refMovel *queue = NULL;
  int choice, selectedCount;
  int tamInfo = sizeof(info);
  queue = cria_(tamInfo);

  if (queue == NULL) {
    printf("Erro criando a fila\n");
    return 1;
  }

  // Tamanho maximo do arquivo (linhas)
  // 10001 Linhas - Cada linha no max 35 caracteres
  char selectedLines[10001][35];
  int lineCount = 0;

  char line[35];

  // Linhas a serem selecionadas
  int maxLines = atoi(argv[2]);
  int selectedCount = 0;

  srand(time(NULL));

  FILE *file = fopen(argv[1], "r");
  if (file == NULL) {
    printf("Falha ao abrir arquivo.\n");
    return 1;
  }

  printf("Escolha uma aplicação:\n");
  printf("1. Ler dados de um arquivo CSV\n");
  printf("2. Realizar operações manuais\n");
  printf("Digite sua escolha: ");
  scanf("%d", &choice);

  switch (choice) {
  case 1:

    // Seleciona linhas aleatorias
    while (fgets(line, sizeof(line), file)) {
      lineCount++;

      // Chance baseada na qtd de linhas desejada
      double chance = (double)maxLines / lineCount;
      // Se aleatorio for menor que chance -> Seleciona linha
      if (selectedCount < maxLines && (rand() / (double)RAND_MAX) < chance) {
        if (selectedCount < 100) {
          strcpy(selectedLines[selectedCount], line);
          selectedCount++;
        } else {
          break;
        }
      }
    }
    break;

  case 2:
    displayMenu(queue);
  }
  destroi_(queue);
  printf("Fila destruída.\n");

  fclose(file);

  return 0;
}
