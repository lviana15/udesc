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
  char lines[1000];
  char *tag;

  FILE *fp = fopen(argv[1], "r");

  while (fgets(lines, sizeof(lines), fp)) {
    tag = strtok(lines, "<");

    while (tag) {
      char *end = strpbrk(tag, " >");
      if (end != NULL)
        *end = '\0';

      if (startsWith(tag, "/")) {
        printf("End tag: %s\n", tag);
        // pop(stack)
      } else if ((hasEndingTag(tag)) && (strlen(tag) > 0)) {
        printf("%s\n", tag);
        // push(tag, stack)
      }

      tag = strtok(NULL, "<");
    }
  }

  return 0;
}
