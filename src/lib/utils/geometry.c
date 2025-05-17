/**
 * @file geometry.c
 * @author Rúben Oliveira (a24861@alunos.ipca.pt)
 * @brief Implementação de funções auxiliares para coordenadas e dimensões da matriz.
 * @version 1.0
 * @date 2025-03-28
 *
 * Contém funções para verificar igualdade de coordenadas e
 * se uma dada posição está dentro dos limites da matriz.
 */

#include "utils/geometry.h"
#include <stdlib.h>

int coord_equals(Coord a, Coord b)
{
  return a.x == b.x && a.y == b.y;
}

int is_within_bounds(int x, int y, Dimensions *dim)
{
  if (!dim)
    return 0;
  return x >= 0 && x < dim->cols && y >= 0 && y < dim->rows;
}

int is_aligned(ED *a1, ED *a2)
{
  int dx = a2->x - a1->x;
  int dy = a2->y - a1->y;
  return (dx == 0 && dy != 0) || (dy == 0 && dx != 0) || (abs(dx) == abs(dy));
}

int get_direction(int delta)
{
  return (delta == 0) ? 0 : (delta > 0 ? 1 : -1);
}

int get_distance(ED *a1, ED *a2)
{
  return abs(a1->x != a2->x ? a2->x - a1->x : a2->y - a1->y);
}

Coord get_effect_position_from(const ED *a, int dir_x, int dir_y, int dist)
{
  return (Coord){
      a->x + dir_x * dist,
      a->y + dir_y * dist};
}
