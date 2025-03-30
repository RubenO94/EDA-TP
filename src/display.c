#include <stdio.h>
#include "display.h"
#include "constants.h"

#pragma region Private_Functions_Definition
static void print_horizontal_border_top(int cols);
static void print_horizontal_border_mid(int cols);
static void print_horizontal_border_bottom(int cols);
static void print_cell_symbol(ED *antennas, ED *effects, int x, int y, int with_effects);
static void print_matrix_rules_summary();

#pragma endregion

void print_matrix(ED *antennas, ED *effects, Dimensions *dim, PrintMode mode)
{
    if (!dim || dim->rows <= 0 || dim->cols <= 0)
    {
        printf(ANSI_RED "[X] Dimensões inválidas.\n" ANSI_RESET);
        return;
    }

    int with_effects = (mode == PRINT_WITH_EFFECTS && effects != NULL);

    // Contadores
    int total_antennas = 0, total_effects = 0;
    for (ED *a = antennas; a; a = a->next)
        total_antennas++;
    if (with_effects)
        for (ED *e = effects; e; e = e->next)
            total_effects++;

    // Cabeçalho informativo
    printf(ANSI_BOLD "\n📡 TABULEIRO DE ANTENAS E EFEITOS\n" ANSI_RESET);
    printf("Dimensões: %d linhas × %d colunas\n", dim->rows, dim->cols);
    printf("Total de antenas: " ANSI_GREEN "%d\n" ANSI_RESET, total_antennas);
    if (with_effects)
        printf("Total de efeitos: " ANSI_RED "%d\n" ANSI_RESET, total_effects);

    // Regras
    print_matrix_rules_summary();

    // Legenda
    printf("\nLegenda:\n");
    printf(ANSI_GREEN "  A" ANSI_RESET " = Antena  | ");
    printf(ANSI_RED "#  " ANSI_RESET " = Efeito  | ");
    printf(ANSI_YELLOW "#A " ANSI_RESET "= Efeito + Antena  | ");
    printf(".  = Vazio\n\n");

    // Cabeçalho das colunas
    printf("    ");
    for (int x = 0; x < dim->cols; x++)
    {
        printf("%4d", x);
    }
    printf("\n");

    print_horizontal_border_top(dim->cols);

    for (int y = 0; y < dim->rows; y++)
    {
        printf("%4d │", y); // Número da linha com separador

        for (int x = 0; x < dim->cols; x++)
        {
            print_cell_symbol(antennas, effects, x, y, with_effects);
        }
        printf("\n");
        if (y == dim->rows - 1)
            print_horizontal_border_bottom(dim->cols);
        else
            print_horizontal_border_mid(dim->cols);
    }

    printf("\n");
}

#pragma region Private_Functions

static void print_cell_symbol(ED *antennas, ED *effects, int x, int y, int with_effects)
{
    const ED *ant = find_ed(antennas, x, y);
    const ED *ef = with_effects ? find_ed(effects, x, y) : NULL;

    char cell[4] = " . "; // Valor por defeito

    if (ef && ant)
        snprintf(cell, sizeof(cell), "#%c", ant->frequency);
    else if (ef)
        snprintf(cell, sizeof(cell), " #");
    else if (ant)
        snprintf(cell, sizeof(cell), " %c", ant->frequency);

    if (ef && ant)
        printf(ANSI_BOLD ANSI_YELLOW "%-3s" ANSI_RESET "│", cell);
    else if (ef)
        printf(ANSI_BOLD ANSI_RED "%-3s" ANSI_RESET "│", cell);
    else if (ant)
        printf(ANSI_BOLD ANSI_GREEN "%-3s" ANSI_RESET "│", cell);
    else
        printf("%-3s│", cell);
}

void print_horizontal_border_top(int cols)
{
    printf("     ┌");
    for (int i = 0; i < cols - 1; i++)
        printf("───┬");
    printf("───┐\n");
}

void print_horizontal_border_mid(int cols)
{
    printf("     ├");
    for (int i = 0; i < cols - 1; i++)
        printf("───┼");
    printf("───┤\n");
}

void print_horizontal_border_bottom(int cols)
{
    printf("     └");
    for (int i = 0; i < cols - 1; i++)
        printf("───┴");
    printf("───┘\n");
}
static void print_matrix_rules_summary()
{
    // Regras e contexto
    printf("\n📏 Regras:\n");
    printf("- Antenas com a mesma frequência devem manter pelo menos %d casas de distância\n", MIN_EFFECT_DISTANCE);
    printf("- Se a distância for menor, será criado um efeito '%c' a essa distância para fora de cada antena\n", EFFECT_SYMBOL);

    printf("- Efeitos podem coexistir com antenas na mesma posição (ex: " ANSI_YELLOW "#A" ANSI_RESET ")\n");
}

#pragma endregion Private_Functions