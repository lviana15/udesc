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

int empilha(info *novo, struct pilha *pilha) {
  struct noPDE *aux = NULL;
  aux = (struct noPDE *)malloc(sizeof(struct noPDE));

  if (aux != NULL) {
    memcpy(&(aux->dados), novo, sizeof(info)); //<<<<<<<<<<

    aux->acima = NULL;
    aux->abaixo = pilha->topo;

    pilha->topo = aux;
    (pilha->tamPilha)++;

    return SUCESSO;
  } else
    return FRACASSO;
}

int desempilha(info *reg, struct pilha *pilha) {
  struct noPDE *aux = NULL;

  if (vazia(pilha) == NAO) {
    memcpy(reg, &(pilha->topo->dados), sizeof(info)); //<<<<<<<

    aux = pilha->topo->abaixo;
    free(pilha->topo);

    pilha->topo = aux;
    (pilha->tamPilha)--;

    return SUCESSO;
  } else
    return FRACASSO;
}

int busca(info *reg, struct pilha *pilha) {
  if (vazia(pilha) == NAO) {
    memcpy(reg, &(pilha->topo->dados), sizeof(info)); //<<<<<<<
    return SUCESSO;
  } else
    return FRACASSO;
}

int buscaBase(info *reg, struct pilha *pilha) {
  struct noPDE *aux = NULL;

  if (vazia(pilha) == NAO) {
    aux = pilha->topo;

    while (aux != NULL) {
      pilha->topo = aux;
      aux = aux->abaixo;
    }

    memcpy(reg, &(pilha->topo->dados), sizeof(info));

    return SUCESSO;
  } else
    return FRACASSO;
}

void reinicia(struct pilha *pilha) {
  struct noPDE *aux = NULL;

  if (vazia(pilha) == NAO) {
    aux = pilha->topo->abaixo;

    while (aux != NULL) {
      free(pilha->topo);

      pilha->topo = aux;
      aux = aux->abaixo;
    }

    free(pilha->topo);

    pilha->topo = NULL;
    pilha->tamPilha = 0;
  }
}

struct pilha *destroi(struct pilha *pilha) {
  reinicia(pilha);
  free(pilha);

  return NULL;
}
