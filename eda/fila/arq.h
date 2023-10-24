#define LIVRE 0
#define OCUPADA 1
#define FRACASSO 0
#define SUCESSO 1
#define FALSO 0
#define VERDADEIRO 1
#define NAO 0
#define SIM 1
#define MAIOR 1
#define IGUAL 0
#define MENOR -1
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define debugging 1

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

struct queue {
  struct node *frente;
  struct node *cauda;
  int tamInfo;
};

//======================APLICACAO=====================

//======================FILA=====================
struct queue *cria(int tamInfo);
int insere(info *novo, struct queue *p);
int tamanhoDaFila(struct queue *p);
int reinicia(struct queue *p);
struct queue *destroi(struct queue *p);
int buscaNaCauda(info *reg, struct queue *p);
int buscaNaFrente(info *reg, struct queue *p);
int remove_(info *reg, struct queue *p);
int testaVazia(struct queue *p);
int inverte(struct queue *p);
