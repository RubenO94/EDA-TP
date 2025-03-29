#include "geometry.h"

int coord_equals(Coord a, Coord b)
{
    return a.x == b.x && a.y == b.y;
}

int is_within_bounds(int x, int y, const Dimensions *dim)
{
    if (!dim)
        return 0;
    return x >= 0 && x < dim->cols && y >= 0 && y < dim->rows;
}