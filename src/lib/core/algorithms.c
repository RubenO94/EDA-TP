#include "core/graph.h"
#include "core/algorithms.h"
#include "core/constants.h"
#include "utils/queue.h"
#include <stdio.h>
#include <stdlib.h>

// Funcoes Aux
static Vertex *dfs_recursive(Vertex *v, char target_freq);
int find_all_paths(Vertex *current, Vertex *end, Vertex **path, int depth);


Vertex *graph_bfs(Vertex *start)
{
  if (!start)
    return NULL;

  Queue *q = queue_create();
  if (!q)
    return NULL;

  Vertex *visit_list = NULL;

  queue_enqueue(q, start);
  start->visited = 1;

  while (!queue_is_empty(q))
  {
    Vertex *current;
    queue_dequeue(q, &current);

    // Criar cópia do vértice visitado
    Vertex *copy = graph_create_vertex(current->frequency, current->x, current->y);
    if (!copy)
    {
      queue_free(q);
      return NULL;
    }

    // Adicionar ao fim da lista (sem tail → percorre até ao fim)
    if (!visit_list)
    {
      visit_list = copy;
    }
    else
    {
      Vertex *tmp = visit_list;
      while (tmp->next)
        tmp = tmp->next;

      tmp->next = copy;
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

Vertex *graph_dfs(Vertex *start)
{
  if (!start)
    return NULL;

  Vertex *head = NULL;

  head = dfs_recursive(start, start->frequency);

  return head;
}

// Função auxiliar recursiva
static Vertex *dfs_recursive(Vertex *v, char target_freq)
{
  if (!v || v->visited || v->frequency != target_freq)
    return NULL;

  v->visited = 1;

  Vertex *copy = graph_create_vertex(v->frequency, v->x, v->y);
  if (!copy)
    return NULL;

  Vertex *last = copy;

  for (Adj_Node *adj = v->adj_list; adj; adj = adj->next)
  {
    Vertex *sublist = dfs_recursive(adj->dest, target_freq);

    // Concatenar a sublista ao final da lista atual
    if (sublist)
    {
      last->next = sublist;

      // Avançar até ao fim da nova sublista para atualizar last
      while (last->next)
        last = last->next;
    }
  }

  return copy;
}

int graph_find_all_paths(Vertex *start, Vertex *end)
{
    if (!start || !end)
        return -1;  // Erro

    Vertex *path[MAX_VERTICES];
    return find_all_paths(start, end, path, 0);
}

int find_all_paths(Vertex *current, Vertex *end, Vertex **path, int depth)
{
    if (!current)
        return 0;

    current->visited = 1;
    path[depth] = current;

    int total_paths = 0;

    if (current == end)
    {
        // Imprimir o caminho atual
        for (int i = 0; i <= depth; i++)
            printf("(%d,%d)%s", path[i]->x, path[i]->y, (i == depth) ? "\n" : " -> ");
        total_paths = 1;
    }
    else
    {
        for (Adj_Node *adj = current->adj_list; adj; adj = adj->next)
        {
            if (!adj->dest->visited)
            {
                total_paths += find_all_paths(adj->dest, end, path, depth + 1);
            }
        }
    }

    current->visited = 0; // backtrack
    return total_paths;
}

