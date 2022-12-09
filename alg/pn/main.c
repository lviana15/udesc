#include <stdio.h>
#include <stdlib.h>

float produto_notavel(int a, int b);
int main() {
    int a, b;
    
    scanf("%i %i", &a, &b);

    printf("%.2f", produto_notavel(a, b));
}

float produto_notavel(int a, int b){
    float pn;
    pn = (a * a) + (2 * a * b) + (b * b);

    return pn;
}