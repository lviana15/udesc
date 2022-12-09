#include <stdio.h>

int main() {
    int opcaoServico;
    char nome[50];
    char animal[50];
    char data[10];
    char medicamento[30];
    char telefone[13];

    printf("Nome do cliente:");
    scanf("%s", nome);

    printf("Escolha o serviço: ");
    printf("\n 1 - Vacina");
    printf("\n 2 - Castração");
    printf("\n 3 - Venda de ração");
    printf("\n 4 - Medicamentos");

    scanf("%i", opcaoServico);
    switch (opcaoServico)
    {
    case 1:
        
        break;
    
    default:
        break;
    }
}