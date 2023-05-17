#include <stdio.h>

int fatorial(int n) {
    int fat = 1;
    while (n > 1) {
        fat = fat * n;
        n--;
    }

    return fat;
}

int main() {
    int vetor[100];
    int i, tamanho, valor, n1 = 0, n2;

    while (n1 < 1) {
        printf("Digite um valor inteiro positivo para N1:\n");
        scanf("%d", &n1);        
    }
    while (n2 <= n1) {
        printf("Digite um valor inteiro positivo maior que N1 para N2:\n");
        scanf("%d", &n2);
    }

    //tamanho do vetor
    tamanho = n2 - n1 + 1;

    //contador para cada valor do intervalo
    valor = n1;

    //preenchendo vetor com valores do intervalo
    for (i = 0; i < tamanho; i++){
        vetor[i] = valor;
        valor++;
    }

    for (i = 0; i < tamanho; i++) printf("%d ", fatorial(vetor[i]));

    printf("\n");

    return 0;
}
