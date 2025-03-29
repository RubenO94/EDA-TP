#include "ed_io.h"
#include "constants.h"
#include "terminal_colors.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#pragma region Private_Functions_Definition

/**
 * @brief
 *
 * @param antennas
 * @param effects
 * @param x
 * @param y
 */
static void print_cell_symbol(ED *antennas, ED *effects, int x, int y, int with_effects);

#pragma endregion Private_Functions_Definition

#pragma region Public_Functions

int load_matrix(const char *filepath, ED **head, Dimensions *dim)
{
    if (!filepath || !head || !dim)
        return 0;

    FILE *file = fopen(filepath, "r");
    if (!file)
    {
        return 0;
    }

    char linha[MAX_LINE_LENGTH];
    int row = 0;
    int max_cols = 0;

    while (fgets(linha, sizeof(linha), file))
    {
        size_t len = strlen(linha);

        // Remover newline
        if (len > 0 && linha[len - 1] == '\n')
        {
            linha[len - 1] = '\0';
            len--;
        }

        for (int col = 0; col < len; col++)
        {
            char ch = linha[col];

            if (isalpha(ch))
            {
                // Verificar se já existe algo nesta coordenada
                if (!find_ed(*head, col, row))
                {
                    ED *node = create_ed(ch, col, row);
                    if (!node || !insert_ed(head, node))
                    {
                        free(node);
                        fclose(file);
                        return 0;
                    }
                }
            }

            if (col + 1 > max_cols)
                max_cols = col + 1;
        }

        row++;
    }

    fclose(file);

    // Guardar dimensões finais
    dim->rows = row;
    dim->cols = max_cols;

    return 1;
}

int save_ed_to_bin(ED *head, const char *filename)
{
    FILE *fp = fopen(filename, "wb");
    if (!fp)
        return 0;

    const ED *current = head;
    while (current != NULL)
    {
        fwrite(&(current->frequency), sizeof(char), 1, fp);
        fwrite(&(current->x), sizeof(int), 1, fp);
        fwrite(&(current->y), sizeof(int), 1, fp);
        current = current->next;
    }

    fclose(fp);
    return 1;
}

ED *load_ed_from_bin(const char *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (!fp)
        return NULL;

    ED *head = NULL;

    char freq;
    int x, y;

    while (fread(&freq, sizeof(char), 1, fp) == 1 &&
           fread(&x, sizeof(int), 1, fp) == 1 &&
           fread(&y, sizeof(int), 1, fp) == 1)
    {

        ED *node = create_ed(freq, x, y);
        if (!node)
        {
            free_ed_list(&head);
            fclose(fp);
            return NULL;
        }
        insert_ed(&head, node);
    }

    fclose(fp);
    return head;
}

void print_matrix(ED *antennas, ED *effects, Dimensions *dim, PrintMode mode)
{
    if (!dim || dim->rows <= 0 || dim->cols <= 0)
    {
        printf("[!] Dimensões inválidas.\n");
        return;
    }

    if (!antennas)
    {
        printf("[!] Não existem antenas carregadas.\n");
        return;
    }

    int with_effects = (mode == PRINT_WITH_EFFECTS && effects != NULL);

    // Cabeçalho das colunas
    printf("    "); // Espaço para alinhar com numeração das linhas
    for (int x = 0; x < dim->cols; x++)
    {
        printf("%3d", x); // Imprime cada número de coluna com 2 espaços
    }
    printf("\n");

    for (int y = 0; y < dim->rows; y++)
    {
        printf("%3d ", y); // Imprime número da linha

        for (int x = 0; x < dim->cols; x++)
        {
            print_cell_symbol(antennas, effects, x, y, with_effects);
        }
        printf("\n");
    }
}

#pragma endregion Public_Functions

#pragma region Private_Functions

static void print_cell_symbol(ED *antennas, ED *effects, int x, int y, int with_effects)
{
    const ED *ant = find_ed(antennas, x, y);
    const ED *ef = with_effects ? find_ed(effects, x, y) : NULL;

    if (ef && ant)
        printf(ANSI_BOLD ANSI_YELLOW " #%c" ANSI_RESET, ant->frequency); // Efeito + antena
    else if (ef)
        printf(ANSI_BOLD ANSI_RED "#  " ANSI_RESET); // Só efeito
    else if (ant)
        printf(ANSI_BOLD ANSI_GREEN "  %c" ANSI_RESET, ant->frequency); // Só antena
    else
        printf("  ."); // Vazio
}

#pragma endregion Private_Functions