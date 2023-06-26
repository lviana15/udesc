#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void preenche_vetor(int v[],int n){
  srand(time(NULL));
  for(int i = 0;i < n;i++){
    v[i] = 1 + rand()%20;
  }
}

int *busca(int v[], int n, int chave){
  int *indices;
  int count = 0;
  for(int i = 0;i < n;i++) {
    if (v[i] == chave) {
      count ++;
      indices = realloc(indices, sizeof(int) * count);
      indices[count-1] = i;
    }
  }

  return indices;
};

int main() {
  int n, chave;
  int *vetor, *buscados;
  
  printf("Digite tamanho do vetor:\n");
  scanf("%d", &n);

  vetor = malloc(sizeof(int) * n);
  buscados = malloc(sizeof(int) * n);
  preenche_vetor(vetor, n);

  printf("Digite o valor a ser buscado:\n");
  scanf("%d", &chave);
  buscados = busca(vetor, n, chave);

  for(int i = 0;i < n;i++) {
    printf("%d ", vetor[i]);
  }

  for(int i = 0;i < n;i++)
    printf("%d ", buscados[i]);

  free(vetor);
  free(buscados);

  return 0;
}
