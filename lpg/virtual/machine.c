#include <stdio.h>

void frente(int vet[], int n, int i, int v){
  int condicao = 1, j = i;
  while (condicao) {
    if((j <= n) && (v > 0)){
      vet[j] = vet[j] + v;
      j++;
      v--;
    } else {
      condicao = 0;
    }
  }
}

void tras(int vet[], int n, int i, int v){
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

void imprime(int vet[], int n, int i){
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
  int comando, i, v, n, m;

  printf("Tamanho do vetor (N) e Quantidade de Instruções(M):\n");
  scanf("%d %d", &n, &m);
  
  /*
  frente(vetor, n, 4, 8);
  tras(vetor, n, 16, 3);
  tras(vetor, n, 2, 12);
  frente(vetor, n, 8, 7);
  printa(vetor, n);
  */

  while(m >= 1) {
    scanf("%d %d %d", &comando, &i, &v);

    switch (comando) {
      case 1:
        frente(vetor, n, i, v);
        break;
      case 2:
        tras(vetor, n, i, v);
        break;
      case 3:
        imprime(vetor, n, i);
        break;
      case 4:
        return 0;
        break;
      default:
        printf("Entrada invalida");
        break;
      }

    m--;
  }

  printa(vetor, n);

  return 0;
}
