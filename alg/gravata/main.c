#include <stdio.h>

int main() {
  int matriz[12][12];
  int maior;

  for(int i = 0; i < 12; i++){
    for(int j = 0; j < 12; j++){
      scanf("%i", &matriz[i][j]);
    }
  }
  
  for(int i = 0; i < 12; i++){
    printf("\n");
    for (int j = 0; j < 12; j++){
      int soma = i + j, diferença = i - j;
      printf("%i\t", matriz[i][j]);
      if (((diferença > 0) && (soma < 11)) || ((diferença < 0) && (soma > 11)) || i == j || soma == 11) {
        if (matriz[i][j] > maior) {
          maior = matriz[i][j];
        }
      }
    }
  }

  printf("\nMaior elemento:%i", maior);
}
