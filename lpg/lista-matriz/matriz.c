#include <stdio.h>

void read_matrix(int n, int m, int matrix[n][m]) {
  int i, j;
    for(i = 0;i < n;i++) {
      for(j = 0;j < m;j++) {
        scanf("%d", &matrix[i][j]);
      }
  }
}


void print_matrix(int n, int m, int matrix[n][m]) {
  int i, j;

  printf("\n");
  for(i = 0;i < n;i++) {
    for(j = 0;j < m;j++) {
      printf("%4d", matrix[i][j]);
    }
    printf("\n");
  }
}

void update_matrix(int n, int m, int matrix[n][m], int i, int j, int x) {
  matrix[i][j] = x;
}

int main() {
  int matrix[50][50];
  int n, m;

  printf("Digite valores para NxM (Ordem da matriz):\n");
  scanf("%d %d", &n, &m);

  printf("Digite valores para matriz %dx%d: \n", n, m);
  read_matrix(n, m, matrix);

  print_matrix(n, m, matrix);
  update_matrix(n, m, matrix, 0, 0, 10);
  print_matrix(n, m, matrix);

  return 0;
}
