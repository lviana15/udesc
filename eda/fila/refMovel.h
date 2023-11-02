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
struct refMovel *cria_(int tamInfo);
int insere_(info *novo, struct refMovel *p);
int tamanhoDaFila_(struct refMovel *p);
int reinicia_(struct refMovel *p);
struct refMovel *destroi_(struct refMovel *p);
int buscaNaCauda_(info *reg, struct refMovel *p);
int buscaNaFrente_(info *reg, struct refMovel *p);
int remove_(info *reg, struct refMovel *p);
int testaVazia_(struct refMovel *p);
