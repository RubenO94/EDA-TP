#include "core/graph.h"
#include "core/algorithms.h"
#include "core/constants.h"
#include "utils/queue.h"
#include <stdio.h>
#include <stdlib.h>

Vertex *graph_bfs(Vertex *start)
{
  if (!start)
    return NULL;

  Queue *q = queue_create();
  if (!q)
    return NULL;

  Vertex *visit_list = NULL;
  Vertex *visit_tail = NULL;

  queue_enqueue(q, start);
  start->visited = 1;

  while (!queue_is_empty(q))
  {
    Vertex *current;
    queue_dequeue(q, &current);

    // Criar uma cópia para a lista de visitados
    Vertex *copy = graph_create_vertex(current->frequency, current->x, current->y);
    if (!visit_list)
    {
      visit_list = visit_tail = copy;
    }
    else
    {
      visit_tail->next = copy;
      visit_tail = copy;
    }

    for (Adj_Node *adj = current->adj_list; adj; adj = adj->next)
    {
      Vertex *neighbor = adj->dest;

      if (neighbor->frequency != start->frequency)
        continue;
      if (neighbor->visited)
        continue;

      neighbor->visited = 1;
      queue_enqueue(q, neighbor);
    }
  }

  queue_free(q);
  return visit_list;
}

// Função auxiliar recursiva
static Vertex *dfs_recursive(Vertex *v, char target_freq, Vertex **tail)
{
  if (!v || v->visited || v->frequency != target_freq)
    return NULL;

  v->visited = 1;

  Vertex *copy = graph_create_vertex(v->frequency, v->x, v->y);
  if (!copy)
    return NULL;

  // Se é o primeiro da lista, retorna como head
  if (*tail == NULL)
  {
    *tail = copy;
  }
  else
  {
    (*tail)->next = copy;
    *tail = copy;
  }

  for (Adj_Node *adj = v->adj_list; adj; adj = adj->next)
  {
    dfs_recursive(adj->dest, target_freq, tail);
  }

  return copy;
}

Vertex *graph_dfs(Vertex *start)
{
  if (!start)
    return NULL;

  Vertex *head = NULL;
  Vertex *tail = NULL;

  head = dfs_recursive(start, start->frequency, &tail);

  return head;
}
