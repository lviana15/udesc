#include <stdio.h>
#include <stdlib.h>

int main() {
    int x = 0, y;
    int stop = 0;

    while (stop == 0){
        y = 3 * (x * x) + 39 * x + 37;

        for (int i = 2; i < y/2; i++) {
            if (y % i == 0) {
                stop = 1;
                break;
            }
        }
        
        printf("(%i) %i ===> primo\n", x, y);
        x++;
    }
}
