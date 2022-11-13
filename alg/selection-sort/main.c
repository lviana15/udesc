#include <stdio.h>

int main() {
  int v[10] = {7, 12, 10, 8, 5, 19, 3, 90, 11, 15};

  for(int i = 0; i < 10; i++){
    int idx_menor = i;
    for (int j = i;j < 10; j++) {
      if (v[j] < v[idx_menor])
        idx_menor = j;
    }

    int aux = v[i];
    v[i] = v[idx_menor];
    v[idx_menor] = aux;
  }

  for(int i = 0; i < 10; i++)
    printf("%d \n", v[i]);
}
