#include "arvoreAVL.h"
#include "arvoreb.h"
#include "rubroNegra.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int insertion_completed = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

typedef struct {
  int *keys;
  int n;
  unsigned long *result;
  void *tree;
} ThreadArgs;

void *thread_insert_avl(void *args) {
  ThreadArgs *targs = (ThreadArgs *)args;
  for (int j = 0; j < targs->n; j++) {
    *(targs->result) += adicionarAVL((ArvoreAVL *)targs->tree, targs->keys[j]);
  }

  pthread_mutex_lock(&mutex);
  insertion_completed = 1;
  pthread_cond_signal(&cond);
  pthread_mutex_unlock(&mutex);

  return NULL;
}

void *thread_remove_avl(void *args) {
  ThreadArgs *targs = (ThreadArgs *)args;

  pthread_mutex_lock(&mutex);
  while (!insertion_completed) {
    pthread_cond_wait(&cond, &mutex);
  }
  pthread_mutex_unlock(&mutex);

  for (int j = 0; j < targs->n; j++) {
    *(targs->result) += removerAVL((ArvoreAVL *)targs->tree, targs->keys[j]);
  }
  return NULL;
}

void *thread_insert_rn(void *args) {
  ThreadArgs *targs = (ThreadArgs *)args;
  for (int j = 0; j < targs->n; j++) {
    *(targs->result) += adicionarRN((ArvoreRN *)targs->tree, targs->keys[j]);
  }

  pthread_mutex_lock(&mutex);
  insertion_completed = 1;
  pthread_cond_signal(&cond);
  pthread_mutex_unlock(&mutex);

  return NULL;
}

void *thread_remove_rn(void *args) {
  ThreadArgs *targs = (ThreadArgs *)args;

  pthread_mutex_lock(&mutex);
  while (!insertion_completed) {
    pthread_cond_wait(&cond, &mutex);
  }
  pthread_mutex_unlock(&mutex);

  for (int j = 0; j < targs->n; j++) {
    *(targs->result) += removerRN((ArvoreRN *)targs->tree, targs->keys[j]);
  }
  return NULL;
}

void *thread_insert_b(void *args) {
  ThreadArgs *targs = (ThreadArgs *)args;
  for (int j = 0; j < targs->n; j++) {
    *(targs->result) += adicionaChaveB((ArvoreB *)targs->tree, targs->keys[j]);
  }
  return NULL;
}

void trocar(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

// Embaralha vetor
void fisherYates(int *v, int tam) {
  srand(time(NULL));
  for (int i = tam - 1; i > 0; i--) {
    int j = rand() % (i + 1);
    trocar(&v[i], &v[j]);
  }
}

// Gera vetor ordenado
int *geraVetor(int n) {
  int *v = malloc(n * sizeof(int));
  for (int i = 0; i < n; i++)
    v[i] = i + 1;

  fisherYates(v, n);
  return v;
}

int main(void) {
  srand(time(NULL));
  FILE *insercao = fopen("insercao.csv", "w"),
       *remocao = fopen("remocao.csv", "w");

  fprintf(insercao, "N,AVL,Rubro-Negra,ArvoreB1,ArvoreB5,ArvoreB10\n");
  fprintf(remocao, "N,AVL,Rubro-Negra,ArvoreB1,ArvoreB5,ArvoreB10\n");

  for (int n = 1; n <= 10000; n++) {
    ArvoreAVL *arvoreAVL = criarAVL();
    ArvoreRN *arvoreRN = criarRN();
    ArvoreB *ordem1 = criaArvoreB(1), *ordem5 = criaArvoreB(5),
            *ordem10 = criaArvoreB(10);

    unsigned long adicaoAVL = 0, adicaoRN = 0, adicaoB1 = 0, adicaoB5 = 0,
                  adicaoB10 = 0;
    unsigned long remocaoAVL = 0, remocaoRN = 0;

    int k = 10;
    int *v = geraVetor(n);

    for (int i = 0; i < k; i++) {
      pthread_t tid_avl_insert, tid_rn_insert, tid_b1_insert, tid_b5_insert,
          tid_b10_insert;

      ThreadArgs args_avl_insert = {v, n, &adicaoAVL, arvoreAVL};
      // ThreadArgs args_avl_remove = {v, n, &remocaoAVL, arvoreAVL};
      ThreadArgs args_rn_insert = {v, n, &adicaoRN, arvoreRN};
      // ThreadArgs args_rn_remove = {v, n, &remocaoRN, arvoreRN};
      ThreadArgs args_b1_insert = {v, n, &adicaoB1, ordem1};
      ThreadArgs args_b5_insert = {v, n, &adicaoB5, ordem5};
      ThreadArgs args_b10_insert = {v, n, &adicaoB10, ordem10};

      pthread_create(&tid_avl_insert, NULL, thread_insert_avl,
                     &args_avl_insert);
      pthread_create(&tid_rn_insert, NULL, thread_insert_rn, &args_rn_insert);
      pthread_create(&tid_b1_insert, NULL, thread_insert_b, &args_b1_insert);
      pthread_create(&tid_b5_insert, NULL, thread_insert_b, &args_b5_insert);
      pthread_create(&tid_b10_insert, NULL, thread_insert_b, &args_b10_insert);

      pthread_join(tid_avl_insert, NULL);
      // pthread_join(tid_avl_remove, NULL);
      pthread_join(tid_rn_insert, NULL);
      // pthread_join(tid_rn_remove, NULL);
      pthread_join(tid_b1_insert, NULL);
      pthread_join(tid_b5_insert, NULL);
      pthread_join(tid_b10_insert, NULL);

      for (int j = 0; j < n; j++) {
        remocaoAVL += removerAVL(arvoreAVL, v[j]);
        remocaoRN += removerRN(arvoreRN, v[j]);
      }
    }

    fprintf(insercao, "%d,%lu,%lu,%lu,%lu,%lu\n", n, adicaoAVL / k,
            adicaoRN / k, adicaoB1 / k, adicaoB5 / k, adicaoB10 / k);

    fprintf(remocao, "%d,%lu,%lu\n", n, remocaoAVL / k, remocaoRN / k);

    free(arvoreAVL);
    free(arvoreRN);
    free_b_tree(ordem1);
    free_b_tree(ordem5);
    free_b_tree(ordem10);
  }

  return 0;
}
