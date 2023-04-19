#include <stdio.h>

int main () {
  int n, m, i, j, k, soma;
  printf("Digite o valor de N e M:");
  scanf("%d %d", &n ,&m);

  i=0;
  while (i < n) {
    j = 1;
    while (j <= m) {
      soma = 0;
      k = 1;
      while (k < j) {
        if (j % k == 0) soma = soma + k;
        k++;
      }

      if(j == soma) {
        printf("\n-> %d é perfeito\n", j);
        i++;
      }

      j++;
    }
  }

  return 0;
}
