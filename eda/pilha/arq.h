#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define SIM 1
#define NAO 0
#define SUCESSO 1
#define FRACASSO 0

//======== Modelo de dados utilizados na implementação da PILHA
//
// Estrutura com informações para
typedef struct info {
  char palavra[15];
  int idade;
} info;

// Nó contendo campo de encadeamento (apontador "abaixo") e área
// para os dados da aplicação (campo "int")
struct noPDE {
  info dados;
  struct noPDE *abaixo;
  struct noPDE *acima;
};
//
// Descritor da pilha, contendo:
// O apontador "topo", o qual indica o endereço do descritor da pilha e
// o "tamanho" atual da pilha
struct pilha {
  struct noPDE *topo;
  int tamPilha;
};

//====== Operações providas na interface da PILHA
//
struct pilha *cria(void);
int vazia(struct pilha *pil);
int empilha(info *dados, struct pilha *pil);
int desempilha(info *dados, struct pilha *pil);
int busca(info *dados, struct pilha *pil);
void reinicia(struct pilha *pil);
struct pilha *destroi(struct pilha *pil);
