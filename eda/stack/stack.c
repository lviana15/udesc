#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

Stack *createStack(int capacity) {
  Stack *stack = malloc(sizeof(Stack));
  stack->top = -1;
  stack->items = malloc(sizeof(int) * capacity);
  stack->size = capacity;
  return stack;
};

void push(Stack *stack, int value) {
  if(stack->size == stack->top + 1) return;
  stack->top++;
  stack->items[stack->top] = value;
};

void printStack(Stack *stack) {
  for (int i = 0; i <= stack->top; i++)
    printf("[%d] ", stack->items[i]);
}
