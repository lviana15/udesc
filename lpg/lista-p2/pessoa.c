#include <stdio.h>
#include <stdlib.h>

struct data {
  int dia;
  int mes;
  int ano;
};

struct pessoa{
  char nome[20];
  struct data *nascimento;
  char cpf[11];
};

void le_data(struct data *d) {
  scanf("%d", &d->dia);
  scanf("%d", &d->mes);
  scanf("%d", &d->ano);
}

void le_pessoa(struct pessoa *p) {
  p->nascimento = malloc(sizeof(struct data));
  scanf("%s", p->nome);
  le_data(p->nascimento);
  scanf("%s", p->cpf);
};

void printa_data(struct data *d) {
  printf("%d/%d/%d\n", d->dia, d->mes, d->ano);
};

void printa_pessoa(struct pessoa *p) {
  printf("%s\n", p->nome);
  printa_data(p->nascimento);
  printf("%s\n", p->cpf);
};

int main() {
  struct pessoa *aluno = malloc(sizeof(struct pessoa));
  le_pessoa(aluno);
  printa_pessoa(aluno);
  free(aluno->nascimento);
  free(aluno);

  return 0;
}
