/**
 * @file graph_io.h
 * @author
 * @brief Funções de entrada/saída para ler e guardar grafos de ficheiros de texto ou binário.
 * @version 1.0
 * @date 2025-05-12
 *
 * Este módulo permite carregar um grafo a partir de uma matriz de texto, bem como
 * guardar e restaurar grafos a partir de ficheiros binários.
 */

#pragma once
#include "core/graph.h"

// =========================
// CARREGAMENTO DE TEXTO
// =========================

/**
 * @brief Carrega um grafo a partir de um ficheiro de texto com a matriz de antenas.
 *
 * Esta função lê o ficheiro linha a linha e cria vértices com base em caracteres alfabéticos.
 * Posições com '.' são ignoradas. As coordenadas são deduzidas da posição do caractere na matriz.
 *
 * O grafo deve já ter sido criado com graph_create().
 *
 * @param filepath Caminho para o ficheiro .txt (matriz).
 * @param g Grafo já criado onde os vértices serão inseridos.
 * @return 1 em caso de sucesso, 0 em caso de erro (ficheiro inválido ou falha de inserção).
 */
int graph_load_from_txt(const char *filepath, GR *g);

// =========================
// BINÁRIO: GUARDA E CARREGA
// =========================

/**
 * @brief Guarda o grafo num ficheiro binário.
 *
 * A função grava os vértices (frequência, coordenadas) e os seus vizinhos,
 * através das coordenadas dos vértices adjacentes.
 *
 * @param filepath Caminho para o ficheiro binário de destino.
 * @param g Grafo a guardar.
 * @return 1 em caso de sucesso, 0 em caso de erro.
 */
int graph_save_to_bin(const char *filepath, const GR *g);

/**
 * @brief Carrega um grafo completo a partir de um ficheiro binário.
 *
 * Lê os vértices e depois reconstrói as arestas usando as coordenadas dos adjacentes.
 * O grafo é criado dentro da função e deve ser libertado com graph_free().
 *
 * @param filepath Caminho para o ficheiro binário.
 * @return Apontador para o grafo carregado, ou NULL em caso de erro.
 */
GR *graph_load_from_bin(const char *filepath);
