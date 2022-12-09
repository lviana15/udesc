#include <stdio.h>

int soma(int a, int b);

int main() {
    int a, b;
    
    scanf("%i %i", &a, &b);

    if (a > 0 && b > 0){ 
        soma(a, b);
        printf("%i", soma(a, b));
    }
}

int soma(int a, int b) {
    int sum;

    sum = a + b;

    return sum;
}