#include "fde.h"
#include "info.h"
#include "refMovel.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

double preencheFRM(struct refMovel *FRM, char selectedLines[][35],
                   int maxLines) {
  info data;
  int result, iterations = 0;
  double average;

  // Insere linhas na fila
  for (int i = 0; i < maxLines; i++) {
    if (sscanf(selectedLines[i], "%29[^,], %29[^,], %d, %29[^\n]", data.nome,
               data.matricula, &data.ranking, data.curso) == 4) {
      result = insereFRM(&data, FRM);
      if (result) {
        iterations += result;
      }
    }
  }

  average = (double)iterations / maxLines;

  return average;
}

double preencheFDE(struct FDE *FDE, char selectedLines[][35], int maxLines) {
  info data;
  int result, iterations = 0;
  double average;

  // Insere linhas na fila
  for (int i = 0; i < maxLines; i++) {
    if (sscanf(selectedLines[i], "%29[^,], %29[^,], %d, %29[^\n]", data.nome,
               data.matricula, &data.ranking, data.curso) == 4) {
      result = insereFDE(&data, FDE);
      if (result) {
        iterations += result;
      }
    }
  }

  average = (double)iterations / maxLines;

  return average;
}

void displayMenu(struct refMovel *FRM) {
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
      result = insereFRM(&data, FRM);
      if (result) {
        printf("Item inserido com sucesso\n");
      } else {
        printf("Falha ao inserir\n");
      }
      break;

    case 2:
      result = removeFRM(&data, FRM);
      if (result) {
        printf("Item removido: %s %s %d %s\n", data.nome, data.matricula,
               data.ranking, data.curso);
      } else {
        printf("Falha ao remover item\n");
      }
      break;

    case 3:
      if (testaVaziaFRM(FRM)) {
        printf("Fila vazia\n");
      } else {
        printf("Fila não vazia\n");
      }
      break;

    case 4:
      printf("Tamanho da fila: %d\n", tamanhoDaFilaFRM(FRM));
      break;

    case 5:
      result = buscaNaFrenteFRM(&data, FRM);
      if (result) {
        printf("Item na frente: %s %s %d %s\n", data.nome, data.matricula,
               data.ranking, data.curso);
      } else {
        printf("Fila vazia.\n");
      }
      break;

    case 6:
      result = buscaNaCaudaFRM(&data, FRM);
      if (result) {
        printf("Item na cauda: %s %s %d %s\n", data.nome, data.matricula,
               data.ranking, data.curso);
      } else {
        printf("Fila vazia.\n");
      }
      break;

    case 7:
      reiniciaFRM(FRM);
      printf("Fila reiniciada.\n");
      break;

    case 8:
      destroiFRM(FRM);
      printf("Fila destruída.\n");

    default:
      printf("Escolha inválida. Tente novamente\n");
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Execução correta: %s <arquivo> <qtd casos>\n", argv[0]);
    printf("Exemplo:\n");
    printf("%s datasetFRMv1 500\n", argv[0]);

    return 1;
  }

  int choice, selectedCount, lineCount, tamInfo = sizeof(info);
  double averageFRM, averageFDE;

  struct FDE *FDE = NULL;
  FDE = criaFDE(tamInfo);

  if (FDE == NULL) {
    printf("Erro criando a fila\n");
    return 1;
  }

  struct refMovel *FRM = NULL;
  FRM = criaFRM(tamInfo);

  if (FRM == NULL) {
    printf("Erro criando a fila\n");
    return 1;
  }

  // Tamanho maximo do arquivo (linhas)
  // 10001 Linhas - Cada linha no max 35 caracteres
  char selectedLines[10001][35];
  char line[35];

  // Linhas a serem selecionadas
  int maxLines = atoi(argv[2]);

  srand(time(NULL));

  FILE *file = fopen(argv[1], "r");
  if (file == NULL) {
    printf("Falha ao abrir arquivo.\n");
    return 1;
  }

  printf("Escolha uma aplicação:\n");
  printf("1. Ler dados do arquivo\n");
  printf("2. Realizar operações manuais\n");
  printf("\nDigite sua escolha: ");
  scanf("%d", &choice);

  switch (choice) {
  case 1:
    while (selectedCount < maxLines &&
           fgets(line, sizeof(line), file) != NULL) {
      lineCount++;

      int randomValue = (rand() % 10001) + 1;

      // Check if the generated number is less than or equal to a threshold
      // (e.g., 50) Adjust the threshold to control how many lines you select
      if (randomValue <= maxLines) {
        strcpy(selectedLines[selectedCount], line);
        selectedCount++;
      }
    }

    // Inserir filas
    averageFRM = preencheFRM(FRM, selectedLines, selectedCount);
    averageFDE = preencheFDE(FDE, selectedLines, selectedCount);
    printf("Media iteracoes Fila com Referencia Movel: %.2f\n", averageFRM);
    printf("Media iteracoes Fila Duplamente Encadeada: %.2f\n", averageFDE);
    break;

  case 2:
    displayMenu(FRM);
  }

  destroiFRM(FRM);
  printf("Fila destruída.\n");

  fclose(file);

  return 0;
}
