#include <stdio.h>

int sequential(int arr[], int n);

int main() {
  int vector[10] = {2, 8, -3, 6, 12, -8, 16, -11, 7, 10};
  int i, posicao = -1, n;

  scanf("%d", &n);

  for(i = 0;i < 10;i++){
    if(vector[i] == n)
      posicao = i;
  }

  if(posicao == -1)
    printf("Valor não encontrado");
  else 
    printf("Valor na posicao: %d", posicao+1 );
  
  return 0;
}
