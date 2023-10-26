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

struct refMovel {
  struct node *frente;
  struct node *cauda;
  struct node *refMovel;
  int tamInfo;
};

//======================APLICACAO=====================

//======================FILA=====================
struct refMovel *cria(int tamInfo);
int insnere(info *novo, struct refMovel *p);
int tamanhoDaFila(struct refMovel *p);
int reinicia(struct refMovel *p);
struct refMovel *destroi(struct refMovel *p);
int buscaNaCauda(info *reg, struct refMovel *p);
int buscaNaFrente(info *reg, struct refMovel *p);
int remove_(info *reg, struct refMovel *p);
int testaVazia(struct refMovel *p);
int inverte(struct refMovel *p);
