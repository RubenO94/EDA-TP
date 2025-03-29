/**
 * @file controller.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-03-29
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include "ed.h"
#include "geometry.h"

extern ED *antennas;
extern ED *effects;
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
 * - As dimensões da matriz (rows x cols),
 * - A lista de antenas,
 * - E a lista de efeitos nefastos (substituindo listas existentes).
 *
 * Todos os dados atuais em memória serão libertados antes da carga.
 *
 * @param filepath Caminho para o ficheiro binário do projeto.
 * @return 1 em caso de sucesso, 0 em caso de falha.
 */
int load_project(const char *filepath);

/**
 * @brief Guarda o projeto atual num ficheiro binário.
 *
 * Esta função grava:
 * - As dimensões da matriz (rows x cols),
 * - A lista de antenas existentes,
 * - E a lista de efeitos nefastos (se existirem).
 *
 * O ficheiro resultante pode ser carregado posteriormente com a função `load_project`.
 *
 * @param filepath Caminho para guardar o ficheiro binário do projeto.
 * @return 1 em caso de sucesso, 0 em caso de falha.
 */
int save_project(const char *filepath);

/**
 * @brief Gera a lista de efeitos nefastos com base nas antenas atuais.
 *
 * Limpa os efeitos anteriores antes de gerar novos.
 *
 * @return Número de efeitos gerados ou -1 em caso de erro.
 */
int generate_effects();

/**
 * @brief Insere uma antena e atualiza os efeitos se necessário.
 *
 * @param freq Carácter da frequência da antena.
 * @param x Coordenada X.
 * @param y Coordenada Y.
 * @return 1 em caso de sucesso, 0 se já existir antena nessa posição ou erro.
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
 * @brief Mostra graficamente a matriz com as antenas (sem efeitos).
 */
void show_antennas();

/**
 * @brief Mostra graficamente a matriz com antenas e efeitos (se existirem).
 */
void show_effects();