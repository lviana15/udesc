#ifndef QUEUE_H
#define QUEUE_H

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
#include "info.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define debugging 1

struct queue {
  struct node *frente;
  struct node *cauda;
  int tamInfo;
};

//======================FILA=====================
struct queue *cria(int tamInfo);
int insere(info *novo, struct queue *p);
int tamanhoDaFila(struct queue *p);
int reinicia(struct queue *p);
struct queue *destroi(struct queue *p);
int buscaNaCauda(info *reg, struct queue *p);
int buscaNaFrente(info *reg, struct queue *p);
int removeF(info *reg, struct queue *p);
int testaVazia(struct queue *p);

#endif // !QUEUE_H
