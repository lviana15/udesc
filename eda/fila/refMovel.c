#include "refMovel.h"
#include <stdlib.h>

/*************** CRIA ***************/
struct refMovel *cria_(int tamInfo) {
  struct refMovel *desc = (struct refMovel *)malloc(sizeof(struct refMovel));
  if (desc != NULL) {
    desc->cauda = NULL;
    desc->frente = NULL;
    desc->tamInfo = tamInfo;
  }
  return desc;
}

/*************** INSERE A PARTIR DA FRENTE ***************/
int insere_(info *pInfo, struct refMovel *p) {
  int result = 0;
  struct node *novoNoFila = NULL, *visitado = NULL;

  if ((novoNoFila = (struct node *)malloc(sizeof(struct node))) != NULL) {
    memcpy(&(novoNoFila->dados), pInfo, p->tamInfo);

    if (p->frente == NULL && p->cauda == NULL) {
      novoNoFila->atras = novoNoFila->defronte = NULL;
      p->frente = p->cauda = novoNoFila;

      p->refMovel = novoNoFila;
      result++;
      return result;
    }

    // Caso 1
    if (novoNoFila->dados.ranking <= p->cauda->dados.ranking) {
      novoNoFila->atras = NULL;
      novoNoFila->defronte = p->cauda;
      p->cauda->atras = novoNoFila;
      p->cauda = novoNoFila;

      p->refMovel = novoNoFila;

      result++;
      return result;
    }

    // Caso 2
    if (p->frente->dados.ranking < novoNoFila->dados.ranking) {
      novoNoFila->atras = p->frente;
      novoNoFila->defronte = NULL;
      p->frente->defronte = novoNoFila;
      p->frente = novoNoFila;

      p->refMovel = novoNoFila;

      result++;
      return result;
    }

    // Caso 3 -- Novo entre cauda e refMovel
    if ((p->cauda->dados.ranking < novoNoFila->dados.ranking) &&
        (novoNoFila->dados.ranking <= p->refMovel->dados.ranking)) {
      int deltaA = abs(p->cauda->dados.ranking - novoNoFila->dados.ranking);
      int deltaB = abs(p->refMovel->dados.ranking - novoNoFila->dados.ranking);

      // Busca pela cauda
      if (deltaA < deltaB) {
        visitado = p->cauda;
        while (visitado != NULL &&
               visitado->dados.ranking <= novoNoFila->dados.ranking) {
          visitado = visitado->defronte;
          result++;
        }

        novoNoFila->atras = visitado;
        novoNoFila->defronte = visitado->defronte;

        if (visitado != NULL) {
          visitado->defronte = novoNoFila;
        } else {
          p->cauda = novoNoFila;
        }

        result++;
        return result;
      } else {
        visitado = p->refMovel;
        while (visitado != NULL &&
               visitado->dados.ranking >= novoNoFila->dados.ranking) {
          visitado = visitado->atras;
          result++;
        }

        novoNoFila->defronte = visitado;
        novoNoFila->atras = visitado->atras;

        if (visitado != NULL) {
          visitado->atras = novoNoFila;
        } else {
          p->refMovel = novoNoFila;
        }

        result++;
        return result;
      }
    }

    // Caso 4 -- Novo entre refMovel e frente
    if ((p->refMovel->dados.ranking < novoNoFila->dados.ranking) &&
        (novoNoFila->dados.ranking <= p->frente->dados.ranking)) {
      int deltaA = abs(p->refMovel->dados.ranking - novoNoFila->dados.ranking);
      int deltaB = abs(p->frente->dados.ranking - novoNoFila->dados.ranking);

      if (deltaA < deltaB) {
        visitado = p->refMovel;
        while (visitado != NULL &&
               visitado->dados.ranking >= novoNoFila->dados.ranking) {
          visitado = visitado->atras;
          result++;
        }

        novoNoFila->defronte = visitado;
        novoNoFila->atras = visitado->atras;

        if (visitado != NULL) {
          visitado->atras = novoNoFila;
        } else {
          p->refMovel = novoNoFila;
        }

        result++;
        return result;
      } else {
        visitado = p->frente;
        while (visitado != NULL &&
               visitado->dados.ranking <= novoNoFila->dados.ranking) {
          visitado = visitado->defronte;
          result++;
        }

        novoNoFila->atras = visitado;
        novoNoFila->defronte = visitado->defronte;

        if (visitado != NULL) {
          visitado->defronte = novoNoFila;
        } else {
          p->frente = novoNoFila;
        }

        result++;
        return result;
      }
    }
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
int buscaNaFrente_(info *reg, struct refMovel *p) {
  int ret = FRACASSO;

  if (p->frente != NULL && p->cauda != NULL) {
    memcpy(reg, &(p->frente->dados), p->tamInfo);
    ret = SUCESSO;
  }

  return ret;
}

/*************** BUSCA NA CAUDA ***************/
int buscaNaCauda_(info *reg, struct refMovel *p) {
  int ret = FRACASSO;

  if (p->cauda != NULL && p->frente != NULL) {
    memcpy(reg, &(p->cauda->dados), p->tamInfo);
    ret = SUCESSO;
  }

  return ret;
}

/*************** VAZIA? ***************/
int testaVazia_(struct refMovel *p) {
  if (p->frente == NULL && p->cauda == NULL) {
    return SIM;
  }

  return NAO;
}

/*************** TAMANHO ***************/
int tamanhoDaFila_(struct refMovel *p) {
  int tam = 0;
  struct node *aux = p->cauda;

  while (aux != NULL) {
    tam++;
    aux = aux->defronte;
  }

  return tam;
}

/*************** PURGA ***************/
int reinicia_(struct refMovel *p) {
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
struct refMovel *destroi_(struct refMovel *p) {
  reinicia_(p);
  free(p);
  return NULL; // aterra o ponteiro externo, declarado na aplicação
}
