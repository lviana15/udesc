#include "fde.h"
#include <stdio.h>
#include <stdlib.h>

/*************** CRIA ***************/
struct FDE *criaFDE(int tamInfo) {
  struct FDE *desc = (struct FDE *)malloc(sizeof(struct FDE));
  if (desc != NULL) {
    desc->cauda = NULL;
    desc->frente = NULL;
    desc->tamInfo = tamInfo;
  }
  return desc;
}

/*************** INSERE A PARTIR DA FRENTE ***************/
int insereFDE(info *pInfo, struct FDE *p) {
  struct node *novoNoFila = NULL, *visitado = NULL;
  int result = 0;

  if ((novoNoFila = (struct node *)malloc(sizeof(struct node))) != NULL) {
    memcpy(&(novoNoFila->dados), pInfo, p->tamInfo);

    if (p->frente == NULL && p->cauda == NULL) {
      novoNoFila->atras = novoNoFila->defronte = NULL;
      p->frente = p->cauda = novoNoFila;

      result++;
    } else {
      if (novoNoFila->dados.ranking < p->cauda->dados.ranking) {
        novoNoFila->atras = NULL;
        novoNoFila->defronte = p->cauda;
        p->cauda->atras = novoNoFila;
        p->cauda = novoNoFila;

        result++;
      } else {
        visitado = p->frente;
        while (visitado->atras != NULL &&
               (visitado->dados.ranking >= novoNoFila->dados.ranking)) {
          visitado = visitado->atras;

          result++;
        }

        if (visitado->dados.ranking < novoNoFila->dados.ranking) {
          novoNoFila->atras = visitado;
          if (visitado->defronte != NULL) {
            novoNoFila->defronte = visitado->defronte;
            visitado->defronte->atras = novoNoFila;
          } else {
            novoNoFila->defronte = NULL;
            p->frente = novoNoFila;
          }
          visitado->defronte = novoNoFila;
        }
      }
    }
    return result;
  }

  return FRACASSO;
}

/*************** REMOVE DA FRENTE ***************/
int removeFDE(info *reg, struct FDE *p) {
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
int buscaNaFrenteFDE(info *reg, struct FDE *p) {
  int ret = FRACASSO;

  if (p->frente != NULL && p->cauda != NULL) {
    memcpy(reg, &(p->frente->dados), p->tamInfo);
    ret = SUCESSO;
  }

  return ret;
}

/*************** BUSCA NA CAUDA ***************/
int buscaNaCaudaFDE(info *reg, struct FDE *p) {
  int ret = FRACASSO;

  if (p->cauda != NULL && p->frente != NULL) {
    memcpy(reg, &(p->cauda->dados), p->tamInfo);
    ret = SUCESSO;
  }

  return ret;
}

/*************** VAZIA? ***************/
int testaVaziaFDE(struct FDE *p) {
  if (p->frente == NULL && p->cauda == NULL) {
    return SIM;
  }

  return NAO;
}

/*************** TAMANHO ***************/
int tamanhoDaFilaFDE(struct FDE *p) {
  int tam = 0;
  struct node *aux = p->cauda;

  while (aux != NULL) {
    tam++;
    aux = aux->defronte;
  }

  return tam;
}

/*************** PURGA ***************/
int reiniciaFDE(struct FDE *p) {
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
struct FDE *destroiFDE(struct FDE *p) {
  reiniciaFDE(p);
  free(p);
  return NULL; // aterra o ponteiro externo, declarado na aplicação
}
