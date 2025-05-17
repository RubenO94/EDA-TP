/**
 * @file algorithms.h
 * @author
 * @brief Interface para os algoritmos de grafos (BFS, DFS, caminhos, interseções).
 * @version 1.0
 * @date 2025-05-XX
 *
 * Fornece funções de percurso e análise de grafos com suporte para callbacks.
 */

#pragma once
#include "core/graph.h"

/**
 * @brief Callback a aplicar em cada vértice visitado.
 *
 * @param v Apontador para o vértice.
 */
typedef void (*VisitCallback)(Vertex *v);

/**
 * @brief Executa uma busca em largura (BFS) a partir de um vértice.
 *
 * Apenas percorre vértices com a mesma frequência.
 *
 * @param start Vértice de partida.
 * @param visit Função a aplicar em cada vértice visitado.
 */
void graph_bfs(Vertex *start, VisitCallback visit);

/**
 * @brief Executa uma busca em profundidade (DFS) recursiva.
 *
 * Apenas percorre vértices com a mesma frequência.
 *
 * @param start Vértice de partida.
 * @param visit Função a aplicar em cada vértice visitado.
 */
void graph_dfs(Vertex *start, VisitCallback visit);

/**
 * @brief Procura e imprime todos os caminhos entre dois vértices.
 *
 * Apenas considera vértices com a mesma frequência.
 *
 * @param start Vértice inicial.
 * @param end Vértice destino.
 */
void graph_find_all_paths(Vertex *start, Vertex *end);

/**
 * @brief Lista todas as interseções entre antenas de duas frequências distintas.
 *
 * @param g Grafo a analisar.
 * @param freq_a Primeira frequência.
 * @param freq_b Segunda frequência.
 */
void graph_list_frequency_intersections(GR *g, char freq_a, char freq_b);
