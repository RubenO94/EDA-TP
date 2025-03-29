/**
 * @file controller.c
 * @author Rúben Oliveira (a24861@alunos.ipca.pt)
 * @brief Orquestra operações de gestão de antenas e efeitos.
 * @version 0.1
 * @date 2025-03-26
 */

#include "controller.h"
#include "ed_io.h"
#include "effect.h"
#include "display.h"
#include <stdlib.h>
#include <ctype.h>

ED *antennas = NULL;
ED *effects = NULL;
Dimensions dim = {0, 0};

int load_map(const char *filepath)
{
    if (!filepath)
        return 0;

    // Limpar listas anteriores
    if (antennas)
        free_ed_list(&antennas);
    if (effects)
        free_ed_list(&effects);

    return load_matrix(filepath, &antennas, &dim);
}

int generate_effects()
{
    if (!antennas)
        return -1;

    // Libertar primeiro caso exista efeitos na lista
    if (effects)
        free_ed_list(&effects);
    return generate_all_effects(antennas, &dim, &effects);
}

int insert_antenna(char freq, int x, int y)
{
    // Validações
    if (!is_within_bounds(x, y, &dim))
        return 0;

    if (find_ed(antennas, x, y))
        return 0;

    // Criar e Inserir
    ED *node = create_ed(freq, x, y);
    if (!node || !insert_ed(&antennas, node))
    {
        free(node);
        return 0;
    }

    // Detetar efeitos com todas as outras antenas
    for (ED *a = antennas; a; a = a->next)
    {
        if (a == node)
            continue;

        Coord e1, e2;
        if (detect_effect_pair(node, a, &dim, &e1, &e2))
        {
            // Inserir os efeitos detectados na lista de efeitos
            insert_effect_at(e1, &dim, &effects);
            insert_effect_at(e2, &dim, &effects);
        }
    }

    return 1;
}

int remove_antenna(int x, int y)
{
    if (!find_ed(antennas, x, y))
        return 0;

    ED *target = find_ed(antennas, x, y);
    if (!target)
        return 0;

    for (ED *a = antennas; a; a = a->next)
    {
        if (a == target)
            continue;

        Coord e1, e2;
        if (detect_effect_pair(target, a, &dim, &e1, &e2))
        {
            remove_ed(&effects, e1.x, e1.y);
            remove_ed(&effects, e2.x, e2.y);
        }
    }

    remove_ed(&antennas, x, y);
    return 1;
}

void show_antennas()
{
    print_matrix(antennas, NULL, &dim, PRINT_ANTENNAS_ONLY);
}

void show_effects()
{
    print_matrix(antennas, effects, &dim, PRINT_WITH_EFFECTS);
}

int load_project(const char *filepath)
{
    if (!filepath)
        return 0;

    int loaded = load_all_from_bin(&antennas, &effects, &dim, filepath);
    if (!loaded)
        return 0;

    return 1;
}

int save_project(const char *filepath)
{
    if (!filepath)
        return 0;

    int saved = save_all_to_bin(antennas, effects, &dim, filepath);
    if (!saved)
        return 0;

    return 1;
}
