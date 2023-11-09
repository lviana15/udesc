typedef struct NoABB {
  struct NoABB *filhoEsq;
  struct NoABB *filhoDir;
  int data;
} NoABB;


NoABB *criaABB(int valor);
int insereABB(NoABB *abb, int valor);
NoABB removeABB(NoABB *abb, int valor);
int buscaABB(NoABB *abb, int valor);
int destroiABB(NoABB *abb);
int contagemABB(NoABB *abb);
