#include <stdio.h>

void frente(int vet[], int * n, int i, int v){
  int condicao = 1, j = i;
  while (condicao) {
    if((j <= *n) && (v > 0)){
      vet[j] = vet[j] + v;
      j++;
      v--;
    } else {
      condicao = 0;
    }
  }
}

void tras(int vet[], int * n, int i, int v){
  int condicao = 1, j = i;
  while (condicao) {
    if((j >= 1) && (v > 0)){
      vet[j] = vet[j] + v;
      j--;
      v--;
    } else {
      condicao = 0;
    }
  }
}

void imprime(int vet[], int i){
  printf("%d\n", vet[i]);
}

void printa(int vet[], int n){
  int i = 1;
  while(i <= n){
    printf("[%d] ", vet[i]);
    i++;
  }
  printf("\n");
}

int main() {
  int vetor[200000];
  int continua = 1, comando, controle = 0, i, v, n, m;

  printf("Tamanho do vetor (N) e Quantidade de Instruções(M):\n");
  scanf("%d %d", &n, &m);
  
  while((controle < m) && (continua == 1)) {
    scanf("%d", &comando);

    switch (comando) {
      case 1:
        scanf ("%d %d", &i, &v);
        frente(vetor, &n, i, v);
        break;

      case 2:
        scanf ("%d %d", &i, &v);
        tras(vetor, &n, i, v);
        break;

      case 3:
        scanf ("%d", &i);
        imprime(vetor, i);
        break;

      case 4:
        continua = 0;
        break;

      default:
        printf("Entrada invalida");
        break;
    }

    controle++;
  }

  return 0;
}
