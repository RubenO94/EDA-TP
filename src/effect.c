#include "effect.h"
#include <stdlib.h>
#include <ctype.h>

#pragma region Public_Functions

int generate_all_effects(ED *antennas, Dimensions *dim, ED **effects)
{
    if (!antennas || !dim || !effects)
        return -1;

    int count = 0;

    for (ED *a1 = antennas; a1 != NULL; a1 = a1->next)
    {
        for (ED *a2 = a1->next; a2 != NULL; a2 = a2->next)
        {
            Coord ef1, ef2;
            if (detect_effect_pair(a1, a2, dim, &ef1, &ef2))
            {
                count += insert_effect_at(ef1, dim, effects);
                count += insert_effect_at(ef2, dim, effects);
            }
        }
    }

    return count;
}

int detect_effect_pair(ED *a1, ED *a2, Dimensions *dim, Coord *out1, Coord *out2)
{
    if (!a1 || !a2 || !dim || !out1 || !out2)
        return 0;

    if (tolower(a1->frequency) != tolower(a2->frequency))
        return 0;

    int dx = a2->x - a1->x;
    int dy = a2->y - a1->y;

    if ((dx == 0 && dy != 0) || (dy == 0 && dx != 0) || (abs(dx) == abs(dy)))
    {
        int dist = abs(dx != 0 ? dx : dy);
        if (dist < MIN_EFFECT_DISTANCE)
        {
            int dir_x = (dx == 0) ? 0 : (dx > 0 ? 1 : -1);
            int dir_y = (dy == 0) ? 0 : (dy > 0 ? 1 : -1);

            // Posição fora da A1
            int x1 = a1->x - dir_x * dist;
            int y1 = a1->y - dir_y * dist;

            // Posição fora da A2
            int x2 = a2->x + dir_x * dist;
            int y2 = a2->y + dir_y * dist;

            *out1 = (Coord){x1, y1};
            *out2 = (Coord){x2, y2};

            // return is_within_bounds(out1->x, out1->y, dim) && is_within_bounds(out2->x, out2->y, dim);
            return 1;
        }
    }

    return 0;
}

int insert_effect_at(Coord pos, Dimensions *dim, ED **effects)
{
    if (!is_within_bounds(pos.x, pos.y, dim))
        return 0;

    // Verifica se já existe nessa posição
    if (find_ed(*effects, pos.x, pos.y))
        return 0;

    ED *e = create_ed(EFFECT_SYMBOL, pos.x, pos.y);
    if (!e || !insert_ed(effects, e))
    {
        free(e);
        return 0;
    }

    return 1;
}

#pragma endregion Public_Functions