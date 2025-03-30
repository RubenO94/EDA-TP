/**
 * @file controller.h
 * @author Rúben Oliveira (a24861@alunos.ipca.pt)
 * @brief Orquestração das operações principais de antenas e efeitos.
 * @version 1.0
 * @date 2025-03-28
 *
 * Define a interface pública para carregar mapas, gerir projetos binários,
 * gerar efeitos e gerir inserções/remoções de antenas.
 */

#pragma once

#include "ed.h"
#include "geometry.h"

/// Lista global de antenas (ligada).
extern ED *antennas;

/// Lista global de efeitos nefastos (ligada).
extern ED *effects;

/// Dimensões globais da matriz carregada.
extern Dimensions dim;

/**
 * @brief Carrega um mapa de antenas a partir de um ficheiro .txt.
 *
 * Substitui qualquer lista de antenas/efeitos existente.
 * Atualiza as dimensões da matriz.
 *
 * @param filepath Caminho do ficheiro .txt.
 * @return 1 em caso de sucesso, 0 em caso de falha.
 */
int load_map(const char *filepath);

/**
 * @brief Carrega um projeto completo a partir de um ficheiro binário.
 *
 * Esta função carrega:
 *
 * - As dimensões da matriz (rows x cols);
 *
 * - A lista de antenas;
 *
 * - A lista de efeitos nefastos.
 *
 * Todos os dados atuais em memória são libertados antes da carga.
 *
 * @param filepath Caminho para o ficheiro binário do projeto.
 * @return 1 em caso de sucesso, 0 em caso de falha.
 */
int load_project(const char *filepath);

/**
 * @brief Guarda o projeto atual num ficheiro binário.
 *
 * Esta função grava:
 *
 * - As dimensões da matriz;
 *
 * - A lista de antenas;
 *
 * - A lista de efeitos (se existirem).
 *
 * O ficheiro resultante pode ser carregado com a função `load_project()`.
 *
 * @param filepath Caminho para guardar o ficheiro binário do projeto.
 * @return 1 em caso de sucesso, 0 em caso de falha.
 */
int save_project(const char *filepath);

/**
 * @brief Insere uma nova antena e atualiza os efeitos, se necessário.
 *
 * @param freq Carácter da frequência da antena.
 * @param x Coordenada X.
 * @param y Coordenada Y.
 * @return 1 em caso de sucesso, 0 se já existir uma antena na posição ou em caso de erro.
 */
int insert_antenna(char freq, int x, int y);

/**
 * @brief Remove uma antena e atualiza os efeitos associados.
 *
 * @param x Coordenada X da antena.
 * @param y Coordenada Y da antena.
 * @return 1 em caso de sucesso, 0 se não existir antena nessa posição.
 */
int remove_antenna(int x, int y);

/**
 * @brief Mostra graficamente a matriz atual com antenas e efeitos (se existirem).
 */
void show_matrix();
