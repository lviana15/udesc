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

Data* le_data(void){
  Data *data;
  data = malloc(sizeof(Data));
  printf("Digite data (DD/MM/AAAA):\n");
  scanf("%d", &data->dia); 
  scanf("%d", &data->mes); 
  scanf("%d", &data->ano); 
  return data;
};

int verifica_data(Data data_a, Data data_b){
  if((data_a.dia == data_b.dia) && (data_a.mes == data_b.mes) && (data_a.ano == data_b.ano))
    return 1;
  return 0;
}

int verifica_horario(Horario horario_a, Horario horario_b) {
  if((horario_a.hora == horario_b.hora) && (horario_a.minuto == horario_b.minuto))
    return 1;
  return 0;
}

Horario* le_horario(void) {
  Horario *horario;
  horario = malloc(sizeof(Horario));

  do {
    printf("Digite a hora (entre 0 e 23): ");
    scanf("%d", &horario->hora);
  } while (horario->hora < 0 || horario->hora > 23);

  do {
    printf("Digite os minutos (entre 0 e 59): ");
    scanf("%d", &horario->minuto);
  } while (horario->minuto < 0 || horario->minuto > 59);

  return horario;
}

Evento le_evento(void) {
  Evento novo_evento;
  
  novo_evento.data_jogo = le_data();

  printf("Digite horario de inicio:\n");
  novo_evento.horario_inicio = le_horario();

  printf("Digite horario de fim:\n");
  novo_evento.horario_fim = le_horario();

  int c;
  while ((c = getchar()) != '\n' && c != EOF) {}
  printf("Digite a descrição do evento:\n");
  fgets(novo_evento.descricao, 10, stdin); 

  fflush(stdin);
  printf("Digite o local do evento:\n");
  fgets(novo_evento.local, 20, stdin); 

  return novo_evento;
};

void printa_data(Data *data) {
  printf("%02d/%02d/%4d\n", data->dia, data->mes, data->ano);
};

void printa_horario(Horario *horario) {
  printf("%02d:%02d\n", horario->hora, horario->minuto);
};

void printa_evento(Evento *evento) {
  printf("\n");
  printa_data(evento->data_jogo);
  printa_horario(evento->horario_inicio);
  printf("%s", evento->descricao);
  printf("%s", evento->local);
}


Evento* adiciona_evento(Evento *jogos, int *jogos_count) {
  (*jogos_count)++;
  jogos = realloc(jogos, (sizeof(Evento) * *jogos_count));
  jogos[*jogos_count-1] = le_evento();

  return jogos;
};

int main() {
  Evento *jogos;
  int i, escolha, valido = 1, jogos_count = 0;
  
  jogos = malloc(sizeof(Evento) * jogos_count);
  while(valido == 1) {
    printf("\n");
    printf("Escolha uma opção:\n");
    printf("1- Cadastrar novo evento\n");
    printf("2- Mostrar todos eventos\n");
    printf("3- Mostrar eventos em data\n");
    printf("4- Mostart eventos com descricao\n");
    printf("5- Remover evento\n");
    scanf("%d", &escolha);

    switch(escolha) {
      case 1:
        jogos = adiciona_evento(jogos, &jogos_count);
        break; 

      case 2:
        if(jogos_count > 0) {
          for(i = 0;i < jogos_count;i++)
            printa_evento(&jogos[i]);
        } else {
          printf("Lista de jogos vazia.\n");
        }
        break;

      case 3:
        if(jogos_count > 0) {
          Data *data_pesquisa;
          data_pesquisa = le_data();
          for(i = 0;i < jogos_count;i++){
            if(verifica_data(*jogos[i].data_jogo, *data_pesquisa))
              printa_evento(&jogos[i]);
          }
        } else {
          printf("Lista de jogos vazia.\n");
        }
        break;

      case 4:
        if(jogos_count > 0) {
          char desc_pesquisa[10]; 
          printf("Digite a descricao que deseja buscar:");
          fflush(stdin);
          fgets(desc_pesquisa, 10, stdin);
          for(i = 0;i < jogos_count;i++){
            if(strcmp(jogos[i].descricao, desc_pesquisa) == 0)
              printa_evento(&jogos[i]);
          }
        } else {
          printf("Lista de jogos vazia.\n");
        }
        break;

      case 5:
        if (jogos_count > 0) {
          Data *data_exclusao;
          Horario *horario_exclusao;
          printf("Digite que evento deseja excluir:");
          data_exclusao = le_data();
          printf("Digite horario do evento:");
          horario_exclusao = le_horario();

          int index_remover = -1;
          for(i = 0;i < jogos_count;i++){
            if(verifica_data(*jogos[i].data_jogo, *data_exclusao) && verifica_horario(*jogos[i].horario_inicio, *horario_exclusao)){
              index_remover = i;
            }
          }

          if(index_remover != -1) {
            free(jogos[index_remover].data_jogo);
            free(jogos[index_remover].horario_inicio);
            free(jogos[index_remover].horario_fim);

            for (i = index_remover; i < jogos_count - 1; i++) {
                jogos[i] = jogos[i + 1];
            }

            jogos_count--;
            jogos = realloc(jogos, sizeof(Evento) * jogos_count);
          } else {
            printf("Evento não encontrado.\n");
          }

        } else {
          printf("Lista vazia.\n");
        }
        break;

      default:
        printf("Opção Invalida");
        valido = 0;
      break;
    }
  }

  free(jogos);
  return 0;
}
