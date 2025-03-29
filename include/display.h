/**
 * @file display.h
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
#include "terminal_colors.h"

typedef enum
{
    PRINT_ANTENNAS_ONLY,
    PRINT_WITH_EFFECTS
} PrintMode;

/**
 * @brief Imprime a matriz no terminal com base nas antenas e (opcionalmente) nos efeitos.
 *
 * A matriz é impressa no formato linha × coluna com as seguintes representações:
 * - '.' para posição vazia
 * - 'A-Z' para antenas
 * - '#' para efeitos
 * - '#A' quando há efeito e antena na mesma posição
 *
 * @param antennas Lista ligada de antenas (obrigatória).
 * @param effects Lista ligada de efeitos (opcional, consoante o modo).
 * @param dim Estrutura com as dimensões da matriz.
 * @param mode Modo de impressão (somente antenas ou antenas + efeitos).
 */
void print_matrix(ED *antennas, ED *effects, Dimensions *dim, PrintMode mode);
