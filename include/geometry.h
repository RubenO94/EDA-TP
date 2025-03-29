/**
 * @file geometry.h
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
 * @brief Representa uma coordenada (x, y) na matriz.
 */
typedef struct
{
    int x;
    int y;
} Coord;

/**
 * @brief Representa as dimensões da matriz.
 */
typedef struct
{
    int rows; // número de linhas (altura)
    int cols; // número de colunas (largura)
} Dimensions;

/**
 * @brief Verifica se duas coordenadas são iguais.
 * @param a Primeira coordenada.
 * @param b Segunda coordenada.
 * @return 1 se forem iguais, 0 caso contrário.
 */
int coord_equals(Coord a, Coord b);

/**
 * @brief Verifica se uma posição (x, y) está dentro dos limites da matriz.
 * @param x Coordenada x.
 * @param y Coordenada y.
 * @param dim Apontador para a estrutura Dimensions.
 * @return 1 se estiver dentro dos limites, 0 se for inválido ou fora dos limites.
 */
int is_within_bounds(int x, int y, const Dimensions *dim);
