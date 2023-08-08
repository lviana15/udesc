#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main() {
  Stack *stack = createStack(5);
  push(stack, 2);
  push(stack, 8);
  push(stack, 3);
  push(stack, 12);
  push(stack, 23);

  printStack(stack);

  free(stack->items);
  free(stack);
  return 0;
}
