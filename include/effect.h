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
#include "geometry.h"
#include "ed.h"

/**
 * @brief Gera a lista completa de efeitos nefastos com base nas antenas.
 *
 * @param antennas Lista ligada de antenas.
 * @param dim Dimensões da matriz.
 * @param effects Apontador para a lista onde os efeitos serão armazenados.
 * @return Número de efeitos gerados ou -1 em caso de erro.
 */
int generate_all_effects(ED *antennas, Dimensions *dim, ED **effects);

/**
 * @brief Verifica se um par de antenas causa efeitos nefastos e calcula as coordenadas.
 *
 * @param a1 Primeira antena.
 * @param a2 Segunda antena.
 * @param dim Dimensões da matriz.
 * @param out1 Efeito gerado a partir de a1.
 * @param out2 Efeito gerado a partir de a2.
 * @return 1 se houver efeito nefasto, 0 caso contrário.
 */
int detect_effect_pair(ED *a1, ED *a2, Dimensions *dim, Coord *out1, Coord *out2);

/**
 * @brief Insere um efeito na lista, se estiver dentro da matriz.
 */
int insert_effect_at(Coord pos, Dimensions *dim, ED **effects);
