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

#include "core/graph.h"
#include <stdio.h>
#include <malloc.h>
#include <ctype.h>

// === Criação e validação ===

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
  v->adj_list = NULL;
  v->next = NULL;

  return v;
}

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

Vertex *graph_find_vertex(GR *g, int x, int y)
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

int graph_add_vertex(GR *g, Vertex *v)
{
  if (!g || !v)
    return 0;

  if (graph_find_vertex(g, v->x, v->y))
    return 0;

  // Caso 1: lista vazia
  if (!g->head)
  {
    g->head = v;
    g->vertex_count++;
    return 1;
  }

  // Caso 2: inserir no início (antes do head atual)
  if (v->y < g->head->y || (v->y == g->head->y && v->x < g->head->x))
  {
    v->next = g->head;
    g->head = v;
    g->vertex_count++;
    return 1;
  }

  // Caso 3: inserir no meio ou fim
  Vertex *curr = g->head;
  while (curr->next &&
         (curr->next->y < v->y || (curr->next->y == v->y && curr->next->x < v->x)))
  {
    curr = curr->next;
  }

  v->next = curr->next;
  curr->next = v;
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
  // Validações
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

  // Caso 1: lista de adjacência vazia
  if (!from->adj_list)
  {
    from->adj_list = new_edge;
    return 1;
  }

  // Caso 2: inserir no início
  if (to->y < from->adj_list->dest->y ||
      (to->y == from->adj_list->dest->y && to->x < from->adj_list->dest->x))
  {
    new_edge->next = from->adj_list;
    from->adj_list = new_edge;
    return 1;
  }

  // Caso 3: inserir no meio ou fim
  Adj_Node *curr = from->adj_list;
  while (curr->next &&
         (curr->next->dest->y < to->y ||
          (curr->next->dest->y == to->y && curr->next->dest->x < to->x)))
  {
    curr = curr->next;
  }

  new_edge->next = curr->next;
  curr->next = new_edge;

  return 1;
}
