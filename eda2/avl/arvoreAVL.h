typedef struct noAVL {
  struct noAVL *pai;
  struct noAVL *esquerda;
  struct noAVL *direita;
  int valor;
  int altura;
} NoAVL;

typedef struct arvoreAVL {
  struct noAVL *raiz;
} ArvoreAVL;

ArvoreAVL *criarAVL();
int vaziaAVL(ArvoreAVL *);
int adicionarNoAVL(NoAVL *, int);
int adicionarAVL(ArvoreAVL *, int);
NoAVL *criarNoAVL(NoAVL *, int);
NoAVL *menorNoAVL(NoAVL *);
int removerAVL(ArvoreAVL *, int);

NoAVL *localizarAVL(NoAVL *, int);
void inOrderAVL(NoAVL *, void (*)(int));
void preOrderAVL(NoAVL *, void (*)(int));
void visitarAVL(int);
int balanceamentoAVL(ArvoreAVL *, NoAVL *);
int alturaAVL(NoAVL *);

int fbAVL(NoAVL *);
NoAVL *rsdAVL(ArvoreAVL *, NoAVL *);
NoAVL *rseAVL(ArvoreAVL *, NoAVL *);
NoAVL *rddAVL(ArvoreAVL *, NoAVL *);
NoAVL *rdeAVL(ArvoreAVL *, NoAVL *);
