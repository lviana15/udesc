#include "arq.h"
#include <math.h>

// Aplicação: apenas um pequeno teste de funções da pilha
int main() {
  info reg, data[] = {{"Wilson", 60}, {"Ponte", 15},  {"Marialucia", 10},
                      {"Uva", 13},    {"Veneza", 60}, {"Tania", 25}};
  int num_of_students = sizeof(data) / sizeof(info);
  struct pilha *pil = NULL;

  pil = cria();

  printf("\n\n");
  puts("Empilhando");
  for (int i = 0; i < num_of_students; i++) {
    empilha(&data[i], pil);
    printf("palavra: %s \n", data[i].palavra);
  }
  busca(&reg, pil);
  printf("\nTopo da pilha: %s \n", reg.palavra);

  printf("\nDesempilhando \n");
  for (int i = 1; i <= num_of_students; i++) {
    desempilha(&reg, pil);
    printf("palavra: %s, ", reg.palavra);
    printf("tamanho da palavra: %i \n", reg.idade);
  }
  printf("\n\n");
  return 0;
}

