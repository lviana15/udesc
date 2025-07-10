#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compara(const void *a, const void *b) { return *(int *)a - *(int *)b; }

int *geraVetor(int n) {
  int *v = malloc(sizeof(int) * (n + 1));
  int i;

  for (i = 0; i < n; i++) {
    v[i] = rand() % n;
  }

  qsort(v, n, sizeof(int), compara);
  return v;
}

int pesquisaSequencial(int chave, int v[], int n) {
  int contador = 1;
  int i;

  for (i = 0; i < n; i++) {
    contador++;
    if (v[i] == chave) {
      return contador; // sucesso
    }
    contador++;
  }

  return contador; // insucesso
}

int pesquisaSequencialSentinela(int chave, int v[], int n) {
  int contador = 1, i = 0;
  v[n] = chave;

  while (v[i] != chave) {
    i++;
    contador++;
  }
  contador++;

  if (i < n)
    return contador; // sucesso

  return contador; // insucesso
}

int pesquisaBinaria(int chave, int v[], int n) {
  int inicio = 0, fim = n - 1, contador = 1;

  while (inicio <= fim) {
    int meio = (inicio + fim) / 2;
    contador++;
    if (chave == v[meio]) {
      return contador; // sucesso
    } else if (chave < v[meio]) {
      fim = meio - 1;
    } else {
      inicio = meio + 1;
    }
    contador += 2;
  }

  return contador; // insucesso
}

int pesquisaInterpolacao(int chave, int v[], int n) {
  int inicio = 0, meio, fim = n - 1, contador = 1;

  if (v[inicio] == v[fim]) {
    contador++;
    return v[inicio] == chave ? contador : contador;
  }

  contador += 3;
  while (inicio <= fim && chave >= v[inicio] && chave <= v[fim]) {
    contador++;
    if (inicio == fim) {
      contador++;
      return v[inicio] == chave ? contador : contador;
    }

    meio = inicio + (((double)(fim - inicio) / (v[fim] - v[inicio])) *
                     (chave - v[inicio]));

    contador++;
    if (chave == v[meio]) {
      return contador;
    } else if (chave < v[meio]) {
      fim = meio - 1;
    } else {
      inicio = meio + 1;
    }

    contador += 4;
  }

  return contador; // Índice inválido
}

int main() {
  srand(time(NULL));

  FILE *arquivo = fopen("experimento.csv", "w");

  fprintf(arquivo, "N,Sequencial,Sentinela,Binaria,Interpolacao\n");

  for (int n = 1; n <= 1000; n++) {
    int *v = geraVetor(n);

    unsigned long sequencial = 0;
    unsigned long sentinela = 0;
    unsigned long binaria = 0;
    unsigned long interpolacao = 0;
    int k = 1000;

    for (int i = 0; i < k; i++) {
      int chave = v[rand() % n];

      sequencial += pesquisaSequencial(chave, v, n);
      sentinela += pesquisaSequencialSentinela(chave, v, n);
      binaria += pesquisaBinaria(chave, v, n);
      interpolacao += pesquisaInterpolacao(chave, v, n);
    }

    fprintf(arquivo, "%d,%lu,%lu,%lu,%lu\n", n, sequencial / k, sentinela / k,
            binaria / k, interpolacao / k);
  }

  fclose(arquivo);
}
