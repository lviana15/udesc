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
  int i, n; 

  printf("Digite o valor de n:");
  scanf("%d", &n);

  for(i = 0;i <= n;i++) {
    vec[i] = 1 + rand() % 50;
  }

  for(i = 0;i < n;i++) {
    for(int j = 0;j < n - i - 1;j++) {
      if (vec[j] > vec[j+1]) swap(&vec[j], &vec[j+1]);
    }
  }

  for(i = 0;i < n;i++) {
    printf("%d\t", vec[i]);
  }
  
  return 0;
}
