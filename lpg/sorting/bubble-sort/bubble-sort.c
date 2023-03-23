#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b);

void swap(int *a, int *b) {
  int buff = *a;
  *a = *b;
  *b = buff;
}

int main() {
  srand(time(NULL));

  int vec[100];
  int i, n, count, cound, ordered;

  printf("Digite o valor de n:");
  scanf("%d", &n);

  for(i = 0;i <= n;i++) {
    vec[i] = 1 + rand() % 50;
  }

  for(i = 0;i < n;i++) {
    ordered = 0;
    for(int j = 0;j < n - i - 1;j++) {
      if (vec[j] > vec[j+1]) {
        swap(&vec[j], &vec[j+1]);
        ordered = 1;
        count++;
      }
      cound++;
    }
    if (ordered == 0) break;
  }

  for(i = 0;i < n;i++) {
    printf("%d\t", vec[i]);
  }

  printf("\nContagem de verificações: %d", count);
  printf("\nContagem: %d", cound);
  
  return 0;
}
