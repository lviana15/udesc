#include <stdio.h>

int main() {
    int vetor [100];
    int i, n, positivos = 0, negativos = 0, soma = 0;

    printf("Digite o valor de N: ");
    scanf("%d", &n);

    for (i = 0;i < n;i++) scanf("%d", &vetor[i]);

    for (i = 0;i < n;i++) {
        if (vetor[i] >= 0) positivos++;
        else negativos++;

        soma = soma + vetor[i];
    }

    if (positivos <= 1) printf("%d valor é positivo, e ", positivos);
    else printf ("%d valores são positivos, e ", positivos);

    if (negativos <= 1) printf("%d valor é negativo. ", negativos);
    else printf ("%d valores são negativos. ", negativos);

    printf("Soma: %d", soma);

    printf("\n");

    return 0;
}
