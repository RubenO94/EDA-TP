/**
 * @file menu.c
 * @author Rúben Oliveira
 * @brief Implementação do menu principal da aplicação.
 * @version 1.0
 * @date 2025-03-29
 *
 * Permite a interação com o utilizador para inserir/remover antenas,
 * carregar ou guardar projetos e visualizar a matriz.
 */

#include "menu.h"
#include "controller.h"
#include "terminal_colors.h"
#include "constants.h"
#include <stdio.h>
#include <stdlib.h>

#pragma region Private_Functions_Declaration

/**
 * @brief Pausa a execução do programa
 *
 */
static void pause(int after_scan);

/**
 * @brief Limpa o ecrã do terminal (suporte multiplataforma).
 */
static void clear_screen();

/**
 * @brief Menu para inserção de uma nova antena.
 */
static void menu_insert_antenna();

/**
 * @brief Menu para remoção de uma antena existente.
 */
static void menu_remove_antenna();

/**
 * @brief Menu para carregar um projeto binário.
 */
static void menu_load_project();

/**
 * @brief Menu para guardar o estado atual num ficheiro binário.
 */
static void menu_save_project();

#pragma endregion

#pragma region Public_Functions

void start_menu()
{
    int opcao;

    load_map(DEFAULT_MATRIX_PATH); // Carrega mapa inicial

    do
    {
        clear_screen();
        show_matrix();

        printf(ANSI_BOLD "\n=== MENU PRINCIPAL ===\n" ANSI_RESET);
        printf("1. Inserir antena\n");
        printf("2. Remover antena\n");
        printf("3. Carregar projeto\n");
        printf("4. Guardar projeto\n");
        printf("0. Sair\n");

        printf("Opção: ");
        if (scanf("%d", &opcao) != 1)
        {
            printf(ANSI_RED "[X] Entrada inválida! Insira um número.\n" ANSI_RESET);
            // while (getchar() != '\n')
            //     ;
            pause(1);
            opcao = -1;
            continue;
        }

        while (getchar() != '\n')
            ; // Limpar buffer de entrada

        switch (opcao)
        {
        case 1:
            menu_insert_antenna();
            break;
        case 2:
            menu_remove_antenna();
            break;
        case 3:
            menu_load_project();
            break;
        case 4:
            menu_save_project();
            break;
        case 0:
            printf("A sair...\n");
            break;
        default:
            printf(ANSI_RED "[!] Opção inválida." ANSI_RESET);
            pause(0);
        }

    } while (opcao != 0);

    // Libertar memória
    free_ed_list(&antennas);
    free_ed_list(&effects);
}

#pragma endregion

#pragma region Private_Functions

static void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

static void pause(int after_scan)
{
    if (after_scan)
        while (getchar() != '\n')
            ;

    printf("\nPrima ENTER para continuar...");
    getchar();
}

static void menu_insert_antenna()
{
    char freq;
    int x, y;

    printf("Frequência: ");
    scanf(" %c", &freq);

    printf("Coordenadas (x y): ");
    scanf("%d %d", &x, &y);

    int result = insert_antenna(freq, x, y);
    if (result >= 0)
    {
        printf(ANSI_GREEN "[✓] Antena inserida com sucesso!\n" ANSI_RESET);
        if (result > 0)
            printf(ANSI_YELLOW "[!]  Foram gerados %d efeito(s) nefasto(s).\n" ANSI_RESET, result);
    }
    else
    {
        printf(ANSI_RED "[X] Erro ao inserir antena.\n" ANSI_RESET);
    }
    pause(1);
}

static void menu_remove_antenna()
{
    int x, y;

    printf("Coordenadas da antena a remover (x y): ");
    scanf("%d %d", &x, &y);

    int result = remove_antenna(x, y);
    if (result >= 0)
    {
        printf(ANSI_GREEN "[✓] Antena removida com sucesso!\n" ANSI_RESET);
        if (result > 0)
            printf(ANSI_GREEN "[✓] Foram removidos %d efeito(s) nefasto(s).\n" ANSI_RESET, result);
    }
    else
    {
        printf(ANSI_RED "[X] Erro ao remover antena.\n" ANSI_RESET);
    }
    pause(1);
}

static void menu_load_project()
{
    char path[MAX_PATH];

    printf("Caminho do ficheiro a carregar: ");
    scanf("%s", path);

    if (load_project(path))
        printf(ANSI_GREEN "[✓] Projeto carregado com sucesso!\n" ANSI_RESET);
    else
        printf(ANSI_RED "[X] Erro ao carregar projeto.\n" ANSI_RESET);
    pause(1);
}

static void menu_save_project()
{
    char path[MAX_PATH];

    printf("Caminho do ficheiro para guardar: ");
    scanf("%s", path);

    if (save_project(path))
        printf(ANSI_GREEN "[✓] Projeto guardado com sucesso!\n" ANSI_RESET);
    else
        printf(ANSI_RED "[X] Erro ao guardar projeto.\n" ANSI_RESET);
    pause(1);
}

#pragma endregion
