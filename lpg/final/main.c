#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int dia;
  int mes;
  int ano;
} Data;

typedef struct {
  int hora;
  int minuto;
} Horario;

typedef struct {
  Data *data_jogo;
  Horario *horario_inicio;
  Horario *horario_fim;
  char descricao[10];
  char local[20];
} Evento;

void le_data(Data *data){
  printf("Digite data (DD/MM/AAAA):\n");
  scanf("%d", &data->dia); 
  scanf("%d", &data->mes); 
  scanf("%d", &data->ano); 
};

void le_horario(Horario *horario) {
  scanf("%d", &horario->hora);
  scanf("%d", &horario->minuto);
}

void le_evento(Evento *evento) {
  evento->data_jogo = malloc(sizeof(Data));
  evento->horario_inicio = malloc(sizeof(Horario));
  evento->horario_fim = malloc(sizeof(Horario));

  le_data(evento->data_jogo);

  printf("Digite horario de inicio (HH:MM):\n");
  le_horario(evento->horario_inicio);

  printf("Digite horario de fim (HH:MM):\n");
  le_horario(evento->horario_fim);

  int c;
  while ((c = getchar()) != '\n' && c != EOF) {}
  printf("Digite a descrição do evento:\n");
  fgets(evento->descricao, 10, stdin); 

  fflush(stdin);
  printf("Digite o local do evento:\n");
  fgets(evento->local, 20, stdin); 
}

void printa_data(Data *data) {
  printf("%02d/%02d/%4d\n", data->dia, data->mes, data->ano);
};

void printa_horario(Horario *horario) {
  printf("%02d:%02d\n", horario->hora, horario->minuto);
};

void printa_evento(Evento *evento) {
  printa_data(evento->data_jogo);
  printa_horario(evento->horario_inicio);
  printf("%s", evento->descricao);
  printf("%s", evento->local);
}

int main() {
  Evento *games;
  int valido = 1, games_count = 0;
  
  games = malloc(sizeof(Evento) * games_count);
  while(valido == 1) {
    printf("Escolha uma opção:\n");
    printf("1- Cadastrar novo evento\n");
    printf("2- Mostrar todos eventos\n");
    printf("3- Mostrar eventos em data\n");
    printf("4- Mostart eventos com descicao\n");
    printf("5- Remover evento\n");
  }


  free(games);
  return 0;
}
