#include "arvoreb.h"
#include <stdio.h>
#include <stdlib.h>

ArvoreB *criaArvoreB(int ordem) {
  ArvoreB *a = malloc(sizeof(ArvoreB));
  a->ordem = ordem;
  a->raiz = criaNoB(a);

  return a;
}

NoB *criaNoB(ArvoreB *arvore) {
  int max = arvore->ordem * 2;
  NoB *no = malloc(sizeof(NoB));

  no->pai = NULL;

  no->chaves = malloc(sizeof(int) * (max + 1));
  no->filhos = malloc(sizeof(NoB) * (max + 2));
  no->total = 0;

  for (int i = 0; i < max + 2; i++)
    no->filhos[i] = NULL;

  return no;
}

void inOrderB(NoB *no) {
  if (no != NULL) {
    for (int i = 0; i < no->total; i++) {
      inOrderB(no->filhos[i]);

      printf("%d ", no->chaves[i]);
    }

    inOrderB(no->filhos[no->total]);
  }
}

int pesquisaBinariaB(NoB *no, int chave) {
  int inicio = 0, fim = no->total - 1, meio;

  while (inicio <= fim) {
    meio = (inicio + fim) / 2;

    if (no->chaves[meio] == chave) {
      return meio;
    } else if (no->chaves[meio] > chave) {
      fim = meio - 1;
    } else {
      inicio = meio + 1;
    }
  }
  return inicio;
}

int localizaChaveB(ArvoreB *arvore, int chave) {
  NoB *no = arvore->raiz;

  while (no != NULL) {
    int i = pesquisaBinariaB(no, chave);

    if (i < no->total && no->chaves[i] == chave) {
      return 1;
    } else {
      no = no->filhos[i];
    }
  }

  return 0;
}

NoB *localizaNoB(ArvoreB *arvore, int chave) {
  NoB *no = arvore->raiz;

  while (no != NULL) {
    int i = pesquisaBinariaB(no, chave);

    if (no->filhos[i] == NULL)
      return no;
    else
      no = no->filhos[i];
  }

  return NULL;
}

int transbordoB(ArvoreB *arvore, NoB *no) {
  return no->total > arvore->ordem * 2;
}

NoB *divideNoB(ArvoreB *arvore, NoB *no) {
  int meio = no->total / 2;
  NoB *novo = criaNoB(arvore);
  novo->pai = no->pai;

  for (int i = meio + 1; i < no->total; i++) {
    novo->filhos[novo->total] = no->filhos[i];
    novo->chaves[novo->total] = no->chaves[i];
    if (novo->filhos[novo->total] != NULL)
      novo->filhos[novo->total]->pai = novo;

    novo->total++;
  }

  novo->filhos[novo->total] = no->filhos[no->total];
  if (novo->filhos[novo->total] != NULL)
    novo->filhos[novo->total]->pai = novo;
  no->total = meio;
  return novo;
}

void adicionaChaveNoB(NoB *no, NoB *novo, int chave) {
  int i = pesquisaBinariaB(no, chave);

  for (int j = no->total - 1; j >= i; j--) {
    no->chaves[j + 1] = no->chaves[j];
    no->filhos[j + 2] = no->filhos[j + 1];
  }

  no->chaves[i] = chave;
  no->filhos[i + 1] = novo;

  no->total++;
}

void adicionaChaveRecursivoB(ArvoreB *arvore, NoB *no, NoB *novo, int chave) {
  adicionaChaveNoB(no, novo, chave);

  if (transbordoB(arvore, no)) {
    int promovido = no->chaves[arvore->ordem];
    NoB *novo = divideNoB(arvore, no);

    if (no->pai == NULL) {
      NoB *pai = criaNoB(arvore);
      pai->filhos[0] = no;
      adicionaChaveNoB(pai, novo, promovido);

      no->pai = pai;
      novo->pai = pai;
      arvore->raiz = pai;
    } else
      adicionaChaveRecursivoB(arvore, no->pai, novo, promovido);
  }
}

void adicionaChaveB(ArvoreB *arvore, int chave) {
  NoB *no = localizaNoB(arvore, chave);

  adicionaChaveRecursivoB(arvore, no, NULL, chave);
}

NoB *predecessorB(NoB *no) {
  NoB *atual = no->filhos[no->total];
  while (atual->filhos[0] != NULL) {
    atual = atual->filhos[atual->total];
  }
  return atual;
}

NoB *sucessorB(NoB *no) {
  NoB *atual = no->filhos[0];
  while (atual->filhos[0] != NULL) {
    atual = atual->filhos[0];
  }
  return atual;
}

void removeChaveNoB(NoB *no, int chave) {
  int i = pesquisaBinariaB(no, chave);
  for (int j = i; j < no->total - 1; j++) {
    no->chaves[j] = no->chaves[j + 1];
    no->filhos[j + 1] = no->filhos[j + 2];
  }
  no->total--;
}

void mergeNosB(ArvoreB *arvore, NoB *pai, int pos) {
  NoB *filho = pai->filhos[pos];
  NoB *irmao = pai->filhos[pos + 1];
  filho->chaves[filho->total] = pai->chaves[pos];
  filho->total++;

  for (int i = 0; i < irmao->total; i++) {
    filho->chaves[filho->total] = irmao->chaves[i];
    filho->filhos[filho->total] = irmao->filhos[i];
    if (filho->filhos[filho->total] != NULL)
      filho->filhos[filho->total]->pai = filho;
    filho->total++;
  }

  filho->filhos[filho->total] = irmao->filhos[irmao->total];
  if (filho->filhos[filho->total] != NULL)
    filho->filhos[filho->total]->pai = filho;

  // Update parent's pointers and total count
  for (int i = pos; i < pai->total - 1; i++) {
    pai->chaves[i] = pai->chaves[i + 1];
    pai->filhos[i + 1] = pai->filhos[i + 2];
  }
  pai->total--;

  // Update parent's child pointer if merging a node
  if (pos < pai->total + 1) {
    pai->filhos[pos + 1] = NULL;
  }

  // Free merged node and adjust root if needed
  free(irmao->chaves);
  free(irmao->filhos);
  free(irmao);

  if (pai->total == 0 && pai == arvore->raiz) {
    arvore->raiz = filho;
    filho->pai = NULL;
    free(pai->chaves);
    free(pai->filhos);
    free(pai);
  } else if (pai->total < arvore->ordem / 2) {
    NoB *novaRaiz = pai->filhos[0];
    novaRaiz->pai = NULL;
    arvore->raiz = novaRaiz;
    free(pai->chaves);
    free(pai->filhos);
    free(pai);
  }
}

void removerChaveRecursivoB(ArvoreB *arvore, NoB *no, int chave) {
  int i = pesquisaBinariaB(no, chave);
  // Caso Nó folha
  if (no->filhos[i] == NULL) {
    if (i < no->total && no->chaves[i] == chave) {
      removeChaveNoB(no, chave);
    }
  } else {
    if (i < no->total && no->chaves[i] == chave) {
      NoB *pred = predecessorB(no->filhos[i]);
      no->chaves[i] = pred->chaves[pred->total - 1];
      removerChaveRecursivoB(arvore, pred, no->chaves[i]);
    } else {
      NoB *filho = no->filhos[i];
      if (filho->total < arvore->ordem) {
        if (i > 0 && no->filhos[i - 1]->total > arvore->ordem) {
          NoB *irmaoEsquerdo = no->filhos[i - 1];
          for (int j = filho->total - 1; j >= 0; j--) {
            filho->chaves[j + 1] = filho->chaves[j];
            filho->filhos[j + 2] = filho->filhos[j + 1];
          }
          filho->filhos[1] = filho->filhos[0];
          filho->chaves[0] = no->chaves[i - 1];
          filho->filhos[0] = irmaoEsquerdo->filhos[irmaoEsquerdo->total];
          if (filho->filhos[0] != NULL)
            filho->filhos[0]->pai = filho;
          no->chaves[i - 1] = irmaoEsquerdo->chaves[irmaoEsquerdo->total - 1];
          irmaoEsquerdo->total--;
          filho->total++;
        } else if (i < no->total && no->filhos[i + 1]->total > arvore->ordem) {
          NoB *irmaoDireito = no->filhos[i + 1];
          filho->chaves[filho->total] = no->chaves[i];
          filho->filhos[filho->total + 1] = irmaoDireito->filhos[0];
          if (filho->filhos[filho->total + 1] != NULL)
            filho->filhos[filho->total + 1]->pai = filho;
          no->chaves[i] = irmaoDireito->chaves[0];
          for (int j = 0; j < irmaoDireito->total - 1; j++) {
            irmaoDireito->chaves[j] = irmaoDireito->chaves[j + 1];
            irmaoDireito->filhos[j] = irmaoDireito->filhos[j + 1];
          }
          irmaoDireito->filhos[irmaoDireito->total - 1] =
              irmaoDireito->filhos[irmaoDireito->total];
          irmaoDireito->total--;
          filho->total++;
        } else {
          if (i < no->total) {
            mergeNosB(arvore, no, i);
          } else {
            mergeNosB(arvore, no, i - 1);
          }
        }
      }
      removerChaveRecursivoB(arvore, no->filhos[i], chave);
    }
  }
}

void removerChaveB(ArvoreB *arvore, int chave) {
  if (localizaChaveB(arvore, chave)) {
    removerChaveRecursivoB(arvore, arvore->raiz, chave);
    if (arvore->raiz->total == 0) {
      NoB *velhaRaiz = arvore->raiz;
      if (arvore->raiz->filhos[0] != NULL) {
        arvore->raiz = arvore->raiz->filhos[0];
        arvore->raiz->pai = NULL;
      } else {
        arvore->raiz = NULL;
      }
      free(velhaRaiz->chaves);
      free(velhaRaiz->filhos);
      free(velhaRaiz);
    } else if (arvore->raiz->total < arvore->ordem) {
      NoB *novaRaiz = arvore->raiz->filhos[0];
      novaRaiz->pai = NULL;
      arvore->raiz = novaRaiz;
      free(arvore->raiz->pai->chaves);
      free(arvore->raiz->pai->filhos);
      free(arvore->raiz->pai);
    }
  }
}
