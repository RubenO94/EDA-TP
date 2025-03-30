/**
 * @file ed_validator.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-03-30
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "ed_validator.h"
#include "constants.h"
#include <ctype.h>

int is_valid_frequency(char freq)
{
    return isalpha(freq); // Apenas A-Z, a-z
}

int same_frequency(char f1, char f2)
{
    return tolower(f1) == tolower(f2);
}

int is_antenna(const ED *node)
{
    if (!node)
        return 0;
    return is_valid_frequency(node->frequency);
}

int is_effect(const ED *node)
{
    if (!node)
        return 0;
    return node->frequency == EFFECT_SYMBOL;
}
