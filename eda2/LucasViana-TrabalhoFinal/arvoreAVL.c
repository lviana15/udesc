#include "arvoreAVL.h"
#include <stdio.h>
#include <stdlib.h>

ArvoreAVL *criarAVL() {
  ArvoreAVL *arvore = malloc(sizeof(ArvoreAVL));
  arvore->raiz = NULL;

  return arvore;
}

int vaziaAVL(ArvoreAVL *arvore) { return arvore->raiz == NULL; }

int adicionarNoAVL(NoAVL *no, int valor) {
  int contador = 1;

  if (valor > no->valor) {
    if (no->direita == NULL) {
      NoAVL *novo = criarNoAVL(no, valor);
      no->direita = novo;

      return contador;
    } else {
      return contador + adicionarNoAVL(no->direita, valor);
    }
  } else {
    if (no->esquerda == NULL) {
      NoAVL *novo = criarNoAVL(no, valor);
      no->esquerda = novo;

      return contador;
    } else {
      return contador + adicionarNoAVL(no->esquerda, valor);
    }
  }
}

int adicionarAVL(ArvoreAVL *arvore, int valor) {
  int contador = 0;

  if (vaziaAVL(arvore)) {
    arvore->raiz = criarNoAVL(NULL, valor);

    return ++contador;
  } else {
    contador++;
    contador += adicionarNoAVL(arvore->raiz, valor);
    contador += balanceamentoAVL(arvore, arvore->raiz->pai);
    return contador;
  }
}

NoAVL *criarNoAVL(NoAVL *pai, int valor) {
  NoAVL *no = malloc(sizeof(NoAVL));
  no->valor = valor;
  no->pai = pai;
  no->esquerda = NULL;
  no->direita = NULL;
  no->altura = 1;

  return no;
}

NoAVL *menorNoAVL(NoAVL *no) {
  NoAVL *atual = no;
  while (atual && atual->esquerda != NULL)
    atual = atual->esquerda;
  return atual;
}

int removerAVL(ArvoreAVL *arvore, int valor) {
  int contador = 1;
  NoAVL *removido = localizarAVL(arvore->raiz, valor);
  if (removido == NULL)
    return contador;

  NoAVL *pai = removido->pai;
  NoAVL *filho;

  if (removido->esquerda == NULL && removido->direita == NULL) {
    if (pai == NULL) {
      arvore->raiz = NULL;
    } else if (removido == pai->esquerda) {
      pai->esquerda = NULL;
    } else if (removido == pai->direita) {
      pai->direita = NULL;
    }
    free(removido);
    contador += 3;
  } else if (removido->esquerda == NULL || removido->direita == NULL) {
    filho =
        (removido->esquerda != NULL) ? removido->esquerda : removido->direita;
    if (pai == NULL) {
      arvore->raiz = filho;
    } else if (removido == pai->esquerda) {
      pai->esquerda = filho;
    } else {
      pai->direita = filho;
    }
    filho->pai = pai;
    free(removido);
    contador += 3;
  } else {
    NoAVL *sucessor = menorNoAVL(removido->direita);
    int valorSucessor = sucessor->valor;
    contador += removerAVL(arvore, sucessor->valor);
    removido->valor = valorSucessor;
    contador++;
  }

  if (pai != NULL) {
    contador += balanceamentoAVL(arvore, pai);
  }

  return contador;
}

NoAVL *localizarAVL(NoAVL *no, int valor) {
  if (no->valor == valor) {
    return no;
  } else {
    if (valor < no->valor) {
      if (no->esquerda != NULL) {
        return localizarAVL(no->esquerda, valor);
      }
    } else {
      if (no->direita != NULL) {
        return localizarAVL(no->direita, valor);
      }
    }
  }

  return NULL;
}

void inOrderAVL(NoAVL *no, void (*callback)(int)) {
  if (no != NULL) {
    inOrderAVL(no->esquerda, callback);
    callback(no->valor);
    inOrderAVL(no->direita, callback);
  }
}

void preOrderAVL(NoAVL *no, void (*callback)(int)) {
  if (no != NULL) {
    callback(no->valor);
    preOrderAVL(no->esquerda, callback);
    preOrderAVL(no->direita, callback);
  }
}

void visitarAVL(int valor) { printf("%d ", valor); }

int balanceamentoAVL(ArvoreAVL *arvore, NoAVL *no) {
  int contador = 1;
  while (no != NULL) {
    int fator = fbAVL(no);
    int alturaEsquerda = (no->esquerda != NULL) ? no->esquerda->altura : 0;
    int alturaDireita = (no->direita != NULL) ? no->direita->altura : 0;

    no->altura =
        (alturaEsquerda > alturaDireita ? alturaEsquerda : alturaDireita) + 1;
    contador++;

    if (fator > 1) {
      if (fbAVL(no->esquerda) >= 0) {
        // printf("RSD(%d)\n", no->valor);
        rsdAVL(arvore, no);
        contador++;
      } else {
        // printf("RDD(%d)\n", no->valor);
        rddAVL(arvore, no);
        contador += 2;
      }
    } else if (fator < -1) {
      if (fbAVL(no->direita) <= 0) {
        // printf("RSE(%d)\n", no->valor);
        rseAVL(arvore, no);
        contador++;
      } else {
        // printf("RDE(%d)\n", no->valor);
        rdeAVL(arvore, no);
        contador += 2;
      }
    }

    no = no->pai;
  }

  return contador;
}

int alturaAVL(NoAVL *no) {
  if (no == NULL) {
    return 0;
  }

  int esquerda = alturaAVL(no->esquerda) + 1;
  int direita = alturaAVL(no->direita) + 1;

  return esquerda > direita ? esquerda : direita;
}

int fbAVL(NoAVL *no) { return alturaAVL(no->esquerda) - alturaAVL(no->direita); }

NoAVL *rseAVL(ArvoreAVL *arvore, NoAVL *no) {
  NoAVL *pai = no->pai;
  NoAVL *direita = no->direita;

  if (direita->esquerda != NULL) {
    direita->esquerda->pai = no;
  }

  no->direita = direita->esquerda;
  no->pai = direita;

  direita->esquerda = no;
  direita->pai = pai;

  if (pai == NULL) {
    arvore->raiz = direita;
  } else {
    if (pai->esquerda == no) {
      pai->esquerda = direita;
    } else {
      pai->direita = direita;
    }
  }

  return direita;
}

NoAVL *rsdAVL(ArvoreAVL *arvore, NoAVL *no) {
  NoAVL *pai = no->pai;
  NoAVL *esquerda = no->esquerda;

  if (esquerda->direita != NULL) {
    esquerda->direita->pai = no;
  }

  no->esquerda = esquerda->direita;
  no->pai = esquerda;

  esquerda->direita = no;
  esquerda->pai = pai;

  if (pai == NULL) {
    arvore->raiz = esquerda;
  } else {
    if (pai->esquerda == no) {
      pai->esquerda = esquerda;
    } else {
      pai->direita = esquerda;
    }
  }

  return esquerda;
}

NoAVL *rdeAVL(ArvoreAVL *arvore, NoAVL *no) {
  no->direita = rsdAVL(arvore, no->direita);
  return rseAVL(arvore, no);
}

NoAVL *rddAVL(ArvoreAVL *arvore, NoAVL *no) {
  no->esquerda = rseAVL(arvore, no->esquerda);
  return rsdAVL(arvore, no);
}
