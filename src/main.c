/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-03-23
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <stdio.h>
#include "ed_io.h"
#include "menu.h"
#include "controller.h"

/**
 * @brief Ponto de entrada da aplicação
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char const *argv[])
{
    int option;
    do
    {
        clear_screen();
        option = show_main_menu();

        switch (option)
        {
        case 1:
            // char path[MAX_FILENAME_LENGTH];
            // printf("Caminho do ficheiro: ");
            // scanf("%s", path);
            if (load_map(DEFAULT_MATRIX_PATH))
                printf(ANSI_GREEN "[✓] Mapa carregado com sucesso!\n" ANSI_RESET);
            else
                printf(ANSI_RED "[X] Erro ao carregar mapa!\n" ANSI_RESET);
            break;
        case 2:
            int effects_count = generate_effects();
            if (effects_count > 0)
                printf(ANSI_YELLOW "[!] Foram detectados %d efeitos nefastos!\n" ANSI_RESET, effects_count);
            else if (effects_count == 0)
            {
                printf(ANSI_GREEN "[✓] Não foram detectados efeitos nefastos!\n" ANSI_RESET);
            }
            else
                printf(ANSI_RED "[X] Erro ao detectar efeitos nefastos!\n" ANSI_RESET);
            break;
            // case 2:
            //     show_antennas();
            break;
        case 3:
            show_effects();
            break;
        case 4:
            // Inserir nova antena
            char freq;
            int x, y;
            printf("Frequência: ");
            scanf(" %c", &freq);
            printf("Coordenadas (x y): ");
            scanf("%d %d", &x, &y);
            if (insert_antenna(freq, x, y))
                printf(ANSI_GREEN "[✓] Antena inserida com sucesso!\n" ANSI_RESET);
            else
                printf(ANSI_RED "[X] Erro ao inserir antena!\n" ANSI_RESET);
            break;

        case 5:
            // Remover antena
            int x1, y1;
            printf("Coordenadas (x y): ");
            scanf("%d %d", &x1, &y1);
            if (remove_antenna(x1, y1))
                printf(ANSI_GREEN "[✓] Antena removida com sucesso!\n" ANSI_RESET);
            else
                printf(ANSI_RED "[X] Erro ao remover antena!\n" ANSI_RESET);
            break;

        case 6:
            char path[MAX_FILENAME_LENGTH];
            printf("Caminho do ficheiro: ");
            scanf("%s", path);
            if (load_project(path))
                printf(ANSI_GREEN "[✓] Projeto carregado com sucesso!\n" ANSI_RESET);
            else
                printf(ANSI_RED "[X] Erro ao carregar projeto!\n" ANSI_RESET);
            break;
            break;

        case 7:
            char path2[MAX_FILENAME_LENGTH];
            printf("Caminho do ficheiro: ");
            scanf("%s", path2);
            if (save_project(path2))
                printf(ANSI_GREEN "[✓] Projeto guardado com sucesso!\n" ANSI_RESET);
            else
                printf(ANSI_RED "[X] Erro ao guardar projeto!\n" ANSI_RESET);
            break;

        case 0:
            printf("A sair...\n");
            break;

        default:
            printf("Opção inválida.\n");
        }

        if (option != 0)
        {
            printf("\nPrima Enter para continuar...");
            getchar();
            getchar(); // limpa buffer
        }

    } while (option != 0);

    if (antennas)
        free_ed_list(&antennas);
    if (effects)
        free_ed_list(&effects);

    return 0;
}
