#include <stdio.h>
#include <stdlib.h>
#include <time.h>
  
void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
  
void bubbleSort(int arr[], int n, int cound) {
  if (n == 1) return;

  int count = 0;
  for (int i=0; i<n-1; i++)
    if (arr[i] > arr[i+1]) {
      swap(&arr[i], &arr[i+1]);
      count++;
      cound++;
    }

  if (count==0) return;

  bubbleSort(arr, n-1, cound);
}


int main() {
  srand(time(NULL));

  int vec[100];
  int i, n, cound;

  printf("Digite o valor de n:");
  scanf("%d", &n);

  for(i = 0;i <= n;i++) {
    vec[i] = 1 + rand() % 50;
  }

  bubbleSort(vec, n, cound);

  for(i = 0;i < n;i++) {
    printf("%d\t", vec[i]);
  }

  printf("\nContagem: %d", cound);
}
