#include <stdio.h>

int verifiy_prime(int n) {
  int i, primo;

  for(i = 2; i <= n; i++){
    if (i != n && n % i == 0) {
      primo = 0;
      break;
    } else {
      primo = 1;
    }
  }
  return primo;
}

int main() {
  int n, i, j, count;
  
  printf("Digite o valor de N:\n");
  scanf("%i", &n);

  if (verifiy_prime(n))
    printf("%i é um número primo\n\n", n);
  else 
    printf("%i não é um número primo\n\n", n);

  printf("Números primos até %i:\n\n", n);
  for(int i = 2; i < n; i++) {
    if (verifiy_prime(i)){
      printf("%i\t", i); 
      count++;
    }
  }

  printf("\nTotal de números primos: %i\n", count);
  printf("\nRelação dos %i primeiros números primos:\n", n);

  i = n;
  j = 1;
  
  while (i >= 1) {
    while (1){
      if (verifiy_prime(j)) {
        printf("%i\t", j);
        j++;
        break;
      }
      j++;
    }

    i--;
  }

  return 0;
}

