#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int stringComecaChar(const char *str, char *target) {
  if (str[0] == *target) {
    return 1;
  }

  return 0;
}

int main(int argc, char *argv[]) {
  // FILE *fp;
  char line[1000] = "<html> Hello World \n </head>";
  char *tag;

  // if ((fp=fopen(argv[1], "w")) == NULL) {
  //     printf("Arquivo não encontrado\n");
  // } else {
  //    printf("Arquivo aberto\n");
  // }

  // while(fgets(line, sizeof(line), fp)){
  //     tag = strtok(line,"<");

  // }
  tag = strtok(line, "<>");
  while (tag) {
    if (stringComecaChar(tag, "/"))
      printf("%s\n", tag);
    tag = strtok(NULL, "<>");
  }

  return 0;
}
