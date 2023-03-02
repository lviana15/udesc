#include<stdio.h>

int main() {
  int a, b, c;
  printf("Digite tres valores:\n");
  scanf("%i %i %i", &a, &b, &c);
  if ((a + b) > c && (b + c) > a && (a + c) > b) {
    if (a == b && b == c) {
      printf("Triangulo equilatero\n");
    } else if (a != b && b != c && a != c){
      printf("Triangulo escaleno\n");
    } else {
      printf("Triangulo isoceles\n");
    }
  } else {
    printf("Não é triangulo\n");
  }

  return 0;
}
