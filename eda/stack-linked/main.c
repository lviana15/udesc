#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main (void) {
    Stack *stack = createStack();

    isEmpty(stack);

    push(stack, 5);
    push(stack, 10);
    peek(stack);

    push(stack, 7);
    push(stack, 21);

    printf("Stack size: %d\n", size(stack));

    printStack(stack);

    freeStack(stack);

    return 0;
}
