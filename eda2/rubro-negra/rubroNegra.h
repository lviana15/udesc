#include <stdio.h>
#include <stdlib.h>

enum coloracao { Vermelho, Preto };
typedef enum coloracao Cor;

typedef struct no {
  struct no *pai;
  struct no *esquerda;
  struct no *direita;
  Cor cor;
  int valor;
} NoRN;

typedef struct arvoreRubroNegra {
  struct no *raiz;
  struct no *nulo;
} ArvoreRN;

ArvoreRN *criarRN(void);
int vaziaRN(ArvoreRN *);

NoRN *criarNoRN(ArvoreRN *, NoRN *, int);
NoRN *adicionarNoRN(ArvoreRN *, NoRN *, int, int *);
int adicionarRN(ArvoreRN *, int);
int balancearRN(ArvoreRN *, NoRN *);
int rotacionarEsquerdaRN(ArvoreRN *, NoRN *);
int rotacionarDireitaRN(ArvoreRN *, NoRN *);

NoRN *localizarRN(ArvoreRN *, int);
void visitar(int);
void preOrderRN(ArvoreRN *, NoRN *, void (*)(int));
void inOrderRN(ArvoreRN *, NoRN *, void (*)(int));

NoRN *menorNoRN(ArvoreRN *, NoRN *);
void transplantarRN(ArvoreRN *, NoRN *, NoRN *, int *);
void removerFixupRN(ArvoreRN *, NoRN *, int *);
int removerRN(ArvoreRN *, int);
