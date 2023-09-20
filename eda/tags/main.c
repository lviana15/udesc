#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int startsWith(const char *str, char *target) {
  if (str[0] == *target) {
    return 1;
  }

  return 0;
}

int hasEndingTag(const char *str) {
  const char *tags[] = {"!DOCTYPE", "input", "frame", "option",
                        "img",      "br",    "hr"};

  for (int i = 0; i < sizeof(tags) / sizeof(tags[0]); i++) {
    if (strcmp(str, tags[i]) == 0) {
      return 0;
    };
  }

  return 1;
}

int main(int argc, char *argv[]) {
  Stack *stack;
  char lines[1000];
  char *tag;

  stack = createStack();
  FILE *fp = fopen(argv[1], "r");

  if ((fp = fopen(argv[1], "r")) == NULL) {
    printf("Usage: %s [filename]\n", argv[0]);
    return 1;
  }

  int count = 1;
  char log[100] = "";
  while (fgets(lines, sizeof(lines), fp)) {

    // Adquire primeira tag e roda enquanto houver proximas tags
    tag = strtok(lines, "<");
    while (tag) {

      // "Corta" string para ter apenas a tag Html
      char *end = strpbrk(tag, " >");
      if (end != NULL)
        *end = '\0';

      // Verifica se é tag de fechamento
      if (startsWith(tag, "/")) {
        // Remover "/" para comparar com topo da pilha
        tag++;

        // Compara a tag de fechamento atual com topo da pilha e desempilha caso
        // TRUE
        if (strcmp(tag, stack->top->data) == 0) {
          pop(stack);
        } else {
          strcat(log, "ERRO\n");
        }

        // Verifica se é tag e empilha
      } else if ((hasEndingTag(tag)) && (strlen(tag) > 0)) {
        push(stack, tag);
      }

      // Passa para proxima linha (tag)
      tag = strtok(NULL, "<");
    }
    count++;
  }

  if (!isEmpty(stack)) {
    strcat(log, "ERRO\n");
  }

  free(stack);
  printf("%s", log);

  return 0;
}
