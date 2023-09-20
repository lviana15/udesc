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
  stack->top = NULL;
  return stack;
}

void push(Stack *stack, int value) {
  Node *newNode = createNode(value);

  newNode->data = value;
  newNode->next = stack->top;
  stack->top = newNode;
}

void pop(Stack *stack) {
  if (!stack->top) {
    printf("Empty stack");
    return;
  }

  Node *aux = stack->top;
  stack->top = aux->next;
  free(aux);
}

void peek(Stack *stack) {
  if (isEmpty(stack))
    printf("Empty stack");
  else
    printf("[%d]", stack->top->data);
  printf("\n");
}

int size(Stack *stack) {
  int size = 0;
  Node *aux = stack->top;

  while (aux != NULL) {
    size++;
    aux = aux->next;
  }

  return size;
}

int isEmpty(Stack *stack) {
  if (stack->top == NULL)
    return 1;
  else
    return 0;
}

void printStack(Stack *stack) {
  Node *aux = stack->top;
  while (aux != NULL) {
    printf("[%d] ", aux->data);
    aux = aux->next;
  }

  printf("\n");
}

void freeStack(Stack *stack) {
  Node *aux = stack->top->next;
  while (aux != NULL) {
    free(stack->top);
    stack->top = aux;
    aux = aux->next;
  }

  free(stack->top);
  free(stack);
}
