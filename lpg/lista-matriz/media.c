#include <stdio.h>

void read_matrix(int n, int m, int matrix[n][m]) {
  int i, j;

  for(i = 0;i < n;i++) {
    for(j = 0;j < m;j++) scanf("%d", &matrix[i][j]);
  }
}


void print_matrix(int n, int m, int matrix[n][m]) {
  int i, j;

  printf("\n");
  for(i = 0;i < n;i++) {
    for(j = 0;j < m;j++) printf("%4d", matrix[i][j]);
    printf("\n");
  }
}

int main() {
  int i, j, n, m;
  float total, valores, media;

  printf("Digite valores para NxM (Ordem da Matriz): \n");
  scanf("%d %d", &n, &m);
  int matrix[n][m];

  printf("Digite valores da matriz:\n");
  read_matrix(n, m, matrix);

  for(i = 0;i < n;i++) {
    for(j = 0;j < m;j++) {
      if(matrix[i][j] > 0) {
        total = total + matrix[i][j];
        valores = valores + 1;
      }
    }
  }

  media = total / valores;
  print_matrix(n, m, matrix);

  printf("\nMedia dos valores positivos: %.2f", media);

  return 0;
}
