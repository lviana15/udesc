#include <stdio.h>

typedef struct No {
  char *simbolo;
  struct No *prox;
} No;

typedef struct {
  No *topo;
} Pilha;

typedef struct HashEntrada {
  char *chave;
  struct Estado *estado;
  struct HashEntrada *prox;
} HashEntrada;

typedef struct {
  int total;
  int tamanho;
  HashEntrada **elementos;
} HashTable;

typedef struct Transicao {
  char *fita;
  char *desempilha;
  char *empilha;
  struct Estado *proximoEstado;
  struct Transicao *prox;
} Transicao;

typedef struct Estado {
  char *id;
  int final;
  Transicao *transicoes;
} Estado;

typedef struct AP {
  char **alfabeto;
  char **auxiliar;
  HashTable *estados;
  Estado *inicial;
  Pilha *pilha;
} AP;

// Funções da pilha
Pilha *criaPilha();
void empilha(Pilha *, char *);
int desempilha(Pilha *);
int vazia(Pilha *);
char *topo(Pilha *);
void destroi(Pilha *);
void apresenta(Pilha *);

// Funções da HashTable
HashTable *criaHashTable(int);
void adicionarHash(HashTable *, char *, Estado *);
void removerHash(HashTable *, char *);
unsigned int hashing(char *, int);
Estado *getEstado(HashTable *, char *);
void liberarHashTable(HashTable *);

AP *criaAutomato();
Estado *criaEstado(char *);
Transicao *criaTransicao(char *, char *, char *, Estado *);
void adicionaTransicao(Estado *, char *, char *, char *, Estado *);

// Funçoes reconhecimento entrada (Automato)
int startsWith(const char *, const char *);
void parseAlfabeto(AP *, char *);
void parseEstados(AP *, char *);
void parseInicial(AP *, char *);
void parseTransicoes(FILE *, AP *);
void parseFinais(AP *, char *);
void parseAuxiliar(AP *, char *);

int verificaAutomato(AP *);
void apresentaAutomato(AP *);
void liberarAutomato(AP *);

int simulaAutomatoRecursivo(Estado *, Pilha *, char *, int);
void simulaAutomato(AP *, char *);
