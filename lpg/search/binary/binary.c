#include <stdio.h>

int binary_search(int arr[], int n) {
  int left = 0, right = 9, mid;

  while (left <= right) {
    mid = (right + left) /2;

    if(n == arr[mid])
      return mid;

    if (n > arr[mid])
      left = mid + 1;
    else
      right = mid - 1;
  }

  return -1;
}

int main() {
  int vector[10] = {2, 4, 5, 8, 11, 17, 32, 44, 60, 81};
  int n, posicao;

  printf("Valor a ser buscado:");
  scanf("%d", &n);
  
  posicao = binary_search(vector, n);

  if(posicao == -1)
    printf("Valor não encontrado");
  else
    printf("Valor na posicao: %d", posicao+1);

  return 0;
}
