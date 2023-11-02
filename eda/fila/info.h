#ifndef INFO_H
#define INFO_H

typedef struct {
  char nome[30];
  char matricula[30];
  int ranking;
  char curso[30];
} info;

struct node {
  info dados;
  struct node *atras;
  struct node *defronte;
};

#endif // !INFO_H

