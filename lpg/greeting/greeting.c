#include <stdio.h>

int main() {
  char nome[250];
  char sexo;

  printf("Digite seu nome e sexo (H/M):\n");
  scanf("%s %c", nome, &sexo);

  if (sexo == 'H') {
    printf("Ilmo. Sr. %s\n", nome);
  } else  if (sexo == 'M'){
    printf("Ilma. Sra. %s\n", nome);
  } else {
    printf("Entrada invalida\n");
  }
  
  
  return 0;
}
