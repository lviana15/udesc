#include <stdio.h>

int main(int argc, char *argv[]) {
  int v[4] = {10, 15, 3, 7};
  int s[4];
  int n = 4, k = 17, count = 0;

  for (int i = 0; i < n; i++) {
    s[i] = k - v[i];
    count++;
  }

  for (int i = 0; i < n; i++) {
    count++;
    if (v[i] + s[i] == k) {
      printf("True\n");
      break;
    }
  }

  printf("%d\n", count);

  return 0;
}
