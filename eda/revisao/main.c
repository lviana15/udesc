#include <stdio.h>
#include <stdlib.h>

typedef struct teste {
  int inteiro;
  float real;
  char nome[30];
} informacao;

int main(void) {
  informacao *p, x = {321, 2.39, "Silva"};
  p = (struct teste *)malloc(sizeof(struct teste));
  p = &x;
  printf("valores struct X: %i, %f, %s", p->inteiro, p->real, p->nome);
}
