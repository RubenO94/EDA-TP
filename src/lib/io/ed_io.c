#include "io/ed_io.h"
#include "io/ed_validator.h"
#include "core/constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int load_ed_list_from_bin(FILE *fp, ED **head);
static int save_ed_list_to_bin(FILE *fp, const ED *head);

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

      if (is_valid_frequency(ch) && !find_ed(*head, col, row))
      {
        ED *node = create_ed(ch, col, row);
        if (!node || !insert_ed(head, node))
        {
          free(node);
          fclose(file);
          return 0;
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

int save_all_to_bin(ED *antennas, ED *effects, Dimensions *dim, const char *filepath)
{
  if (!antennas || !dim || !filepath)
    return 0;
  FILE *fp = fopen(filepath, "wb");
  if (!fp)
    return 0;

  // Guardar dimensões
  fwrite(&(dim->rows), sizeof(int), 1, fp);
  fwrite(&(dim->cols), sizeof(int), 1, fp);

  // Guardar antenas & Efeitos
  if (!save_ed_list_to_bin(fp, antennas) ||
      !save_ed_list_to_bin(fp, effects))
  {
    fclose(fp);
    return 0;
  }

  fclose(fp);
  return 1;
}

int load_all_from_bin(ED **antennas, ED **effects, Dimensions *dim, const char *filepath)
{
  if (!antennas || !effects || !dim || !filepath)
    return 0;

  FILE *fp = fopen(filepath, "rb");
  if (!fp)
    return 0;

  // Limpar listas anteriores
  if (*antennas)
    free_ed_list(antennas);
  if (*effects)
    free_ed_list(effects);

  fread(&(dim->rows), sizeof(int), 1, fp);
  fread(&(dim->cols), sizeof(int), 1, fp);

  if (!load_ed_list_from_bin(fp, antennas) ||
      !load_ed_list_from_bin(fp, effects))
  {
    fclose(fp);
    return 0;
  }

  fclose(fp);
  return 1;
}

static int load_ed_list_from_bin(FILE *fp, ED **head)
{
  int count;
  if (fread(&count, sizeof(int), 1, fp) != 1)
    return 0;

  for (int i = 0; i < count; i++)
  {
    char f;
    int x, y;
    if (fread(&f, sizeof(char), 1, fp) != 1 ||
        fread(&x, sizeof(int), 1, fp) != 1 ||
        fread(&y, sizeof(int), 1, fp) != 1)
    {
      return 0;
    }

    ED *node = create_ed(f, x, y);
    if (!node || !insert_ed(head, node))
    {
      free(node);
      return 0;
    }
  }

  return 1;
}

static int save_ed_list_to_bin(FILE *fp, const ED *head)
{
  int count = 0;
  for (const ED *cur = head; cur; cur = cur->next)
    count++;

  if (fwrite(&count, sizeof(int), 1, fp) != 1)
    return 0;

  for (const ED *cur = head; cur; cur = cur->next)
  {
    if (fwrite(&(cur->frequency), sizeof(char), 1, fp) != 1 ||
        fwrite(&(cur->x), sizeof(int), 1, fp) != 1 ||
        fwrite(&(cur->y), sizeof(int), 1, fp) != 1)
    {
      return 0;
    }
  }

  return 1;
}
