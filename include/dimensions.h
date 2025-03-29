/**
 * @file matrix.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-03-29
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

/**
 * @brief Estrutura que define as dimensões da matriz carregada
 *
 */
typedef struct
{
    int rows; // Número de linhas da matriz (altura → y)
    int cols; // Número de colunas da matriz (largura → x)
} Dimensions;

int is_within_bounds(int x, int y, const Dimensions *dim);
