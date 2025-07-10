#include <stdio.h>

void printVec(int *v, int n) {
    printf("[ ");

    for (int i = 0;i< n; i++) {
        printf("%d ", v[i]);
    }

    printf("]\n");
}
