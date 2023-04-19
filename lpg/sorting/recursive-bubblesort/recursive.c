#include <stdio.h>
#include <stdlib.h>
#include <time.h>
  
void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
  
int bubbleSort(int arr[], int n) {
  if (n == 1) return 1;

  int count = 0;
  for (int i=0; i<n-1; i++) {
    if (arr[i] > arr[i+1]) {
      swap(&arr[i], &arr[i+1]);
      count++;
    }
    // printf("\n%d", *complex);
  }

  if (count==0) return 1;

  bubbleSort(arr, n-1);
}


int main() {
  srand(time(NULL));

  int vec[100];
  int i, n, complex = 0;

  printf("Digite o valor de n:");
  scanf("%d", &n);

  for(i = 0;i <= n;i++) {
    vec[i] = 1 + rand() % 50;
  }

  bubbleSort(vec, n);

  for(i = 0;i < n;i++) {
    printf("%d\t", vec[i]);
  }

  printf("\nComplex: %d", complex);

}
