#include "rubroNegra.h"

ArvoreRN *criarRN(void) {
  ArvoreRN *arvore = malloc(sizeof(ArvoreRN));
  arvore->nulo = NULL;
  arvore->raiz = NULL;

  arvore->nulo = criarNoRN(arvore, NULL, 0);
  arvore->nulo->cor = Preto;

  return arvore;
}

int vaziaRN(ArvoreRN *arvore) {
  return arvore->raiz == arvore->nulo || arvore->raiz == NULL;
}

NoRN *criarNoRN(ArvoreRN *arvore, NoRN *pai, int valor) {
  NoRN *no = malloc(sizeof(NoRN));

  no->pai = pai;
  no->valor = valor;
  no->direita = arvore->nulo;
  no->esquerda = arvore->nulo;

  return no;
}

NoRN *adicionarNoRN(ArvoreRN *arvore, NoRN *no, int valor, int *contador) {
  (*contador)++;
  if (valor > no->valor) {
    if (no->direita == arvore->nulo) {
      no->direita = criarNoRN(arvore, no, valor);
      no->direita->cor = Vermelho;

      return no->direita;
    } else {
      (*contador)++;
      return adicionarNoRN(arvore, no->direita, valor, contador);
    }
  } else {
    if (no->esquerda == arvore->nulo) {
      no->esquerda = criarNoRN(arvore, no, valor);
      no->esquerda->cor = Vermelho;

      return no->esquerda;
    } else {
      (*contador)++;
      return adicionarNoRN(arvore, no->esquerda, valor, contador);
    }
  }
}

int adicionarRN(ArvoreRN *arvore, int valor) {
  int contador = 0;
  if (vaziaRN(arvore)) {
    arvore->raiz = criarNoRN(arvore, arvore->nulo, valor);
    arvore->raiz->cor = Preto;

    return contador;
  } else {
    NoRN *no = adicionarNoRN(arvore, arvore->raiz, valor, &contador);
    contador += balancearRN(arvore, no);

    return contador;
  }
}

int balancearRN(ArvoreRN *arvore, NoRN *no) {
  int contador = 1;
  while (no->pai->cor == Vermelho) {
    if (no->pai == no->pai->pai->esquerda) {
      NoRN *tio = no->pai->pai->direita;

      contador++;
      if (tio->cor == Vermelho) {
        tio->cor = Preto;
        no->pai->cor = Preto;

        no->pai->pai->cor = Vermelho;
        no = no->pai->pai;
      } else {
        contador++;
        if (no == no->pai->direita) {
          no = no->pai;
          contador += rotacionarEsquerdaRN(arvore, no);
        } else {
          no->pai->cor = Preto;
          no->pai->pai->cor = Vermelho;
          contador += rotacionarDireitaRN(arvore, no->pai->pai);
        }
      }
    } else {
      NoRN *tio = no->pai->pai->esquerda;

      contador++;
      if (tio->cor == Vermelho) {
        tio->cor = Preto;
        no->pai->cor = Preto;

        no->pai->pai->cor = Vermelho;
        no = no->pai->pai;
      } else {
        contador++;
        if (no == no->pai->esquerda) {
          no = no->pai;
          contador += rotacionarDireitaRN(arvore, no);
        } else {
          no->pai->cor = Preto;
          no->pai->pai->cor = Vermelho;
          contador += rotacionarEsquerdaRN(arvore, no->pai->pai);
        }
      }
    }
  }

  arvore->raiz->cor = Preto;
  return contador;
}

int rotacionarEsquerdaRN(ArvoreRN *arvore, NoRN *no) {
  int contador = 0;
  NoRN *direita = no->direita;
  printf("Rotacionando esquerda nó: %d\n", no->valor);
  no->direita = direita->esquerda;

  contador++;
  if (direita != arvore->nulo && direita->esquerda != arvore->nulo) {
    direita->esquerda->pai = no;
  }

  direita->pai = no->pai;

  if (no->pai == arvore->nulo) {
    arvore->raiz = direita;
  } else if (no == no->pai->esquerda) {
    no->pai->esquerda = direita;
  } else {
    no->pai->direita = direita;
  }
  contador += 2;

  direita->esquerda = no;
  no->pai = direita;

  return contador;
}

int rotacionarDireitaRN(ArvoreRN *arvore, NoRN *no) {
  int contador = 0;
  NoRN *esquerda = no->esquerda;
  printf("Rotacionando direita nó %d\n", no->valor);
  no->esquerda = esquerda->direita;

  contador++;
  if (esquerda != arvore->nulo && esquerda->direita != arvore->nulo) {
    esquerda->direita->pai = no;
  }

  esquerda->pai = no->pai;

  if (no->pai == arvore->nulo) {
    arvore->raiz = esquerda;
  } else if (no == no->pai->esquerda) {
    no->pai->esquerda = esquerda;
  } else {
    no->pai->direita = esquerda;
  }
  contador += 2;

  esquerda->direita = no;
  no->pai = esquerda;

  return contador;
}

NoRN *localizarRN(ArvoreRN *arvore, int valor) {
  if (!vaziaRN(arvore)) {
    NoRN *no = arvore->raiz;

    while (no != arvore->nulo) {
      if (no != arvore->nulo) {
        if (no->valor == valor) {
          printf("Nó encontrado %d\n", no->valor);
          return no;
        } else {
          no = valor < no->valor ? no->esquerda : no->direita;
        }
      }
    }
  }

  printf("Nó nao encontrado %d\n", valor);
  return arvore->nulo;
}

void visitar(int valor) { printf("%d ", valor); }

void preOrderRN(ArvoreRN *arvore, NoRN *no, void (*callback)(int)) {
  if (no != arvore->nulo) {
    callback(no->valor);
    preOrderRN(arvore, no->esquerda, callback);
    preOrderRN(arvore, no->direita, callback);
  }
}

void inOrderRN(ArvoreRN *arvore, NoRN *no, void(callback)(int)) {
  if (no != arvore->nulo) {
    inOrderRN(arvore, no->esquerda, callback);
    callback(no->valor);
    inOrderRN(arvore, no->direita, callback);
  }
}

NoRN *menorNoRN(ArvoreRN *arvore, NoRN *no) {
  NoRN *atual = no;
  while (atual != arvore->nulo && atual->esquerda != arvore->nulo)
    atual = atual->esquerda;
  return atual;
}

void transplantarRN(ArvoreRN *arvore, NoRN *antigo, NoRN *novo, int *contador) {
  (*contador)++;
  printf("Transplantando: antigo=%d, novo=%d\n", antigo->valor, novo->valor);
  if (antigo->pai == arvore->nulo) {
    arvore->raiz = novo;
  } else if (antigo == antigo->pai->esquerda) {
    (*contador)++;
    antigo->pai->esquerda = novo;
  } else {
    antigo->pai->direita = novo;
  }
  if (novo != arvore->nulo && novo != NULL) {
    novo->pai = antigo->pai;
  }
}

void removerFixupRN(ArvoreRN *arvore, NoRN *no, int *contador) {
  while (no != arvore->raiz && no->cor == Preto) {
    (*contador)++;
    if (no->pai != arvore->nulo) {
      if (no == no->pai->esquerda) {
        printf("Fixup filho esquerda\n");
        NoRN *irmao = no->pai->direita;
        (*contador)++;
        if (irmao->cor == Vermelho) {
          irmao->cor = Preto;
          no->pai->cor = Vermelho;
          (*contador) += rotacionarEsquerdaRN(arvore, no->pai);
          irmao = no->pai->direita;
        }
        (*contador)++;
        if (irmao->esquerda != arvore->nulo && irmao->direita != arvore->nulo &&
            irmao->esquerda->cor == Preto && irmao->direita->cor == Preto) {
          irmao->cor = Vermelho;
          no = no->pai;
        } else {
          (*contador)++;
          if (irmao->direita->cor == Preto) {
            irmao->esquerda->cor = Preto;
            irmao->cor = Vermelho;
            (*contador) += rotacionarDireitaRN(arvore, irmao);
            irmao = no->pai->direita;
          }
          irmao->cor = no->pai->cor;
          no->pai->cor = Preto;
          irmao->direita->cor = Preto;
          (*contador) += rotacionarEsquerdaRN(arvore, no->pai);
          no = arvore->raiz;
        }
      } else {
        printf("Fixup filho direita\n");
        NoRN *irmao = no->pai->esquerda;
        (*contador)++;
        if (irmao->cor == Vermelho) {
          irmao->cor = Preto;
          no->pai->cor = Vermelho;
          (*contador) += rotacionarDireitaRN(arvore, no->pai);
          irmao = no->pai->esquerda;
        }
        (*contador)++;
        if (irmao->esquerda != arvore->nulo && irmao->direita != arvore->nulo &&
            irmao->esquerda->cor == Preto && irmao->direita->cor == Preto) {
          irmao->cor = Vermelho;
          no = no->pai;
        } else {
          (*contador)++;
          if (irmao->esquerda->cor == Preto) {
            irmao->direita->cor = Preto;
            irmao->cor = Vermelho;
            (*contador) += rotacionarEsquerdaRN(arvore, irmao);
            irmao = no->pai->esquerda;
          }
          irmao->cor = no->pai->cor;
          no->pai->cor = Preto;
          irmao->esquerda->cor = Preto;
          (*contador) += rotacionarDireitaRN(arvore, no->pai);
          no = arvore->raiz;
        }
      }
    }
  }
  no->cor = Preto;
}

int removerRN(ArvoreRN *arvore, int valor) {
  int contador = 1;
  NoRN *removido = localizarRN(arvore, valor);

  if (removido == arvore->nulo) {
    printf("Nao encontrado\n");
    return contador;
  }

  NoRN *substituto = removido;
  NoRN *atual;
  int yCorOriginal = substituto->cor;

  if (removido->esquerda == arvore->nulo) {
    printf("Esquerda nulo\n");
    atual = removido->direita;
    transplantarRN(arvore, removido, removido->direita, &contador);
  } else if (removido->direita == arvore->nulo) {
    printf("Direita nulo\n");
    atual = removido->esquerda;
    transplantarRN(arvore, removido, removido->esquerda, &contador);
  } else {
    printf("Nenhum nulo\n");
    substituto = menorNoRN(arvore, removido->direita);
    yCorOriginal = substituto->cor;
    atual = substituto->direita;
    if (substituto->pai == removido) {
      atual->pai = substituto;
    } else {
      transplantarRN(arvore, substituto, substituto->direita, &contador);
      substituto->direita = removido->direita;
      substituto->direita->pai = substituto;
    }
    transplantarRN(arvore, removido, substituto, &contador);
    substituto->esquerda = removido->esquerda;
    substituto->esquerda->pai = substituto;
    substituto->cor = removido->cor;
  }

  printf("Removendo nó %d\n", removido->valor);
  free(removido);
  if (yCorOriginal == Preto && atual != arvore->nulo) {
    removerFixupRN(arvore, atual, &contador);
  }

  return contador;
}
