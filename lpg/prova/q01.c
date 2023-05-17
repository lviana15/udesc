#include <stdio.h>

void divisivel(int a) {
    if (a % 4 == 0) printf("[%d] ", a);
    else printf("%d ", a);
}

int main() {
  int n = 0;

    while (n <= 0) {
        printf("Digite um valor maior que 0 para N:\n");
        scanf("%d", &n);
    }

    while(n >= 1) {
        divisivel(n);
        n--;
    }

    printf("\n");

    return 0;
}
