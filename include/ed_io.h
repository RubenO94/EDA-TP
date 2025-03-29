/**
 * @file ed_io.h
 * @author Rúben Oliveira (a24861@alunos.ipca.pt)
 * @brief Funções responsáveis por carregar, guardar listas ED e metadados da matriz.
 * @version 0.1
 * @date 2025-03-21
 * @copyright Copyright (c) 2025
 */

#pragma once

#include "ed.h"
#include "geometry.h"
#include "constants.h"

/**
 * @brief Guarda antenas + efeitos + dimensões num único ficheiro binário.
 *
 * @param antennas Lista de antenas.
 * @param effects Lista de efeitos.
 * @param dim Estrutura com rows e cols.
 * @param filepath Caminho do ficheiro binário.
 * @return 1 em caso de sucesso, 0 em caso de erro.
 */
int save_all_to_bin(ED *antennas, ED *effects, Dimensions *dim, const char *filepath);

/**
 * @brief Carrega antenas + efeitos + dimensões de um ficheiro binário.
 *
 * Substitui os dados existentes.
 *
 * @param antennas Apontador para cabeça da lista de antenas.
 * @param effects Apontador para cabeça da lista de efeitos.
 * @param dim Estrutura a preencher com as dimensões.
 * @param filepath Caminho do ficheiro binário.
 * @return 1 em caso de sucesso, 0 em caso de erro.
 */
int load_all_from_bin(ED **antennas, ED **effects, Dimensions *dim, const char *filepath);

/**
 * @brief Carrega uma matriz de antenas a partir de um ficheiro de texto.
 *
 * Apenas os caracteres válidos (A-Z, a-z) são inseridos na lista. O caractere '#' é ignorado por representar efeitos e será gerado posteriormente.
 * A função também determina as dimensões da matriz (linhas e colunas).
 *
 * @param filepath Caminho para o ficheiro .txt com a matriz.
 * @param head Apontador para onde será guardada a cabeça da lista de antenas.
 * @param dim Estrutura onde serão guardadas as dimensões da matriz carregada.
 * @return 1 em caso de sucesso, 0 em caso de falha (ex: ficheiro inválido).
 */
int load_matrix(const char *filepath, ED **head, Dimensions *dim);
