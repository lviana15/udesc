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
  char *tags[] = {"!DOCTYPE", "input", "frame", "option", "img", "br", "hr"};
  for (int i = 0; i < sizeof(tags); i++) {
    if (strcmp(str, tags[i])) {
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

    char *end = strpbrk(tag, " >");
    if (end != NULL)
      *end = '\0';

    if (startsWith(tag, "/")) {

    }
  }

  return 0;
}
