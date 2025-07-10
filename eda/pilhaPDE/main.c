#include "arq.h"
#include <math.h>

// Aplicação: apenas um pequeno teste de funções da pilha
int main() {
  info reg, data[] = {{"Wilson", 60}, {"Ponte", 15},  {"Marialucia", 10},
                      {"Uva", 13},    {"Veneza", 60}, {"Tania", 25}};
  int num_of_students = sizeof(data) / sizeof(info);
  struct pilha *pilha = NULL;

  pilha = cria();

  if (vazia(pilha)) printf("\nPilha vazia\n");
  else printf("\nPilha não vazia\n");

  puts("\nEmpilhando");
  for (int i = 0; i < num_of_students; i++) {
    empilha(&data[i], pilha);
    printf("palavra: %s \n", data[i].palavra);
  }

  if (vazia(pilha)) printf("\nPilha vazia\n");
  else printf("\nPilha não vazia\n");

  busca(&reg, pilha);
  printf("\nTopo da pilha: %s \n", reg.palavra);

  buscaBase(&reg, pilha);
  printf("\nBase da pilha: %s \n", reg.palavra);

  printf("\nDesempilhando \n");
  for (int i = 1; i <= num_of_students; i++) {
    desempilha(&reg, pilha);
    printf("palavra: %s, ", reg.palavra);
    printf("tamanho da palavra: %i \n", reg.idade);
  }
  return 0;
}
