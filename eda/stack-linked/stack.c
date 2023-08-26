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

  newNode->data = value;
  newNode->next = stack->top;
  stack->top = newNode;
}

int isEmpty(Stack *stack) {
    if (stack->top == NULL) return 1;
    else return 0;
}

void peek(Stack *stack) {
    if (isEmpty(stack)) printf("Empty stack");
    else printf("[%d]", stack->top->data);
}

void printStack(Stack *stack) {
  while (stack->top != NULL) {
    printf("[%d] ", stack->top->data);
    stack->top = stack->top->next;
  }

  printf("\n");
}

void freeStack(Stack *stack) {
    while (stack->top != NULL) {
        Node *aux = stack->top;
        free(aux);
        stack->top = aux->next;
    }

    free(stack);
}

