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
#include "info.h"

#define debugging 1


struct refMovel {
  struct node *frente;
  struct node *cauda;
  struct node *refMovel;
  int tamInfo;
};

//======================FILA=====================
struct refMovel *criaFRM(int tamInfo);
int insereFRM(info *novo, struct refMovel *p);
int tamanhoDaFilaFRM(struct refMovel *p);
int reiniciaFRM(struct refMovel *p);
struct refMovel *destroiFRM(struct refMovel *p);
int buscaNaCaudaFRM(info *reg, struct refMovel *p);
int buscaNaFrenteFRM(info *reg, struct refMovel *p);
int removeFRM(info *reg, struct refMovel *p);
int testaVaziaFRM(struct refMovel *p);
