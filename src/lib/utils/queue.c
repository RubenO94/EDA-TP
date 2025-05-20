#include "utils/queue.h"
#include <stdlib.h>

// =========================
// Criação
// =========================

Queue *queue_create()
{
  Queue *q = malloc(sizeof(Queue));
  if (!q)
    return NULL;

  q->front = NULL;
  q->rear = NULL;
  return q;
}

// =========================
// Estado
// =========================

int queue_is_empty(Queue *q)
{
  if (!q)
    return 1;
  return (q->front == NULL);
}

// =========================
// Inserir
// =========================

int queue_enqueue(Queue *q, Vertex *v)
{
  if (!q || !v)
    return 0;

  QueueNode *new_node = malloc(sizeof(QueueNode));
  if (!new_node)
    return 0;

  new_node->data = v;
  new_node->next = NULL;

  if (q->rear)
  {
    q->rear->next = new_node;
  }
  else
  {
    q->front = new_node;
  }

  q->rear = new_node;
  return 1;
}

// =========================
// Remover
// =========================

int queue_dequeue(Queue *q, Vertex **v)
{
  if (!q || queue_is_empty(q) || !v)
    return 0;

  QueueNode *temp = q->front;
  *v = temp->data;
  q->front = temp->next;

  if (!q->front)
    q->rear = NULL;

  free(temp);
  return 1;
}

// =========================
// Libertar
// =========================

void queue_free(Queue *q)
{
  if (!q)
    return;

  QueueNode *curr = q->front;
  while (curr)
  {
    QueueNode *next = curr->next;
    free(curr);
    curr = next;
  }

  free(q);
}
