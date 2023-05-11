#include <stdio.h>

//Preenche matriz com valores de acordo com a posição
void read_matrix(int n, int m, int matrix[n][m]) {
  int i, j, value;

  for(i = 0;i < n;i++) {
    for(j = 0;j < m;j++) {
      value = i + j;
      matrix[i][j] = value;
    }
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
  int matrix[50][50];
  int n, m;

  printf("Digite valores para NxM (Ordem da Matriz):\n");
  scanf("%d %d", &n, &m);

  read_matrix(n, m, matrix);
  print_matrix(n, m, matrix);

  return 0;
}
