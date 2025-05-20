/**
 * @file ed_validator.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-03-30
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once
#include "core/ed.h"

/**
 * @brief Verifica se uma frequência é válida (A-Z, a-z).
 *
 * @param freq Carácter a verificar.
 * @return 1 se for válida, 0 caso contrário.
 */
int is_valid_frequency(char freq);

/**
 * @brief Verifica se a frequência de duas antenas é igual (case-insensitive).
 *
 * @param f1 Primeira frequência.
 * @param f2 Segunda frequência.
 * @return 1 se forem iguais, 0 caso contrário.
 */
int same_frequency(char f1, char f2);

/**
 * @brief Verifica se um nó ED representa uma antena (e não um efeito).
 *
 * @param node Apontador para o nó.
 * @return 1 se for antena, 0 se for efeito ou inválido.
 */
int is_antenna(const ED *node);

/**
 * @brief Verifica se um nó ED representa um efeito nefasto.
 *
 * @param node Apontador para o nó.
 * @return 1 se for efeito, 0 se não for.
 */
int is_effect(const ED *node);
