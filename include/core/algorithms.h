/**
 * @file algorithms.h
 * @author
 * @brief Algoritmos de grafos: BFS, DFS, caminhos e interseções.
 * @version 1.0
 * @date 2025-05-15
 *
 * Este módulo implementa algoritmos clássicos de percurso e análise em grafos
 * com base em listas ligadas: busca em largura, profundidade, caminhos múltiplos
 * e interseções entre frequências distintas.
 */

#pragma once
#include "core/graph.h"

// =========================
// PERCURSOS
// =========================

/**
 * @brief Executa uma busca em largura (BFS) a partir de um vértice.
 *
 * Apenas percorre vértices com a mesma frequência do vértice de partida.
 * Retorna uma nova lista ligada com os vértices visitados, na ordem em que foram explorados.
 *
 * @param start Vértice de partida.
 * @return Lista ligada com os vértices visitados ou NULL em caso de erro.
 */
Vertex *graph_bfs(Vertex *start);

/**
 * @brief Executa uma busca em profundidade (DFS) a partir de um vértice.
 *
 * Apenas percorre vértices com a mesma frequência do vértice de partida.
 * Retorna uma nova lista ligada com os vértices visitados, na ordem em que foram explorados.
 *
 * @param start Vértice de partida.
 * @return Lista ligada com os vértices visitados ou NULL em caso de erro.
 */
Vertex *graph_dfs(Vertex *start);

// =========================
// CAMINHOS E INTERSEÇÕES (NÃO IMPLEMENTADOS)
// =========================

/**
 * @brief [NÃO IMPLEMENTADO]
 * @note Função referida em aula mas não abordada em profundidade.
 */
int graph_find_all_paths(Vertex *start, Vertex *end);

/**
 * @brief [NÃO IMPLEMENTADO]
 * @note Referido em contexto teórico; não incluído para garantir domínio do código.
 */
/// int graph_list_frequency_intersections(GR *g, char freq_a, char freq_b);
