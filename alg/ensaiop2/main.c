#include <stdio.h>
#include <math.h>
#define PI 3.14

int main() {
  int opc;
  double a, b, c, p, raio, A_circulo, A_triangulo, A_retangulo, A_quadrado;

  while (opc != -1){

    printf("\nEscolha a figura que deseja: \n");
    printf("1 - Circulo\n");
    printf("2 - Triangulo\n");
    printf("3 - Retangulo\n");
    printf("4 - Quadrado\n");
    printf("-1 - Parar\n");

    scanf("%i", &opc);
    printf("\n");

    switch(opc) {
      case -1:
      break;

      case 1:
        printf("Digite o raio do circulo\n");
        scanf("%lf", &raio);
        A_circulo = PI * pow(raio, 2);

        printf("Area do circulo: %.2lf\n", A_circulo);
        break;

      case 2:
        printf("Digite os lados do triangulo\n");
        scanf("%lf %lf %lf", &a, &b, &c);

        p = (a + b + c) / 2;
        A_triangulo = sqrt(p * (p - a) * (p - b) * (p - c));

        printf("Area do triangulo: %.2lf\n", A_triangulo);
        break;

      case 3:
        printf("Digite os lados do retangulo:\n");
        scanf("%lf %lf", &a, &b);
        A_retangulo = (a * b);

        printf("Area do retangulo: %.2lf\n", A_retangulo);
        break;

      case 4:
        printf("Digite o lado do quadrado:\n");
        scanf("%lf", &a);
        A_quadrado = pow (a, 2);

        printf("Area do quadrado: %.2lf\n", A_quadrado);
        break;
        default:
        printf("Opcao invalida!\n");
    }
  }
}
