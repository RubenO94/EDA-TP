/**
 * @file geometry.h
 * @author Rúben Oliveira (a24861@alunos.ipca.pt)
 * @brief Estruturas e funções auxiliares para coordenadas e dimensões.
 * @version 1.0
 * @date 2025-03-27
 *
 * Fornece estruturas genéricas para manipulação de posições em grelhas bidimensionais,
 * bem como funções utilitárias para verificação de igualdade e limites.
 */

#pragma once
#include "core/ed.h"

/**
 * @brief Representa uma coordenada (x, y) na matriz.
 *
 * Utilizada para identificar a posição de antenas, efeitos ou quaisquer outros pontos relevantes.
 */
typedef struct
{
  int x; /** Coluna */
  int y; /** Linha */
} Coord;

/**
 * @brief Representa as dimensões da matriz.
 *
 * Usado para validar posições dentro dos limites da matriz e organizar a visualização.
 */
typedef struct
{
  int rows; /** Número total de linhas (altura) */
  int cols; /** Número total de colunas (largura) */
} Dimensions;

/**
 * @brief Verifica se duas coordenadas são iguais.
 *
 * Compara os valores de x e y de ambas as coordenadas.
 *
 * @param a Primeira coordenada.
 * @param b Segunda coordenada.
 * @return 1 se ambas as coordenadas forem exatamente iguais, 0 caso contrário.
 */
int coord_equals(Coord a, Coord b);

/**
 * @brief Verifica se uma posição (x, y) está dentro dos limites da matriz.
 *
 * Garante que a coordenada fornecida pertence ao intervalo definido pelas dimensões da matriz.
 *
 * @param x Valor da coluna (0-based).
 * @param y Valor da linha (0-based).
 * @param dim Apontador para a estrutura Dimensions que define os limites da matriz.
 * @return 1 se a posição estiver dentro dos limites definidos, 0 se estiver fora.
 *
 * @note Esta função é essencial para evitar acessos inválidos durante operações na grelha.
 */
int is_within_bounds(int x, int y, Dimensions *dim);

/**
 * @brief Verifica se dois elementos estão alinhados (horizontal, vertical ou diagonal).
 * @param a Elemento A.
 * @param b Elemento B.
 * @return 1 se estiverem alinhados, 0 caso contrário.
 */
int is_aligned(ED *a, ED *b);

/**
 * @brief Retorna a direção (+1, -1 ou 0) de um deslocamento.
 * @param delta Valor da diferença (por exemplo, dx ou dy).
 * @return Direção: 1 (positivo), -1 (negativo), ou 0.
 */
int get_direction(int delta);

/**
 * @brief Calcula a distância entre dois elementos alinhados.
 * @param a Elemento A.
 * @param b Elemento B.
 * @return Distância (valor absoluto).
 */
int get_distance(ED *a, ED *b);

/**
 * @brief Calcula a posição de um efeito nefasto a partir de uma antena, numa direção específica.
 *
 * Dada uma antena e uma direção (normalizada), esta função devolve a coordenada onde
 * o efeito nefasto deverá ser colocado, a uma distância especificada.
 *
 * @param a Apontador para a antena de origem.
 * @param dir_x Direção no eixo X (-1, 0, 1).
 * @param dir_y Direção no eixo Y (-1, 0, 1).
 * @param dist Distância do efeito a partir da antena.
 * @return Coordenada (x, y) onde o efeito deverá ser inserido.
 */
Coord get_effect_position_from(const ED *a, int dir_x, int dir_y, int dist);
