#include "lib.h"
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr,
            "Uso: %s <arquivo_definicao_automato> <arquivo_palavras_teste>\n",
            argv[0]);
    return 1;
  }

  printf("Abrindo arquivo de definição do autômato: %s\n", argv[1]);
  FILE *arquivoAutomato = fopen(argv[1], "r");
  if (!arquivoAutomato) {
    perror("Erro ao abrir arquivo de definição do autômato");
    return 1;
  }

  AP *automato = criaAutomato();
  if (!automato) {
    fprintf(stderr, "Erro ao alocar memória para o autômato\n");
    fclose(arquivoAutomato);
    return 1;
  }

  char linha[256];
  while (fgets(linha, sizeof(linha), arquivoAutomato)) {
    if (startsWith(linha, "Alfabeto:")) {
      parseAlfabeto(automato, linha);
    } else if (startsWith(linha, "Estados:")) {
      parseEstados(automato, linha);
    } else if (startsWith(linha, "Auxiliar:")) {
      parseAuxiliar(automato, linha);
    } else if (startsWith(linha, "Estado inicial:")) {
      parseInicial(automato, linha);
    } else if (startsWith(linha, "Finais:")) {
      parseFinais(automato, linha);
    } else if (startsWith(linha, "Transicoes:")) {
      parseTransicoes(arquivoAutomato, automato);
    }
  }
  fclose(arquivoAutomato);

  if (verificaAutomato(automato) == 0) {
    liberarAutomato(automato);
    return 1;
  }

  printf("Abrindo arquivo de palavras de teste: %s\n", argv[2]);
  FILE *entradas = fopen(argv[2], "r");
  if (!entradas) {
    perror("Erro ao abrir arquivo de palavras de teste");
    liberarAutomato(automato);
    return 1;
  }

  char palavra[256];
  while (fgets(palavra, sizeof(palavra), entradas)) {
    palavra[strcspn(palavra, "\n")] = 0;
    simulaAutomato(automato, palavra);
  }
  fclose(entradas);

  liberarAutomato(automato);

  return 0;
}
