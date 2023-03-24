#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  srand(time(NULL));

  int vec[100];
  int i, j, n, head, count;

  printf("Digite o valor de n:");
  scanf("%d", &n);

  for(i = 0;i < n;i++) vec[i] = 1 + rand() % 50;

  for(i = 1;i < n;i++) {
    head = vec[i];

    j = i-1;
    while (head < vec[j]) {
      count++;
      vec[j+1] = vec[j];
      j--;
    }
    vec[j+1] = head;
  }

  for(i = 0;i < n;i++) printf("%d\t", vec[i]);
  printf("\nContagem alocações: %d", count);

  return 0;
}
