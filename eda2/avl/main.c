#include "arvoreAVL.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc <= 1)
    return 1;
  int insert = 0, remove = 0, contador = atoi(argv[1]);
  ArvoreAVL *a = criarAVL();

  for (int i = 0; i < contador; i++) {
    insert = adicionarAVL(a, i);
  }

  printf("\n");
  preOrderAVL(a->raiz, visitarAVL);
  printf("\n");

  remove += removerAVL(a, 4);
  remove += removerAVL(a, 1);
  remove += removerAVL(a, 7);
  remove += removerAVL(a, 9);
  remove += removerAVL(a, 2);
  remove += removerAVL(a, 6);
  remove += removerAVL(a, 8);
  remove += removerAVL(a, 3);
  remove += removerAVL(a, 5);

  preOrderAVL(a->raiz, visitarAVL);
  printf("\n");

  printf("Insertion: %d\n", insert);
  printf("Remove: %d\n", remove);
}
