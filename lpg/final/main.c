#include <stdio.h>
#include <stdlib.h>

struct data {
  int dia;
  int mes;
  int ano;
};

struct horario {
  int hora;
  int minuto;
};

struct evento {
  struct data data_jogo;
  struct horario horario_inicio;
  struct horario horario_fim;
  char descicao[10];
  char local[20];
};

int main() {

  return 0;
}
