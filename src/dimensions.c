#include "dimensions.h"

int is_within_bounds(int x, int y, const Dimensions *dim)
{
    return dim && x >= 0 && x < dim->cols && y >= 0 && y < dim->rows;
}
