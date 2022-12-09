#include <stdio.h>

int parCollatz(int x);
int imparCollatz(int x);

int main (){
    int N, maior, count;

    scanf("%i", &N);
    maior = N;

    while (N != 1) {
        if (N % 2 == 0) 
            N = parCollatz(N);
        else 
            N = imparCollatz(N);
        if (N > maior) 
            maior = N;

        count++;
    }
    printf("\n %i", count);
    printf("\n %i", maior);
}

int parCollatz(int x) {
    return x / 2;
}

int imparCollatz(int x) {
    return 3 * x + 1;
}