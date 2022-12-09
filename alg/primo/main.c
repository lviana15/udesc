#include <stdio.h>

int primo(int x);

int main() {
    int N;
    
    scanf("%i", &N);

    for(int i = N - 1; i >= 2; i--){
        if (primo(i) == 1){
            printf("%i", i);
            return 0;
        }
    }

    printf("Não tem primos anteriores");
    return 0;
}

int primo(int x) {
    for (int i = 2; i < x-1; i++)
        if ((x % i == 0)){
            return 0;
            break;
        }

    return 1;
}