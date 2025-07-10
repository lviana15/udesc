#include "lib.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  int v[] = {1, 2, 3, 4, 5};
  int n = sizeof(v) / sizeof(v[0]), count = 0, prod = 1;

  // for (int i = 0; i < n; i++) {
  //   int prod = 1;

  //  for (int j = 0; j < n; j++) {
  //    if (i != j)
  //      prod *= v[j];
  //  }

  //  p[i] = prod;
  //}

  printVec(v, n);
  for (int i = 0; i < n; i++) {
    prod *= v[i];
  }

  for (int i = 0; i < n; i++) {
    v[i] = prod / v[i];
  }

  printVec(v, n);

  printf("%d", count);

  return 0;
}
