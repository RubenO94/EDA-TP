/**
 * @file queue.h
 * @author
 * @brief Estrutura de dados FIFO (fila) para armazenar vértices em algoritmos de grafos.
 * @version 1.0
 * @date 2025-05-XX
 *
 * Implementação de fila dinâmica com listas ligadas para uso em BFS.
 */

#pragma once
#include "graph.h"

/**
 * @brief Nó interno da fila.
 */
typedef struct QueueNode
{
  Vertex *data;           /** Vértice armazenado */
  struct QueueNode *next; /** Próximo elemento da fila */
} QueueNode;

/**
 * @brief Estrutura principal da fila.
 */
typedef struct Queue
{
  QueueNode *front; /** Início da fila (para dequeue) */
  QueueNode *rear;  /** Fim da fila (para enqueue) */
} Queue;

/**
 * @brief Cria uma nova fila vazia.
 *
 * @return Apontador para a fila criada ou NULL em caso de erro.
 */
Queue *queue_create();

/**
 * @brief Verifica se a fila está vazia.
 *
 * @param q Fila a verificar.
 * @return 1 se estiver vazia, 0 caso contrário.
 */
int queue_is_empty(Queue *q);

/**
 * @brief Adiciona um novo vértice ao fim da fila.
 *
 * @param q Fila onde será adicionado.
 * @param v Vértice a adicionar.
 * @return 1 em caso de sucesso, 0 em caso de erro.
 */
int queue_enqueue(Queue *q, Vertex *v);

/**
 * @brief Remove o vértice no início da fila.
 *
 * @param q Fila de onde será removido.
 * @param v Apontador onde será guardado o vértice removido.
 * @return 1 em caso de sucesso, 0 se a fila estiver vazia.
 */
int queue_dequeue(Queue *q, Vertex **v);

/**
 * @brief Liberta toda a memória usada pela fila.
 *
 * @param q Fila a destruir.
 */
void queue_free(Queue *q);
