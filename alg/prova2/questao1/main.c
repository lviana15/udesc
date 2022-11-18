#include <stdio.h>
#include <stdlib.h>

int main () {
    float levantamento[10] = {200, 500, 50, 30, 1000, 200, 600, 350, 1000, 2000};
    float loja1[10] = {150, 490, 50, 3, 900, 180, 550, 300, 750, 1800};
    float loja2[10] = {100, 290, 25, 10, 1000, 280, 500, 200, 550, 2100};
    float desconto_loja1, desconto_loja2;

    for (int i = 0; i < 10; i++) {
        printf("\n");
        printf("Produto %i\n", i);
        desconto_loja1 = (loja1[i] / levantamento[i]) * 100;
        desconto_loja2 = (loja2[i] / levantamento[i]) * 100;
        if (desconto_loja1 < 100)
            printf ("Loja 1: Baixou %.2f%%\n", desconto_loja1);
        else if (desconto_loja1 > 100) 
            printf ("Loja 1: Subiu %.2f%%", desconto_loja1);
        else 
            printf ("Loja 1: Mesmo preço.\n");

        if (desconto_loja2 < 100)
            printf ("Loja 2: Baixou %.2f%%\n", desconto_loja2);
        else if (desconto_loja2 > 100) 
            printf ("Loja 2: Subiu %.2f%%\n", desconto_loja2);
        else 
            printf ("Loja 2: Mesmo preço.\n");
    }
}