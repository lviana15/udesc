#ifndef STACK_H
#define STACK_H

typedef struct Node {
  char *data;
  struct Node *next;
} Node;

typedef struct Stack {
  struct Node *top;
} Stack;

Stack *createStack();
Node *createNode(char *tag);
void push(Stack *stack, char *value);
void pop(Stack *stack);
char *peek(Stack *stack);
int size(Stack *stack);
int isEmpty(Stack *stack);
void freeStack(Stack *stack);
void printStack(Stack *stack);

#endif // !"stack.h"
