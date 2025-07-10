#include "lib.h"
#include <stdio.h>
#include <stdlib.h>

// Starts a new Dynamic Array
Vector *new_vector() {
  Vector *vec = malloc(sizeof(Vector));
  if (vec != NULL) {
    vec->array = NULL;
    vec->size = 0;
  }

  return vec;
}

// Push new element to [vec]
void add(Vector *vec, int n) {
  if (vec != NULL) {
    vec->array = realloc(vec->array, (vec->size + 1) * sizeof(int));

    if (vec->array != NULL) {
      vec->array[vec->size] = n;
      vec->size++;
    }
  }
}

// Change element [idx] to [n] on [vec]
void change(Vector *vec, int idx, int n) {
  if (vec != NULL && idx < vec->size) {
    vec->array[idx] = n;
  }
}

void empty(Vector *vec) {
  if (vec != NULL) {
    free(vec->array);
    vec->array = NULL;
    vec->size = 0;
  }
}

void free_vector(Vector *vec) {
  if (vec != NULL) {
    free(vec->array);
    free(vec);
  }
}

// Return min non-locked element idx on Record [arr] of [size]
//
// If all elements are locked returns -1
int get_key(Record *arr, int size) {
  int idx = -1;
  for (int i = 0; i < size; i++) {
    if ((arr[i].data <= arr[idx].data) && (arr[i].locked == 0)) {
      idx = i;
    }
  }

  return idx;
}

void print_arr(int *arr, int size) {
  printf("[ ");
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("]\n");
}

void print_vec(Vector *vec) {
  printf("[ ");
  for (int i = 0; i < vec->size; i++) {
    printf("%d ", vec->array[i]);
  }
  printf("]\n");
}

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void insertion_sort(int *arr, int size) {
  int i = 1;
  while (i < size) {
    int j = i;
    while ((j > 0) && (arr[j - 1] > arr[j])) {
      swap(&arr[j], &arr[j - 1]);
      j--;
    }

    i++;
  }
}

Vector *substitution(int archive[], int M) {
  int min, count = 0;
  Record memory[M];
  Vector *partitions[10];
  int *next;

  // 1- Le primeiros M registros do arquivo
  for (int i = 0; i < M; i++) {
    memory[i].data = archive[i];
    memory[i].locked = 0;
  }

  next = &archive[M];

  // Iterates over [archive] moving pointer to [next] element
  while (*next && count < 10) {
    Vector *partition = new_vector();
    int flag = 0;

    for (int i = 0; i < M; i++) {
      memory[i].locked = 0;
    }

    while (*next && flag == 0) {
      // 2- Seleciona o menor registro
      min = get_key(memory, M);

      if (min == -1) {
        partitions[count++] = partition;
        flag = 1;
      } else {
        add(partition, memory[min].data);

        if (*next < memory[min].data) {
          memory[min].locked = 1;
        }
        memory[min].data = *next;

        next++;
      }
    }

    print_vec(partition);
    empty(partition);

    if (flag == 0 && memory[min].locked == 0) {
      next++;
    }

    free_vector(partition);
  }

  return *partitions;
}
