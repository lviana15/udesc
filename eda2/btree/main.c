#include "arvoreb.h"
#include <stdio.h>
#include <stdlib.h>
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
  ArvoreB *ordem1 = criaArvoreB(1);
  // int n = 100;
  // int *v = geraVetor(n);

  // for (int i = 0; i < n; i++) {
  //   adicionaChaveB(ordem1, v[i]);
  // }

  // printf("add\n");
  // fisherYates(v, n);
  // for (int i = 0; i < n; i++) {
  //   printf("%d ", v[i]);
  // }

  // // inOrderB(ordem1->raiz);
  // printf("\n");

  // for (int i = 0; i < n; i++) {
  //   removerChaveB(ordem1, v[i]);
  // }

  // printf("arvor\n");
  // inOrderB(ordem1->raiz);
  adicionaChaveB(ordem1, 2);
  adicionaChaveB(ordem1, 12);
  adicionaChaveB(ordem1, 5);
  adicionaChaveB(ordem1, 7);
  adicionaChaveB(ordem1, 4);
  adicionaChaveB(ordem1, 6);

  inOrderB(ordem1->raiz);
}
