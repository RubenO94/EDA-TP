#include "core/graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// =========================
// CRIAÇÃO
// =========================

GR *graph_create()
{
  GR *g = malloc(sizeof(GR));
  if (!g)
    return NULL;

  g->head = NULL;
  g->vertex_count = 0;
  return g;
}

Vertex *graph_create_vertex(char frequency, int x, int y)
{
  Vertex *v = malloc(sizeof(Vertex));
  if (!v)
    return NULL;

  v->frequency = frequency;
  v->x = x;
  v->y = y;
  v->visited = 0;
  v->adj_list = NULL;
  v->next = NULL;

  return v;
}

// =========================
// INSERÇÃO E ESTRUTURAÇÃO
// =========================

int graph_add_vertex(GR *g, Vertex *v)
{
  if (!g || !v)
    return 0;

  if (graph_find_vertex(g, v->x, v->y))
    return 0;

  // Inserção ordenada por y, depois x
  if (!g->head || (v->y < g->head->y || (v->y == g->head->y && v->x < g->head->x)))
  {
    v->next = g->head;
    g->head = v;
  }
  else
  {
    Vertex *curr = g->head;
    while (curr->next &&
           (curr->next->y < v->y || (curr->next->y == v->y && curr->next->x < v->x)))
    {
      curr = curr->next;
    }
    v->next = curr->next;
    curr->next = v;
  }

  g->vertex_count++;
  return 1;
}

int graph_add_edge(Vertex *from, Vertex *to)
{
  if (!from || !to || from == to)
    return 0;
  if (from->frequency != to->frequency)
    return 0;
  if (graph_has_edge(from, to))
    return 0;

  Adj_Node *new_edge = malloc(sizeof(Adj_Node));
  if (!new_edge)
    return 0;

  new_edge->dest = to;
  new_edge->next = NULL;

  if (!from->adj_list ||
      (to->y < from->adj_list->dest->y ||
       (to->y == from->adj_list->dest->y && to->x < from->adj_list->dest->x)))
  {
    new_edge->next = from->adj_list;
    from->adj_list = new_edge;
  }
  else
  {
    Adj_Node *curr = from->adj_list;
    while (curr->next &&
           (curr->next->dest->y < to->y ||
            (curr->next->dest->y == to->y && curr->next->dest->x < to->x)))
    {
      curr = curr->next;
    }
    new_edge->next = curr->next;
    curr->next = new_edge;
  }

  return 1;
}

int graph_connect_adjacent_nodes(GR *g)
{
  if (!g)
    return 0;

  for (Vertex *v = g->head; v; v = v->next)
  {
    for (int dy = -1; dy <= 1; dy++)
    {
      for (int dx = -1; dx <= 1; dx++)
      {
        if (dx == 0 && dy == 0)
          continue;

        int nx = v->x + dx;
        int ny = v->y + dy;

        Vertex *neighbor = graph_find_vertex(g, nx, ny);
        if (neighbor &&
            neighbor->frequency == v->frequency &&
            !graph_has_edge(v, neighbor))
        {
          graph_add_edge(v, neighbor);
          graph_add_edge(neighbor, v);
        }
      }
    }
  }

  return 1;
}

// =========================
// BUSCAS E CONSULTAS
// =========================

Vertex *graph_find_vertex(GR *g, int x, int y)
{
  if (!g)
    return NULL;

  for (Vertex *curr = g->head; curr; curr = curr->next)
  {
    if (curr->x == x && curr->y == y)
      return curr;
  }

  return NULL;
}

int graph_has_edge(Vertex *from, Vertex *to)
{
  if (!from || !to)
    return 0;

  for (Adj_Node *adj = from->adj_list; adj; adj = adj->next)
  {
    if (adj->dest == to)
      return 1;
  }

  return 0;
}

// =========================
// VALIDAÇÃO
// =========================

int graph_validate_vertex(GR *g, char frequency, int x, int y)
{
  if (!isalpha(frequency))
    return INVALID_FREQUENCY;
  if (x < 0 || y < 0)
    return INVALID_COORDINATES;
  if (graph_find_vertex(g, x, y))
    return DUPLICATE_VERTEX;
  return VALID;
}

// =========================
// UTILITÁRIOS
// =========================

int graph_clear_visits(GR *g)
{
  if (!g)
    return 0;

  for (Vertex *v = g->head; v; v = v->next)
    v->visited = 0;

  return 1;
}

int graph_free(GR *g)
{
  if (!g)
    return 0;

  Vertex *v = g->head;
  while (v)
  {
    Vertex *next_v = v->next;

    Adj_Node *adj = v->adj_list;
    while (adj)
    {
      Adj_Node *next_adj = adj->next;
      free(adj);
      adj = next_adj;
    }

    free(v);
    v = next_v;
  }

  free(g);
  return 1;
}

void graph_print(GR *g)
{
  if (!g)
    return;

  for (Vertex *v = g->head; v; v = v->next)
  {
    printf("(%d, %d) [%c] ->", v->x, v->y, v->frequency);
    for (Adj_Node *adj = v->adj_list; adj; adj = adj->next)
    {
      printf("\t(%d,%d)", adj->dest->x, adj->dest->y);
    }
    printf("\n");
  }
}

void graph_print_vertices(Vertex *list)
{
  for (Vertex *v = list; v; v = v->next)
  {
    printf("Visitado: (%d, %d) [%c]\n", v->x, v->y, v->frequency);
  }
}
