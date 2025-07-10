typedef struct no {
  int total;
  int *chaves;
  struct no **filhos;
  struct no *pai;
} NoB;

typedef struct arvoreB {
  NoB *raiz;
  int ordem;
} ArvoreB;

ArvoreB *criaArvoreB(int);
NoB *criaNoB(ArvoreB *);

void inOrderB(NoB *);
int pesquisaBinariaB(NoB *, int);

int localizaChaveB(ArvoreB *, int);
NoB *localizaNoB(ArvoreB *, int);

int transbordoB(ArvoreB *, NoB *);
NoB *divideNoB(ArvoreB *, NoB *);
void adicionaChaveNoB(NoB *, NoB *, int);
void adicionaChaveRecursivoB(ArvoreB *, NoB *, NoB *, int);
void adicionaChaveB(ArvoreB *, int);

NoB *predecessor(NoB *);
NoB *sucessorB(NoB *);

void removerChaveNoB(NoB *, int);
void mergeNosB(ArvoreB *, NoB *, int);
void removerChaveRecursivoB(ArvoreB *, NoB *, int);
void removerChaveB(ArvoreB *, int chave);
