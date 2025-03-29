#include "ed_io.h"
#include "constants.h"
#include "terminal_colors.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

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

#pragma endregion Public_Functions
