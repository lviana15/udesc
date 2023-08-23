#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

Node *createNode(int value) {
  Node *newNode = malloc(sizeof(Node));
  newNode->data = value;
  newNode->next = NULL;

  return newNode;
}

Stack *createStack() {
  Stack *stack = malloc(sizeof(Stack));
  return stack;
}

void push(Stack *stack, int value) {
  Node *newNode = createNode(value);

  if (stack->top != NULL) {
    stack->top = newNode;
  } else {
    newNode->next = stack->top;
    stack->top = newNode;
  }
}
