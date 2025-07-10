typedef struct noB {
  int total;
  int *chaves;
  struct noB **filhos;
  struct noB *pai;
} NoB;

typedef struct arvoreB {
  NoB *raiz;
  int ordem;
} ArvoreB;

ArvoreB *criaArvoreB(int);
NoB *criaNoB(ArvoreB *);

void inOrderB(NoB *);
int pesquisaBinariaB(NoB *, int, int *);

int localizaChaveB(ArvoreB *, int, int *contador);
NoB *localizaNoB(ArvoreB *, int, int *);

int transbordoB(ArvoreB *, NoB *);
NoB *divideNoB(ArvoreB *, NoB *, int *);
void adicionaChaveNoB(NoB *, NoB *, int, int *);
int adicionaChaveRecursivoB(ArvoreB *, NoB *, NoB *, int);
int adicionaChaveB(ArvoreB *, int);

NoB *predecessor(NoB *);
NoB *sucessorB(NoB *);

void removerChaveNoB(NoB *, int);
void mergeNosB(ArvoreB *, NoB *, int);
void removerChaveRecursivoB(ArvoreB *, NoB *, int);
void removerChaveB(ArvoreB *, int chave);

void free_nodes(NoB *, int);
void free_b_tree(ArvoreB *);
