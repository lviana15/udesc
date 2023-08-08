#ifndef STACK_H
#define STACK_H

typedef struct {
    int top;
    int *items;
    int size;
} Stack;

Stack* createStack(int capacity);
void push(Stack *stack, int value);
void pop(Stack *stack);
int isEmpty(Stack *stack);
void printStack(Stack *stack);

#endif

