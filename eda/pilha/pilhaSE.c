#include "arq.h"

int vazia(struct pilha *pil) {
  if (pil->topo == NULL)
    return SIM;
  else
    return NAO;
}

struct pilha *cria(void) {
  struct pilha *p = NULL;
  p = (struct pilha *)malloc(sizeof(struct pilha));
  if (p) {
    p->topo = NULL; //<<<<<<
    p->tamPilha = 0;
  }
  return p;
}

int empilha(info *novo, struct pilha *pil) {
  struct noPDE *aux = NULL;
  aux = (struct noPDE *)malloc(sizeof(struct noPDE));
  if (aux != NULL) {
    memcpy(&(aux->dados), novo, sizeof(info)); //<<<<<<<<<<
    aux->abaixo = pil->topo;
    pil->topo = aux;
    (pil->tamPilha)++;
    return SUCESSO;
  } else
    return FRACASSO;
}

int desempilha(info *reg, struct pilha *pil) {
  struct noPDE *aux = NULL;
  if (vazia(pil) == NAO) {
    memcpy(reg, &(pil->topo->dados), sizeof(info)); //<<<<<<<
    aux = pil->topo->abaixo;
    free(pil->topo);
    pil->topo = aux;
    (pil->tamPilha)--;
    return SUCESSO;
  } else
    return FRACASSO;
}

int busca(info *reg, struct pilha *pil) {
  if (vazia(pil) == NAO) {
    memcpy(reg, &(pil->topo->dados), sizeof(info)); //<<<<<<<
    return SUCESSO;
  } else
    return FRACASSO;
}

void reinicia(struct pilha *pil) {
  struct noPDE *aux = NULL;
  if (vazia(pil) == NAO) {
    aux = pil->topo->abaixo;
    while (aux != NULL) {
      free(pil->topo);
      pil->topo = aux;
      aux = aux->abaixo;
    }
    free(pil->topo);
    pil->topo = NULL;
    pil->tamPilha = 0;
  }
}

struct pilha *destroi(struct pilha *pil) {
  reinicia(pil);
  free(pil);
  return NULL;
}
