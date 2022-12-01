#include <stdio.h>
#include <stdlib.h>

int main () {
  int N, distancia_N, menor_distancia;
  int V[10] = {9, 10, 200, 5, 6, 4, 70, 80, 91, 100};

  scanf("%i", &N);
  menor_distancia = N - V[0];

  for (int i = 0; i < 10; i++){
    if (N < V[i])
      distancia_N = V[i] - N;
    else
      distancia_N = N - V[i];

    if (V[i] == N) {
      printf("%i", N);
      printf("\n");
      printf("Posicao %i", i);
      printf("\n");
      break;
    } else {
      if (distancia_N < menor_distancia)
        menor_distancia = distancia_N;
    } 
  }

  for (int k = 0; k < 10; k++) {
    if (N > V[k]){
      if (N - V[k] == menor_distancia){
        printf("Mais proximo %i posicao %i", V[k], k);
        printf("\n");
      }
    } else {
      if (V[k] - N == menor_distancia){
        printf("Mais proximo %i posicao %i", V[k], k);    
        printf("\n");
      }
    }
  } 
}
