/**
 * @file effect.c
 * @author Rúben Oliveira (a24861@alunos.ipca.pt)
 * @brief Implementação das funções de deteção e gestão de efeitos nefastos entre antenas.
 * @version 1.0
 * @date 2025-03-28
 */

#include "effect.h"
#include "constants.h"
#include "ed_validator.h"
#include <stdlib.h>

#pragma region Private_Functions_Definition

/**
 * @brief Calcula as coordenadas dos efeitos nefastos entre duas antenas, se aplicável.
 *
 * @param a1 Primeira antena.
 * @param a2 Segunda antena.
 * @param dim Dimensões da matriz.
 * @param out1 Coordenada do efeito a partir de a1.
 * @param out2 Coordenada do efeito a partir de a2.
 * @return 1 se houver interferência e coordenadas válidas, 0 caso contrário.
 */
static int calculate_effect_area(ED *a1, ED *a2, Dimensions *dim, Coord *out1, Coord *out2);

/**
 * @brief Processa dois nós e, se gerarem interferência, insere os efeitos.
 *
 * @param a1 Antena 1
 * @param a2 Antena 2
 * @param dim Dimensões da matriz
 * @param effects Lista a atualizar
 * @return Número de efeitos inseridos
 */
static int process_effects_between_pair(ED *a1, ED *a2, Dimensions *dim, ED **effects);

/**
 * @brief Insere um efeito nefasto na posição indicada, se estiver dentro da matriz.
 *
 * Verifica se as coordenadas são válidas e insere um novo nó com frequência '#' na
 * lista de efeitos.
 *
 * @param pos Estrutura com coordenadas do efeito.
 * @param dim Dimensões da matriz.
 * @param effects Lista de efeitos onde o novo nó será inserido.
 * @return 1 se o efeito foi inserido com sucesso, 0 caso contrário.
 *
 * @note Os efeitos podem ser inseridos em posições já ocupadas por antenas.
 * @warning Não são feitas validações de duplicados. Pode existir mais do que um efeito
 * com as mesmas coordenadas.
 */
static int insert_effect_at(Coord pos, Dimensions *dim, ED **effects);

#pragma endregion

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
            count += process_effects_between_pair(a1, a2, dim, effects);
        }
    }

    return count;
}

int detect_effects_for_node(ED *node, ED *antennas, Dimensions *dim, ED **effects)
{
    if (!node || !antennas || !dim || !effects)
        return -1;

    int count = 0;

    for (ED *a = antennas; a; a = a->next)
    {
        if (a == node)
            continue;

        count += process_effects_between_pair(node, a, dim, effects);
    }

    return count;
}

int remove_effects_for_node(ED *node, ED *antennas, Dimensions *dim, ED **effects)
{
    if (!node || !antennas || !dim || !effects)
        return -1;

    int removed = 0;

    for (ED *a = antennas; a; a = a->next)
    {
        if (a == node)
            continue;

        Coord e1, e2;
        if (calculate_effect_area(node, a, dim, &e1, &e2))
        {
            removed += remove_ed(effects, e1.x, e1.y);
            removed += remove_ed(effects, e2.x, e2.y);
        }
    }

    return removed;
}

#pragma endregion

#pragma region Private_Functions_Implementation

static int process_effects_between_pair(ED *a1, ED *a2, Dimensions *dim, ED **effects)
{
    Coord ef1, ef2;
    int count = 0;

    if (calculate_effect_area(a1, a2, dim, &ef1, &ef2))
    {
        count += insert_effect_at(ef1, dim, effects);
        count += insert_effect_at(ef2, dim, effects);
    }

    return count;
}

static int insert_effect_at(Coord pos, Dimensions *dim, ED **effects)
{
    if (!is_within_bounds(pos.x, pos.y, dim))
        return 0;

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

static int calculate_effect_area(ED *a1, ED *a2, Dimensions *dim, Coord *out1, Coord *out2)
{
    if (!a1 || !a2 || !dim || !out1 || !out2)
        return 0;

    if (!same_frequency(a1->frequency, a2->frequency))
        return 0;

    if (!is_aligned(a1, a2))
        return 0;

    int dx = a2->x - a1->x;
    int dy = a2->y - a1->y;
    int dist = get_distance(a1, a2);

    if (dist > MIN_EFFECT_DISTANCE)
        return 0;

    int dir_x = get_direction(dx);
    int dir_y = get_direction(dy);

    *out1 = get_effect_position_from(a1, (-dir_x), (-dir_y), dist); // dir <--
    *out2 = get_effect_position_from(a2, dir_x, dir_y, dist);       // dir -->

    return 1;
}

#pragma endregion