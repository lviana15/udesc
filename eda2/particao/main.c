#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
  int archive[] = {30, 14, 15, 75, 32, 6,  5,  81, 48, 41, 87, 18,
                   56, 20, 26, 4,  21, 65, 22, 49, 11, 16, 8,  12,
                   44, 9,  7,  81, 23, 19, 1,  78, 13, 16, 51, 8};

  // if (argc < 2) {
  //   printf("Correct usage:\n");
  //   printf("%s [array size]", argv[0]);
  // }

  // srand(time(NULL));
  // int M = 7;
  // int arr[M];

  // for (int i = 0; i < M; i++) {
  //   arr[i] = rand() % 100 + 1;
  // }

  // print_arr(arr, M);
  // insertion_sort(arr, M);
  // print_arr(arr, M);

  substitution(archive, 7);

  return 0;
}
