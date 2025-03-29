/**
 * @file effects.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-03-28
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once
#include "dimensions.h"
#include "ed.h"

/**
 * @brief Detecta e regista efeitos nefastos na matriz a partir de pares de antenas com a mesma frequência.
 *
 * Esta função percorre a lista de antenas, procura pares com a mesma frequência,
 * e determina a zona de interferência (efeito nefasto) entre elas, com base nas coordenadas.
 * Os efeitos são registados numa nova lista ligada de ED com frequência '#'.
 *
 * @param antennas Lista ligada de antenas carregadas.
 * @param table Estrutura com metadados da matriz, como rows e cols.
 * @param effects Apontador para a lista ligada de efeitos (irá ser preenchida).
 * @return Número de efeitos detetados ou em caso de erro  retorna -1.
 */
int detect_effects(ED *antennas, Dimensions *dim, ED **effects);
