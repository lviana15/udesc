#include <stdio.h>

void swap(int *a, int *b);

void swap(int *a, int *b) {
  int buff = *a;
  *a = *b;
  *b = buff;
}

int main() {
  int vec[10] = { 7,3,6,2,8,10,1,4,5,9 };
  int i;

  for(i = 0;i < 10;i++) {
    printf("%d\t", vec[i]);
  }
  printf("\n\n");

  for(i = 0;i < 10;i++) {
    for(int j = 0;j < 10 - i - 1;j++) {
      if (vec[j] > vec[j+1]) swap(&vec[j], &vec[j+1]);
    }
  }

  for(i = 0;i < 10;i++) {
    printf("%d\t", vec[i]);
  }
  
  return 0;
}
