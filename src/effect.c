#include "effect.h"
#include <stdlib.h>
#include <ctype.h>

#pragma region Private_Functions_Definition

static int insert_effect_at(int x, int y, Dimensions *dim, ED **effects);

#pragma endregion Private_Functions_Definition

#pragma region Public_Functions
int detect_effects(ED *antennas, Dimensions *dim, ED **effects)
{
    if (!antennas || !dim || !effects)
        return -1;

    int effects_count = 0;

    for (ED *a1 = antennas; a1 != NULL; a1 = a1->next)
    {
        for (ED *a2 = a1->next; a2 != NULL; a2 = a2->next)
        {

            // Frequência igual (case-insensitive)
            if (tolower(a1->frequency) != tolower(a2->frequency))
                continue;

            int dx = a2->x - a1->x;
            int dy = a2->y - a1->y;

            // Verifica alinhamento válido
            if ((dx == 0 && dy != 0) || (dy == 0 && dx != 0) || (abs(dx) == abs(dy)))
            {
                int dist = abs(dx != 0 ? dx : dy);

                if (dist < MIN_EFFECT_DISTANCE)
                {
                    // Direção normalizada
                    int dir_x = (dx == 0) ? 0 : (dx > 0 ? 1 : -1);
                    int dir_y = (dy == 0) ? 0 : (dy > 0 ? 1 : -1);

                    // Efeito nefasto a partir de a1
                    int x1 = a1->x + dir_x * dist;
                    int y1 = a1->y + dir_y * dist;

                    effects_count += insert_effect_at(x1, y1, dim, effects);

                    // Efeito nefasto a partir de a2
                    int x2 = a2->x - dir_x * dist;
                    int y2 = a2->y - dir_y * dist;

                    effects_count += insert_effect_at(x2, y2, dim, effects);
                }
            }
        }
    }

    return effects_count;
}
#pragma endregion Public_Functions

#pragma region Private_Functions

static int insert_effect_at(int x, int y, Dimensions *dim, ED **effects)
{
    if (x < 0 || x >= dim->cols || y < 0 || y >= dim->rows)
        return 0;

    ED *e = create_ed(EFFECT_SYMBOL, x, y);
    if (!e)
        return 0;

    if (!insert_ed(effects, e))
    {
        free(e);
        return 0;
    }

    return 1;
}

#pragma endregion Private_Functions