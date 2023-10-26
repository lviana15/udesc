#include "refMovel.h"

/*************** CRIA ***************/
struct refMovel *cria(int tamInfo) {
  struct refMovel *desc = (struct refMovel *)malloc(sizeof(struct refMovel));
  if (desc != NULL) {
    desc->cauda = NULL;
    desc->frente = NULL;
    desc->tamInfo = tamInfo;
  }
  return desc;
}

/*************** INSERE A PARTIR DA FRENTE ***************/
int insere(info *pInfo, struct refMovel *p) {
  int result;
  struct node *novoNoFila = NULL, *visitado = NULL;

  if ((novoNoFila = (struct node *)malloc(sizeof(struct node))) != NULL) {
      memcpy(&(novoNoFila->dados), pInfo, p->tamInfo);

      if (p->frente == NULL && p->cauda == NULL) {
          novoNoFila->atras = novoNoFila->defronte = NULL;
          p->frente = p->cauda = novoNoFila;
      } else {
          if(novoNoFila->dados.ranking < p->cauda->dados.ranking) {
              novoNoFila->atras = NULL;
              novoNoFila->defronte = p->cauda;
              p->cauda->atras = novoNoFila;
              p->cauda = novoNoFila;
          }
      }

      return result;
  }

  return FRACASSO;
}

/*************** REMOVE DA FRENTE ***************/
int remove_(info *reg, struct refMovel *p) {
  int ret = FRACASSO;
  struct node *aux = p->cauda;

  if (p->cauda != NULL && p->frente != NULL) {
    memcpy(reg, &(p->frente->dados), p->tamInfo);

    if (aux == p->frente) { // caso tenha 1 elemento apenas
      free(p->frente);
      p->frente = p->cauda = NULL;
    } else {
      p->frente = p->frente->atras;
      free(p->frente->defronte);
      p->frente->defronte = NULL;
    }
    ret = SUCESSO;
  }

  return ret;
}

/*************** BUSCA NA FRENTE ***************/
int buscaNaFrente(info *reg, struct refMovel *p) {
  int ret = FRACASSO;

  if (p->frente != NULL && p->cauda != NULL) {
    memcpy(reg, &(p->frente->dados), p->tamInfo);
    ret = SUCESSO;
  }

  return ret;
}

/*************** BUSCA NA CAUDA ***************/
int buscaNaCauda(info *reg, struct refMovel *p) {
  int ret = FRACASSO;

  if (p->cauda != NULL && p->frente != NULL) {
    memcpy(reg, &(p->cauda->dados), p->tamInfo);
    ret = SUCESSO;
  }

  return ret;
}

/*************** VAZIA? ***************/
int testaVazia(struct refMovel *p) {
  if (p->frente == NULL && p->cauda == NULL) {
    return SIM;
  }

  return NAO;
}

/*************** TAMANHO ***************/
int tamanhoDaFila(struct refMovel *p) {
  int tam = 0;
  struct node *aux = p->cauda;

  while (aux != NULL) {
    tam++;
    aux = aux->defronte;
  }

  return tam;
}

/*************** PURGA ***************/
int reinicia(struct refMovel *p) {
  int ret = FRACASSO;
  struct node *aux = NULL;

  if (p->frente != NULL && p->cauda != NULL) {
    aux = p->cauda->defronte;
    while (aux != NULL) {
      free(p->cauda);
      p->cauda = aux;
      aux = aux->defronte;
    }

    free(p->cauda);
    p->frente = NULL;
    p->cauda = NULL;
    ret = SUCESSO;
  }
  return ret;
}

/*************** DESTROI ***************/
struct refMovel *destroi(struct refMovel *p) {
  reinicia(p);
  free(p);
  return NULL; // aterra o ponteiro externo, declarado na aplicação
}
