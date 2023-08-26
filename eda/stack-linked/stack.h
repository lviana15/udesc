#ifndef STACK_H
#define STACK_H

typedef struct Node {
  int data;
  struct Node *next;
} Node;

typedef struct Stack {
  struct Node *top;
} Stack;

Stack* createStack();
Node* createNode(int value);
void push(Stack *stack, int value);
void pop(Stack *stack);
void peek(Stack *stack);
int size(Stack *stack);
int isEmpty(Stack *stack);
void freeStack(Stack *stack);
void printStack(Stack *stack);

#endif // !"stack.h"
