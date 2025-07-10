#include "lib.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define VERMELHO "\x1b[31m"
#define VERDE "\x1b[32m"
#define LIMPA "\x1b[0m"

Pilha *criaPilha() {
  Pilha *pilha = malloc(sizeof(Pilha));

  pilha->topo = NULL;

  return pilha;
}

void empilha(Pilha *pilha, char *simbolo) {
  No *novo = (No *)malloc(sizeof(No));
  novo->simbolo = strdup(simbolo);
  novo->prox = pilha->topo;

  pilha->topo = novo;
}

int desempilha(Pilha *pilha) {
  if (vazia(pilha)) {
    printf("Error: Trying to pop from an empty stack.\n");
    return 1;
  }

  No *removido = pilha->topo;
  pilha->topo = removido->prox;
  free(removido->simbolo);
  free(removido);

  return 0;
}

int vazia(Pilha *pilha) { return pilha->topo == NULL; }

char *topo(Pilha *pilha) {
  if (!vazia(pilha)) {
    return strdup(pilha->topo->simbolo);
  } else {
    return strdup("-");
  }
}

void destroi(Pilha *pilha) {
  No *aux = NULL;

  if (!vazia(pilha)) {
    aux = pilha->topo->prox;

    while (aux != NULL) {
      free(pilha->topo->simbolo);
      free(pilha->topo);

      pilha->topo = aux;
      aux = aux->prox;
    }

    free(pilha->topo->simbolo);
    free(pilha->topo);
  }

  free(pilha);
}

void apresenta(Pilha *pilha) {
  No *no = pilha->topo;

  printf(" ___\n");

  while (no) {
    printf("| %s |\n", no->simbolo);
    no = no->prox;
  }
}

HashTable *criaHashTable(int tamanho) {
  HashTable *hash = (HashTable *)malloc(sizeof(HashTable));
  hash->total = 0;
  hash->tamanho = tamanho;
  hash->elementos = (HashEntrada **)malloc(sizeof(HashEntrada *) * tamanho);

  for (int i = 0; i < hash->tamanho; i++) {
    hash->elementos[i] = NULL;
  }

  return hash;
}

void adicionarHash(HashTable *hash, char *chave, Estado *estado) {
  if (hash != NULL && hash->total < hash->tamanho) {
    int idx = hashing(chave, hash->tamanho);

    HashEntrada *novaEntrada = (HashEntrada *)malloc(sizeof(HashEntrada));
    novaEntrada->chave = strdup(chave);
    novaEntrada->estado = estado;
    novaEntrada->prox = hash->elementos[idx];

    hash->elementos[idx] = novaEntrada;
  }
}

void removerHash(HashTable *hash, char *chave) {
  unsigned int idx = hashing(chave, hash->tamanho);
  HashEntrada *entrada = hash->elementos[idx];
  HashEntrada *anterior = NULL;

  while (entrada != NULL && strcmp(entrada->chave, chave) != 0) {
    anterior = entrada;
    entrada = entrada->prox;
  }

  if (entrada == NULL) {
    printf("Chave '%s' nao encontrada.\n", chave);
    return;
  }

  if (anterior == NULL) {
    hash->elementos[idx] = entrada->prox;
  } else {
    anterior->prox = entrada->prox;
  }

  hash->total--;
  free(entrada);
}

unsigned int hashing(char *chave, int tamanho) {
  unsigned int hashValue = 0;
  for (int i = 0; chave[i] != '\0'; i++) {
    hashValue = 31 * hashValue + chave[i];
  }
  return hashValue % tamanho;
}

Estado *getEstado(HashTable *hash, char *chave) {
  unsigned int idx = hashing(chave, hash->tamanho);
  HashEntrada *entrada = hash->elementos[idx];
  while (entrada != NULL && (strcmp(entrada->chave, chave) != 0)) {
    entrada = entrada->prox;
  }

  return entrada == NULL ? NULL : entrada->estado;
}

AP *criaAutomato() {
  AP *automato = (AP *)malloc(sizeof(AP));
  automato->alfabeto = NULL;
  automato->auxiliar = NULL;
  automato->estados = criaHashTable(32);
  automato->inicial = NULL;
  automato->pilha = criaPilha();

  return automato;
}

Estado *criaEstado(char *id) {
  Estado *estado = (Estado *)malloc(sizeof(Estado));
  estado->id = id;
  estado->final = 0;
  estado->transicoes = NULL;

  return estado;
}

void adicionaTransicao(Estado *estadoAtual, char *fita, char *desempilha,
                       char *empilha, Estado *proxEstado) {
  Transicao *novaTransicao = (Transicao *)malloc(sizeof(Transicao));

  novaTransicao->fita = strdup(fita);
  novaTransicao->desempilha = strdup(desempilha);
  novaTransicao->empilha = strdup(empilha);
  novaTransicao->proximoEstado = proxEstado;

  novaTransicao->prox = estadoAtual->transicoes;
  estadoAtual->transicoes = novaTransicao;
}

Transicao *criaTransicao(char *fita, char *desempilha, char *empilha,
                         Estado *proximo) {
  Transicao *transicao = (Transicao *)malloc(sizeof(Transicao));
  transicao->fita = fita;
  transicao->empilha = empilha;
  transicao->desempilha = desempilha;
  transicao->proximoEstado = proximo;

  return transicao;
};

void parseAlfabeto(AP *automato, char *linha) {
  char **alfabeto = NULL;
  int tam = 0;

  char *token = strtok(linha, "{, }");
  token = strtok(NULL, "{, }");

  while (token) {
    if (isalpha(token[0])) {
      alfabeto = (char **)realloc(alfabeto, (tam + 1) * sizeof(char *));
      alfabeto[tam] = (char *)malloc(2 * sizeof(char));
      alfabeto[tam][0] = token[0];
      alfabeto[tam][1] = '\0';
      tam++;
    }

    token = strtok(NULL, "{, }");
  }

  alfabeto = (char **)realloc(alfabeto, (tam + 1) * sizeof(char *));
  alfabeto[tam] = NULL;

  automato->alfabeto = alfabeto;
}

void parseEstados(AP *automato, char *linha) {
  char *token = strtok(linha, "{, }");
  token = strtok(NULL, "{, }");

  while (token) {
    if (isalnum(token[0])) {
      Estado *estado = criaEstado(strdup(token));
      adicionarHash(automato->estados, token, estado);
    }

    token = strtok(NULL, "{, }");
  }
}

void parseInicial(AP *automato, char *linha) {
  Estado *estado = NULL;

  char *token = strtok(linha, ": ");
  token = strtok(NULL, ": ");
  token = strtok(NULL, ": ");

  token[strcspn(token, "\n")] = 0;

  estado = getEstado(automato->estados, token);
  if (estado == NULL) {
    printf("Estado inicial (%s) invalido", token);
  } else {
    automato->inicial = estado;
  }
}

void parseTransicoes(FILE *arquivo, AP *automato) {
  char linha[256];
  while (fgets(linha, sizeof(linha), arquivo)) {
    char *id = NULL, *atual = NULL, *proximo = NULL, *fita = NULL,
         *desempilha = NULL, *empilha = NULL;
    if (sscanf(linha, "%m[^:]: [%m[^,], %m[^,], %m[^,], %m[^,], %m[^]]", &id,
               &atual, &proximo, &fita, &desempilha, &empilha) == 6) {
      // printf("Lendo linha de transição: %s", linha);

      Estado *estadoAtual = getEstado(automato->estados, atual);
      Estado *proximoEstado = getEstado(automato->estados, proximo);
      if (estadoAtual && proximoEstado) {
        adicionaTransicao(estadoAtual, fita, desempilha, empilha,
                          proximoEstado);
      } else {
        printf("Estado atual (%s) ou próximo estado (%s) não encontrado no "
               "automato\n",
               atual, proximo);
      }

      free(id);
    } else {
      printf("Não foi possível ler/transicionar para a linha: %s", linha);
    }
  }
}

void parseFinais(AP *automato, char *linha) {
  char *token = strtok(linha, "{, }");
  token = strtok(NULL, "{, }");

  while (token != NULL) {
    Estado *estado = getEstado(automato->estados, token);
    if (estado) {
      estado->final = 1;
    } else {
      printf("Estado %s não encontrado.\n", token);
    }

    token = strtok(NULL, "{}, \t\n");
  }
}

void parseAuxiliar(AP *automato, char *linha) {
  char **auxiliar = NULL;
  int tam = 0;

  char *inicio = strchr(linha, '{');
  if (!inicio) {
    return;
  }
  inicio++;

  char *final = strchr(inicio, '}');
  if (!final) {
    return;
  }
  *final = '\0';

  char *token = strtok(inicio, ", ");
  while (token) {
    auxiliar = (char **)realloc(auxiliar, (tam + 1) * sizeof(char *));
    auxiliar[tam] = strdup(token);
    tam++;
    token = strtok(NULL, ", ");
  }

  auxiliar = (char **)realloc(auxiliar, (tam + 1) * sizeof(char *));
  auxiliar[tam] = NULL;

  automato->auxiliar = auxiliar;
}

void buscaProfundidade(Estado *estado, HashTable *estados, int *visitados) {
  if (visitados[hashing(estado->id, estados->tamanho)]) {
    return;
  }

  visitados[hashing(estado->id, estados->tamanho)] = 1;

  Transicao *transicao = estado->transicoes;
  while (transicao != NULL) {
    buscaProfundidade(transicao->proximoEstado, estados, visitados);
    transicao = transicao->prox;
  }
}

int verificaAutomato(AP *automato) {
  printf("Verificando automato...\n");

  // Arrays para marcar símbolos utilizados
  int *simbolosUtilizados = calloc(automato->estados->tamanho, sizeof(int));
  int *auxiliarUtilizados = calloc(automato->estados->tamanho, sizeof(int));

  // Verificação de transições e símbolos
  for (int i = 0; i < automato->estados->tamanho; i++) {
    HashEntrada *entrada = automato->estados->elementos[i];
    while (entrada) {
      Estado *estado = entrada->estado;
      printf("Verificando estado: %s\n", estado->id);

      Transicao *transicao = estado->transicoes;
      while (transicao) {
        printf("  Transicao: [%s, %s, %s, %s, %s]\n", estado->id,
               transicao->proximoEstado ? transicao->proximoEstado->id : "NULL",
               transicao->fita, transicao->desempilha, transicao->empilha);

        if (!transicao->proximoEstado) {
          printf(VERMELHO "  Erro: Transicao para estado vazio.\n\n" LIMPA);
          free(simbolosUtilizados);
          free(auxiliarUtilizados);
          return 0;
        }

        int simboloValido = 0;
        for (int j = 0; automato->alfabeto[j] != NULL; j++) {
          if (strcmp(automato->alfabeto[j], transicao->fita) == 0 ||
              strcmp(transicao->fita, "$") == 0) {
            simboloValido = 1;
            simbolosUtilizados[j] = 1;
            break;
          }
        }

        if (!simboloValido) {
          printf(VERMELHO
                 "  Erro: Simbolo %s nao pertence ao alfabeto.\n\n" LIMPA,
                 transicao->fita);
          free(simbolosUtilizados);
          free(auxiliarUtilizados);
          return 0;
        }

        int simboloAuxiliarValido = 0;
        for (int k = 0; automato->auxiliar[k] != NULL; k++) {
          if (strcmp(automato->auxiliar[k], transicao->desempilha) == 0 ||
              strcmp(transicao->desempilha, "$") == 0) {
            simboloAuxiliarValido = 1;
            auxiliarUtilizados[k] = 1;
            break;
          }
        }

        if (!simboloAuxiliarValido) {
          printf(
              VERMELHO
              "  Erro: Simbolo %s nao pertence ao alfabeto auxiliar.\n\n" LIMPA,
              transicao->desempilha);
          free(simbolosUtilizados);
          free(auxiliarUtilizados);
          return 0;
        }

        simboloAuxiliarValido = 0;
        for (int k = 0; automato->auxiliar[k] != NULL; k++) {
          if (strcmp(automato->auxiliar[k], transicao->empilha) == 0 ||
              strcmp(transicao->empilha, "$") == 0) {
            simboloAuxiliarValido = 1;
            auxiliarUtilizados[k] = 1;
            break;
          }
        }

        if (!simboloAuxiliarValido) {
          printf(
              VERMELHO
              "  Erro: Simbolo %s nao pertence ao alfabeto auxiliar.\n\n" LIMPA,
              transicao->empilha);
          free(simbolosUtilizados);
          free(auxiliarUtilizados);
          return 0;
        }

        transicao = transicao->prox;
      }

      entrada = entrada->prox;
    }
  }

  // Verificação de estados não alcançáveis
  int *visitados = calloc(automato->estados->tamanho, sizeof(int));
  buscaProfundidade(automato->inicial, automato->estados, visitados);

  for (int i = 0; i < automato->estados->tamanho; i++) {
    HashEntrada *entrada = automato->estados->elementos[i];
    while (entrada) {
      if (!visitados[hashing(entrada->estado->id,
                             automato->estados->tamanho)]) {
        printf(VERMELHO "  Erro: Estado %s nao e alcançavel.\n\n" LIMPA,
               entrada->estado->id);
        free(visitados);
        free(simbolosUtilizados);
        free(auxiliarUtilizados);
        return 0;
      }
      entrada = entrada->prox;
    }
  }

  // Verificação de símbolos não utilizados no alfabeto
  for (int j = 0; automato->alfabeto[j] != NULL; j++) {
    if (!simbolosUtilizados[j]) {
      printf(VERMELHO
             "  Aviso: Simbolo %s no alfabeto nao e utilizado.\n\n" LIMPA,
             automato->alfabeto[j]);
    }
  }

  // Verificação de símbolos não utilizados no alfabeto auxiliar
  for (int k = 0; automato->auxiliar[k] != NULL; k++) {
    if (!auxiliarUtilizados[k]) {
      printf(
          VERMELHO
          "  Aviso: Simbolo %s no alfabeto auxiliar nao e utilizado.\n\n" LIMPA,
          automato->auxiliar[k]);
    }
  }

  free(visitados);
  free(simbolosUtilizados);
  free(auxiliarUtilizados);
  printf(VERDE "Automato válido.\n\n" LIMPA);
  return 1;
}

void apresentaAlfabeto(char **alfabeto, const char *descricao) {
  printf("%s: { ", descricao);
  for (int i = 0; alfabeto[i] != NULL; i++) {
    printf("%s", alfabeto[i]);
    if (alfabeto[i + 1] != NULL) {
      printf(", ");
    }
  }
  printf(" }\n");
}

void apresentaTransicoes(Transicao *transicao) {
  while (transicao) {
    printf("    [%s, %s, %s] -> %s\n", transicao->fita, transicao->desempilha,
           transicao->empilha, transicao->proximoEstado->id);
    transicao = transicao->prox;
  }
}

void apresentaEstados(HashTable *hash) {
  printf("Estados:\n");
  for (int i = 0; i < hash->tamanho; i++) {
    HashEntrada *entrada = hash->elementos[i];
    while (entrada != NULL) {
      Estado *estado = entrada->estado;
      printf("  Estado: %s%s\n", estado->id, estado->final ? " (final)" : "");
      printf("  Transições:\n");
      apresentaTransicoes(estado->transicoes);
      printf("\n");
      entrada = entrada->prox;
    }
  }
}

void apresentaAutomato(AP *automato) {
  printf("Apresentando autômato:\n");

  apresentaAlfabeto(automato->alfabeto, "Alfabeto");
  apresentaAlfabeto(automato->auxiliar, "Alfabeto auxiliar");
  apresentaEstados(automato->estados);

  printf("Estado inicial: %s\n", automato->inicial->id);
}

int startsWith(const char *str, const char *pre) {
  while (*pre && *str) {
    if (tolower((unsigned char)*pre) != tolower((unsigned char)*str) &&
        !isspace((unsigned char)*str)) {
      return 0;
    }
    pre++;
    str++;
  }
  return 1;
}

void liberarAlfabeto(char **alfabeto) {
  if (alfabeto) {
    for (int i = 0; alfabeto[i] != NULL; i++) {
      free(alfabeto[i]);
    }
    free(alfabeto);
  }
}

void liberarPilha(Pilha *pilha) {
  if (pilha) {
    while (!vazia(pilha)) {
      desempilha(pilha);
    }
    free(pilha);
  }
}

void liberarTransicoes(Transicao *transicao) {
  while (transicao) {
    Transicao *prox = transicao->prox;
    free(transicao);
    transicao = prox;
  }
}

void liberarEstado(Estado *estado) {
  if (estado) {
    liberarTransicoes(estado->transicoes);
    free(estado->id);
    free(estado);
  }
}

void liberarHashTable(HashTable *hash) {
  if (hash) {
    for (int i = 0; i < hash->tamanho; i++) {
      HashEntrada *entrada = hash->elementos[i];
      while (entrada) {
        HashEntrada *prox = entrada->prox;
        liberarEstado(entrada->estado);
        if (entrada->chave != NULL)
          free(entrada->chave);
        free(entrada);
        entrada = prox;
      }
    }
    free(hash->elementos);
    free(hash);
  }
}

void liberarAutomato(AP *automato) {
  if (automato) {
    liberarAlfabeto(automato->alfabeto);
    liberarAlfabeto(automato->auxiliar);
    liberarHashTable(automato->estados);
    liberarPilha(automato->pilha);
    free(automato);
  }
}

int simulaAutomatoRecursivo(Estado *estadoAtual, Pilha *pilha, char *entrada,
                            int i) {
  if (entrada[i] == '\0') {
    // Verifica se o estado atual é final quando a entrada é completamente
    // processada
    if (estadoAtual->final) {
      // printf("Palavra '%s' aceita pelo automato.\n", entrada);
      return 1; // Aceita a entrada
    } else {
      // Verifica transições vazias para estados finais
      Transicao *transicao = estadoAtual->transicoes;
      while (transicao != NULL) {
        if (strcmp(transicao->fita, "$") == 0 &&
            strcmp(transicao->desempilha, "$") == 0 &&
            transicao->proximoEstado->final) {

          // printf("\nVerificando transicao vazia para estado final: [%s, %s, "
          //        "%s, %s, %s]\n",
          //        estadoAtual->id, transicao->proximoEstado->id,
          //        transicao->fita, transicao->desempilha, transicao->empilha);

          // Chama recursivamente sem avançar no símbolo da entrada
          // printf("Movendo para o proximo estado: %s\n",
          //       transicao->proximoEstado->id);
          return simulaAutomatoRecursivo(transicao->proximoEstado, pilha,
                                         entrada, i);
        }
        transicao = transicao->prox;
      }

      // printf("Palavra rejeitada pelo automato (estado %s não é final).\n",
      //        estadoAtual->id);
      return 0; // Rejeita a entrada
    }
  }

  char simboloAtual = entrada[i];
  int aceitou =
      0; // Flag para indicar se a palavra foi aceita por alguma transição

  // Percorre as transições do estado atual para encontrar todas as transições
  // válidas
  Transicao *transicao = estadoAtual->transicoes;
  while (transicao != NULL) {
    // printf("\nVerificando transicao: [%s, %s, %s, %s, %s]\n",
    // estadoAtual->id,
    //        transicao->proximoEstado->id, transicao->fita,
    //        transicao->desempilha, transicao->empilha);

    // Verifica transição normal com símbolo da fita e desempilhamento
    if (transicao->fita[0] == simboloAtual &&
        (strcmp(topo(pilha), transicao->desempilha) == 0 ||
         strcmp(transicao->desempilha, "$") == 0)) {

      // Processa a transição encontrada
      // Desempilha e empilha conforme necessário
      if (strcmp(transicao->desempilha, "$") != 0) {
        // printf("Desempilhando %s\n", transicao->desempilha);
        desempilha(pilha);
      }
      if (strcmp(transicao->empilha, "$") != 0) {
        // printf("Empilhando %s\n", transicao->empilha);
        empilha(pilha, transicao->empilha);
      }

      // Chama recursivamente para o próximo símbolo da entrada
      // printf("Movendo para o proximo estado: %s\n",
      //      transicao->proximoEstado->id);
      if (simulaAutomatoRecursivo(transicao->proximoEstado, pilha, entrada,
                                  i + 1)) {
        aceitou = 1; // Marca que a palavra foi aceita por uma transição
      }

      // Desfaz a transição para testar outras possibilidades
      if (strcmp(transicao->empilha, "$") != 0) {
        // printf("Desempilhando %s\n", transicao->empilha);
        desempilha(pilha);
      }
      if (strcmp(transicao->desempilha, "$") != 0) {
        // printf("Empilhando %s\n", transicao->desempilha);
        empilha(pilha, transicao->desempilha);
      }
    }

    // Verifica transição vazia
    if (strcmp(transicao->fita, "$") == 0 &&
        strcmp(transicao->desempilha, "$") == 0) {

      // printf("\nVerificando transicao vazia: [%s, %s, %s, %s, %s]\n",
      // estadoAtual->id, transicao->proximoEstado->id, transicao->fita,
      // transicao->desempilha, transicao->empilha);

      // Chama recursivamente sem avançar no símbolo da entrada
      // printf("Movendo para o proximo estado: %s\n",
      // transicao->proximoEstado->id);
      if (simulaAutomatoRecursivo(transicao->proximoEstado, pilha, entrada,
                                  i)) {
        aceitou = 1; // Marca que a palavra foi aceita por uma transição vazia
      }
    }

    transicao = transicao->prox;
  }

  // Retorna se a palavra foi aceita por alguma transição
  return aceitou;
}

void simulaAutomato(AP *automato, char *entrada) {
  Estado *estadoInicial = automato->inicial;
  Pilha *pilha = criaPilha();
  empilha(pilha, "$"); // Empilha símbolo vazio inicialmente

  printf("\nTestando palavra: %s\n", entrada);
  if (simulaAutomatoRecursivo(estadoInicial, pilha, entrada, 0)) {
    printf(VERDE "Palavra '%s' Aceita" LIMPA "\n",
           strcmp(entrada, "") ? entrada : "vazia");
  } else {
    printf(VERMELHO "Palavra '%s' Rejeitada" LIMPA "\n", entrada);
  }

  liberarPilha(pilha);
}
