#include <stdio.h>
#include <stdlib.h>

int main () {
  int v[10];

  for(int i = 0; i < 10; i++)
    scanf("%i", &v[i]);
  
  for(int j = 0; j < 10; j++) {
    int count = 0;
    for(int k = j; k < 10; k++) {
      if (v[j] == v[k]) {
        count++;
      }
    }

    if (count > 1) {
      printf("\n");
      printf("%i: %i vezes", v[j], count);
    }
  }
}
