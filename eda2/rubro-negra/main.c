#include "rubroNegra.h"
#include <stdio.h>
#include <time.h>

void trocar(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void fisherYates(int *v, int tam) {
  srand(time(NULL));
  for (int i = tam - 1; i > 0; i--) {
    int j = rand() % (i + 1);
    trocar(&v[i], &v[j]);
  }
}

int *geraVetor(int n) {
  int *v = malloc(n * sizeof(int));
  for (int i = 0; i < n; i++) {
    v[i] = i + 1;
  }

  fisherYates(v, n);
  return v;
}

int main() {
  ArvoreRN *a = criarRN();
  int n = 1000;

  int *v = geraVetor(n);

  for (int i = 0; i < n; i++) {
    adicionarRN(a, v[i]);
  }

  printf("add\n");
  fisherYates(v, n);
  preOrderRN(a, a->raiz, visitar);
  printf("\n");

  for (int i = 0; i < n; i++) {
    removerRN(a, v[i]);
  }

  printf("Raiz: %d", a->raiz->valor);
  preOrderRN(a, a->raiz, visitar);
}
