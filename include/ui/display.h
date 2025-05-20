/**
 * @file display.h
 * @author Rúben Oliveira (a24861@alunos.ipca.pt)
 * @brief Funções de apresentação gráfica da matriz de antenas e efeitos.
 * @version 1.0
 * @date 2025-03-28
 *
 * Contém funções para imprimir visualmente a matriz no terminal, com cores ANSI,
 * legendas, bordas e suporte a diferentes modos de visualização.
 */

#pragma once

#include "core/ed.h"
#include "utils/geometry.h"
#include "ui/terminal_colors.h"

/**
 * @brief Modo de visualização da matriz.
 */
typedef enum
{
  PRINT_ANTENNAS_ONLY, // Mostra apenas as antenas
  PRINT_WITH_EFFECTS   // Mostra antenas e efeitos nefastos (se existirem)
} PrintMode;

/**
 * @brief Imprime a matriz no terminal com base nas antenas e (opcionalmente) nos efeitos.
 *
 * A matriz é apresentada com coordenadas e bordas, utilizando as seguintes regras de visualização:
 *
 * - `.` para posições vazias;
 *
 * - `A-Z` para antenas;
 *
 * - `#` para efeitos;
 *
 * - `#A` quando há simultaneamente efeito e antena na mesma posição.
 *
 * @note A função assume que as coordenadas das antenas e efeitos estão dentro dos limites definidos por `dim`.
 *
 * @param antennas Lista ligada de antenas (obrigatória).
 * @param effects Lista ligada de efeitos (opcional; usada apenas se `mode == PRINT_WITH_EFFECTS`).
 * @param dim Ponteiro para estrutura que define as dimensões da matriz.
 * @param mode Modo de impressão (apenas antenas ou antenas + efeitos).
 */
void print_matrix(ED *antennas, ED *effects, Dimensions *dim, PrintMode mode);
