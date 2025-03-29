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
#include "effect.h"
#include "display.h"
#include "menu.h"

/**
 * @brief Ponto de entrada da aplicação
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char const *argv[])
{
    ED *antennas = NULL;
    ED *effects = NULL;
    Dimensions dim = {0};

    int option;
    do
    {
        clear_screen();
        option = show_main_menu();

        switch (option)
        {
        case 1:
            load_matrix(DEFAULT_MATRIX_PATH, &antennas, &dim);
            break;
        case 2:
            detect_effects(antennas, &dim, &effects);
            break;
        case 3:
            print_matrix(antennas, NULL, &dim, PRINT_ANTENNAS_ONLY);
            break;
        case 4:
            print_matrix(antennas, effects, &dim, PRINT_WITH_EFFECTS);
            break;
        case 5:
            // Inserir nova antena
            char freq;
            int x, y;
            printf("Frequência: ");
            scanf(" %c", &freq);
            printf("Coordenadas (x y): ");
            scanf("%d %d", &x, &y);

            if (is_within_bounds(x, y, &dim) && !find_ed(antennas, x, y))
            {
                ED *nova = create_ed(freq, x, y);
                if (nova && insert_ed(&antennas, nova))
                {
                    printf("Antena inserida com sucesso.\n");
                }
                else
                {
                    printf("Erro ao inserir.\n");
                    free_ed_list(&nova);
                }
            }
            else
            {
                printf("Coordenadas inválidas ou já ocupadas.\n");
            }
            break;

        case 6:
            // Remover antena
            printf("Coordenadas da antena a remover (x y): ");
            scanf("%d %d", &x, &y);
            if (remove_ed(&antennas, x, y))
                printf("Antena removida.\n");
            else
                printf("Antena não encontrada.\n");
            break;

        case 7:
            save_ed_to_bin(antennas, "antenas.bin");
            break;

        case 8:
            save_ed_to_bin(effects, "efeitos.bin");
            break;

        case 9:
            printf("A sair...\n");
            break;

        default:
            printf("Opção inválida.\n");
        }

        if (option != 9)
        {
            printf("\nPrima Enter para continuar...");
            getchar();
            getchar(); // limpa buffer
        }

    } while (option != 9);

    if (antennas)
        free_ed_list(&antennas);
    if (effects)
        free_ed_list(&effects);

    return 0;
}
