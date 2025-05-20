#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "io/graph_io.h"
#include "core/constants.h"

int graph_load_from_txt(const char *filepath, GR *g)
{
  if (!filepath || !g)
    return 0;

  FILE *fp = fopen(filepath, "r");
  if (!fp)
    return 0;

  char line[MAX_LINE_LENGTH];
  int y = 0;

  while (fgets(line, sizeof(line), fp))
  {
    size_t len = strlen(line);

    // Remover newline, se existir
    if (len > 0 && line[len - 1] == '\n')
      line[len - 1] = '\0';

    for (int x = 0; line[x] != '\0'; x++)
    {
      char c = line[x];

      if (isalpha(c))
      {
        Vertex *v = graph_create_vertex(c, x, y);
        if (!v || !graph_add_vertex(g, v))
        {
          fclose(fp);
          return 0;
        }
      }
    }

    y++;
  }

  fclose(fp);
  return 1;
}

int graph_save_to_bin(const char *filepath, const GR *g)
{
  if (!filepath || !g)
    return 0;

  FILE *fp = fopen(filepath, "wb");
  if (!fp)
    return 0;

  fwrite(&g->vertex_count, sizeof(int), 1, fp);

  for (Vertex *v = g->head; v; v = v->next)
  {
    fwrite(&v->frequency, sizeof(char), 1, fp);
    fwrite(&v->x, sizeof(int), 1, fp);
    fwrite(&v->y, sizeof(int), 1, fp);

    int adj_count = 0;
    for (Adj_Node *adj = v->adj_list; adj; adj = adj->next)
      adj_count++;

    fwrite(&adj_count, sizeof(int), 1, fp);

    for (Adj_Node *adj = v->adj_list; adj; adj = adj->next)
    {
      int dx = adj->dest->x;
      int dy = adj->dest->y;
      fwrite(&dx, sizeof(int), 1, fp);
      fwrite(&dy, sizeof(int), 1, fp);
    }

    // Escreve marcador de fim do vértice
    int marker = VERTEX_END_MARKER;
    fwrite(&marker, sizeof(int), 1, fp);
  }

  fclose(fp);
  return 1;
}

GR *graph_load_from_bin(const char *filepath)
{
  if (!filepath)
    return NULL;

  FILE *fp = fopen(filepath, "rb");
  if (!fp)
    return NULL;

  GR *g = graph_create();
  if (!g)
  {
    fclose(fp);
    return NULL;
  }

  int vertex_count;
  if (fread(&vertex_count, sizeof(int), 1, fp) != 1)
  {
    fclose(fp);
    graph_free(g);
    return NULL;
  }

  for (int i = 0; i < vertex_count; i++)
  {
    char freq;
    int x, y;

    if (fread(&freq, sizeof(char), 1, fp) != 1 ||
        fread(&x, sizeof(int), 1, fp) != 1 ||
        fread(&y, sizeof(int), 1, fp) != 1)
    {
      fclose(fp);
      graph_free(g);
      return NULL;
    }

    Vertex *v = graph_create_vertex(freq, x, y);
    if (!v || !graph_add_vertex(g, v))
    {
      fclose(fp);
      graph_free(g);
      return NULL;
    }

    int adj_count;
    if (fread(&adj_count, sizeof(int), 1, fp) != 1)
    {
      fclose(fp);
      graph_free(g);
      return NULL;
    }

    for (int j = 0; j < adj_count; j++)
    {
      int dx, dy;
      if (fread(&dx, sizeof(int), 1, fp) != 1 ||
          fread(&dy, sizeof(int), 1, fp) != 1)
      {
        fclose(fp);
        graph_free(g);
        return NULL;
      }

      Vertex *to = graph_find_vertex(g, dx, dy);
      if (to)
      {
        graph_add_edge(v, to);
        graph_add_edge(to, v); // <- garantir ser bidirecional
      }
    }

    // Validar marcador de fim do vértice
    int marker;
    if (fread(&marker, sizeof(int), 1, fp) != 1 || marker != VERTEX_END_MARKER)
    {
      fclose(fp);
      graph_free(g);
      return NULL;
    }
  }

  fclose(fp);
  return g;
}
