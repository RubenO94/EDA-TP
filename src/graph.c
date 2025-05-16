/**
 * @file graph.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-05-16
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "graph.h"
#include "stdio.h"
#include "malloc.h"
#include <ctype.h>

// === Criação e validação ===

Graph *graph_create()
{
  Graph *g = malloc(sizeof(Graph));
  if (!g)
    return NULL;

  g->head = NULL;
  g->vertex_count = 0;
  return g;
}

Vertex *graph_create_vertex(char frequency, int x, int y)
{
  if (!isalpha(frequency) || x < 0 || y < 0)
    return NULL;

  Vertex *v = malloc(sizeof(Vertex));
  if (!v)
    return NULL;

  v->frequency = frequency;
  v->x = x;
  v->y = y;
  v->adj_list = NULL;
  v->next = NULL;

  return v;
}

int graph_validate_vertex(Graph *g, char frequency, int x, int y)
{
  if (!isalpha(frequency))
    return INVALID_FREQUENCY;
  if (x < 0 || y < 0)
    return INVALID_COORDINATES;
  if (graph_find_vertex(g, x, y))
    return DUPLICATE_VERTEX;
  return VALID;
}

Vertex *graph_find_vertex(Graph *g, int x, int y)
{
  if (!g)
    return NULL;

  Vertex *curr = g->head;
  while (curr)
  {
    if (curr->x == x && curr->y == y)
      return curr;
    curr = curr->next;
  }
  return NULL;
}

int graph_add_vertex(Graph *g, Vertex *v)
{
  if (!g || !v)
    return 0;

  if (graph_find_vertex(g, v->x, v->y))
    return 0;

  // Inserir ordenado por coordenadas: primeiro Y, depois X
  Vertex **curr = &g->head;
  while (*curr && ((*curr)->y < v->y || ((*curr)->y == v->y && (*curr)->x < v->x)))
  {
    curr = &((*curr)->next);
  }

  v->next = *curr;
  *curr = v;
  g->vertex_count++;
  return 1;
}

int graph_has_edge(Vertex *from, Vertex *to)
{
  if (!from || !to)
    return 0;

  Adj_Node *adj = from->adj_list;
  while (adj)
  {
    if (adj->dest == to)
      return 1;
    adj = adj->next;
  }
  return 0;
}

Adj_Node *graph_create_edge(Vertex *dest)
{
  if (!dest)
    return NULL;

  Adj_Node *edge = malloc(sizeof(Adj_Node));
  if (!edge)
    return NULL;

  edge->dest = dest;
  edge->next = NULL;
  return edge;
}

int graph_add_edge(Vertex *from, Vertex *to)
{
  if (!from || !to)
    return 0;
  if (from == to)
    return 0;
  if (from->frequency != to->frequency)
    return 0;
  if (graph_has_edge(from, to))
    return 0;

  Adj_Node *new_edge = graph_create_edge(to);
  if (!new_edge)
    return 0;

  new_edge->dest = to;
  new_edge->next = NULL;

  // Inserir de forma ordenada na lista de adjacências (por y, depois x)
  Adj_Node **curr = &from->adj_list;
  while (*curr && ((*curr)->dest->y < to->y ||
                   ((*curr)->dest->y == to->y && (*curr)->dest->x < to->x)))
  {
    curr = &((*curr)->next);
  }

  new_edge->next = *curr;
  *curr = new_edge;

  return 1;
}
