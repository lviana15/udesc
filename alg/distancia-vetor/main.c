#include <stdio.h>
#include <stdlib.h>

int main () {
  int N, idx_N, distancia_N;
  int V[10] = {9, 10, 200, 5, 6, 4, 70, 80, 91, 100};

  scanf("%i", &N);

  for (int i = 0; i < 10; i++){
    if (V[i] == N) {
      idx_N = i;
      printf("%i", N);
      printf("\n");
      printf("Posicao %i", idx_N);
      printf("\n");
      break;
    } else {
      distancia_N = N - V[i];
      if (distancia_i == distancia_N) {
        printf("Mais proximo %i posicao %i")
      }
    } 
  }
} 
