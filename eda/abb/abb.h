struct NoABB {
  struct NoABB *filhoEsq;
  struct NoABB *filhoDir;
  int data;
};

typedef struct ABB {
  struct NoABB *raiz;
};

ABB *criaABB(int valor);
int insereABB(ABB *abb, int valor);
NoABB removeABB(ABB *abb, int valor);
int buscaABB(ABB *abb, int valor);
int destroiABB(ABB *abb);
int contagemABB(ABB *abb);
