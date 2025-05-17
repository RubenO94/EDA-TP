/**
 * @file graph_io.h
 * @author
 * @brief Operações de entrada/saída para guardar e carregar grafos (binário e texto).
 * @version 1.0
 * @date 2025-05-XX
 *
 * Este módulo permite guardar grafos em ficheiros binários e carregar grafos a partir de ficheiros de texto
 * com mapas de antenas, onde cada antena é representada por um caractere (A-Z, a-z).
 */

#pragma once
#include "core/graph.h"
#include "utils/geometry.h" // Para Dimensions
#include <stdio.h>

/**
 * @brief Guarda o grafo completo num ficheiro binário.
 *
 * Armazena todos os vértices com as suas coordenadas, frequência e adjacências.
 *
 * @param g Grafo a guardar.
 * @param filename Caminho para o ficheiro .bin.
 * @return 1 em caso de sucesso, 0 em caso de erro.
 */
int save_graph(const GR *g, const char *filename);

/**
 * @brief Carrega um grafo completo a partir de um ficheiro binário.
 *
 * Reconstrói todos os vértices e arestas.
 *
 * @param filename Caminho do ficheiro .bin.
 * @return Apontador para o grafo carregado ou NULL em caso de erro.
 */
GR *load_graph(const char *filename);

/**
 * @brief Constrói um grafo a partir de um ficheiro de texto com a matriz de antenas.
 *
 * Cada linha do ficheiro representa uma linha da matriz. Apenas letras (A-Z, a-z) são consideradas antenas.
 * As posições são usadas como coordenadas (x, y). O grafo resultante conecta antenas com a mesma frequência.
 *
 * @param filename Caminho do ficheiro .txt.
 * @param dim Estrutura opcional onde serão armazenadas as dimensões da matriz (pode ser NULL).
 * @return Grafo construído com os vértices e ligações, ou NULL em caso de erro.
 */
GR *load_graph_from_txt(const char *filename, Dimensions *dim);
