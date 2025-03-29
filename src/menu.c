#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int show_main_menu()
{
    int option;

    printf(ANSI_BOLD "\n=== MENU PRINCIPAL ===\n" ANSI_RESET);
    printf("1. Carregar matriz (.txt)\n");
    printf("2. Detetar efeitos nefastos\n");
    printf("3. Mostrar matriz\n");
    printf("4. Inserir antena\n");
    printf("5. Remover antena\n");
    printf("6. Carregar Projeto\n");
    printf("7. Guardar Projeto\n");
    printf("0. Sair\n");
    printf("--------------------------\n");
    printf("Escolha uma opção: ");
    scanf("%d", &option);

    return option;
}