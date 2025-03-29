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

/**
 * @brief Ponto de entrada da aplicação
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char const *argv[])
{
    // int option;
    Dimensions dim;
    ED *antennas = NULL;
    ED *effects = NULL;

    int res = load_matrix(DEFAULT_MATRIX_PATH, &antennas, &dim);

    if (res)
    {
        detect_effects(antennas, &dim, &effects);
        printf("ROWS: %d \t COLS: %d\n", dim.rows, dim.cols);
        print_matrix(antennas, effects, &dim, PRINT_WITH_EFFECTS);
    }
    else
    {
        printf("Erro ao carregar matriz");
        return 1;
    }

    // do {
    //     print_menu();
    //     scanf("%d", &option);
    //     handle_option(option, &antennas, &effects, &rows, &cols);
    // }
    // while (option != 7);
    if (antennas)
        free_ed_list(&antennas);
    if (effects)
        free_ed_list(&effects);

    return 0;
}
