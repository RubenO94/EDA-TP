/**
 * @file controller.c
 * @author Rúben Oliveira (a24861@alunos.ipca.pt)
 * @brief Implementação da lógica de controlo de antenas e efeitos.
 * @version 1.0
 * @date 2025-03-28
 *
 * Contém a lógica para gerir a lista de antenas, efeitos nefastos,
 * e coordenação com ficheiros binários e de texto.
 */

#include "controller.h"
#include "ed.h"
#include "ed_io.h"
#include "ed_validator.h"
#include "effect.h"
#include "display.h"
#include <stddef.h>
#include <ctype.h>
#include <malloc.h>

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

    int load_result = load_matrix(filepath, &antennas, &dim);
    if (!load_result)
        return 0;
    if (generate_all_effects(antennas, &dim, &effects) < 0)
        return 0;
    return 1;
}

int insert_antenna(char freq, int x, int y)
{
    if (!isalpha(freq) || !is_within_bounds(x, y, &dim) || find_ed(antennas, x, y))
        return -1;

    ED *node = create_ed(freq, x, y);
    if (!node || !insert_ed(&antennas, node))
    {
        free(node);
        return -1;
    }

    // Detetar efeitos com outras antenas
    int effects_found = detect_effects_for_node(node, antennas, &dim, &effects);
    return effects_found >= 0 ? effects_found : -1;
}

int remove_antenna(int x, int y)
{
    ED *target = find_ed(antennas, x, y);
    if (!target)
        return -1;

    int effects_removed = remove_effects_for_node(target, antennas, &dim, &effects);
    if (!remove_ed(&antennas, x, y))
        return -1;

    return effects_removed >= 0 ? effects_removed : -1;
}

void show_matrix()
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
