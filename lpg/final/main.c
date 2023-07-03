#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int verifica_data(Data *data_a, Data *data_b){
  if((data_a->dia == data_b->dia) && (data_a->mes == data_b->mes) && (data_a->ano == data_b->ano))
    return 1;
  return 0;
}

int verifica_horario(Horario *horario_a, Horario *horario_b) {
  if((horario_a->hora == horario_b->hora) && (horario_a->minuto == horario_b->minuto))
    return 1;
  return 0;
}

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


Evento* adiciona_evento(Evento *jogos, int *jogos_count) {
  Evento *novo_jogo;

  (*jogos_count)++;
  jogos = realloc(jogos, (sizeof(Evento) * *jogos_count));
  le_evento(novo_jogo);


  return jogos;
};

int main() {
  Evento *jogos;
  int i, escolha, valido = 1, jogos_count = 0;
  
  jogos = malloc(sizeof(Evento) * jogos_count);
  while(valido == 1) {
    printf("Escolha uma opção:\n");
    printf("1- Cadastrar novo evento\n");
    printf("2- Mostrar todos eventos\n");
    printf("3- Mostrar eventos em data\n");
    printf("4- Mostart eventos com descricao\n");
    printf("5- Remover evento\n");

    switch(escolha) {
      case 1:
        break; 

      case 2:
        if(jogos_count > 0) {
          for(i = 0;i <= jogos_count;i++)
            printa_evento(&jogos[i]);
        } else {
          printf("Lista de jogos vazia.");
        }
        break;

      case 3:
        if(jogos_count > 0) {
          Data *data_pesquisa;
          le_data(data_pesquisa);
          for(i = 0;i <= jogos_count;i++){
            if(verifica_data(jogos[i].data_jogo, data_pesquisa))
              printa_evento(&jogos[i]);
          }
          free(data_pesquisa);
        }
        break;

      case 4:
        if(jogos_count > 0) {
          char desc_pesquisa[10]; 
          printf("Digite a descricao que deseja buscar:\n");
          fgets(desc_pesquisa, 10, stdin);
          for(i = 0;i <= jogos_count;i++){
            if(strcmp(jogos[i].descricao, desc_pesquisa) == 0)
              printa_evento(&jogos[i]);
          }
        }
        break;

      case 5:
        if (jogos_count > 0) {
          Data *data_exclusao;
          Horario *horario_exclusao;
          printf("Digite que evento deseja excluir:");
          le_data(data_exclusao);
          le_horario(horario_exclusao);

          for(i = 0;i <= jogos_count;i++){
            if(verifica_data(jogos[i].data_jogo, data_exclusao) && verifica_horario(jogos[i].horario_inicio, horario_exclusao)){}
          }
        }
    }
  }

  free(jogos);
  return 0;
}
