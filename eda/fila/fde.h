#ifndef FDE_H
#define FDE_H

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

struct FDE {
  struct node *frente;
  struct node *cauda;
  int tamInfo;
};

//======================FILA=====================
struct FDE *criaFDE(int tamInfo);
int insereFDE(info *novo, struct FDE *p);
int tamanhoDaFilaFDE(struct FDE *p);
int reiniciaFDE(struct FDE *p);
struct FDE *destroiFDE(struct FDE *p);
int buscaNaCaudaFDE(info *reg, struct FDE *p);
int buscaNaFrenteFDE(info *reg, struct FDE *p);
int removeFDE(info *reg, struct FDE *p);
int testaVaziaFDE(struct FDE *p);

#endif
