#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "terminal_colors.h"

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
    printf("1. Carregar matriz de antenas (ficheiro .txt)\n");
    printf("2. Detetar efeitos nefastos\n");
    printf("3. Imprimir matriz (sem efeitos)\n");
    printf("4. Imprimir matriz (com efeitos)\n");
    printf("5. Inserir nova antena\n");
    printf("6. Remover antena\n");
    printf("7. Guardar lista de antenas em binário\n");
    printf("8. Guardar lista de efeitos em binário\n");
    printf("9. Sair\n");
    printf("--------------------------\n");
    printf("Escolha uma opção: ");
    scanf("%d", &option);

    return option;
}