/**
 * @file effect.h
 * @author Rúben Oliveira (a24861@alunos.ipca.pt)
 * @brief Funções para deteção e gestão de efeitos nefastos.
 * @version 1.0
 * @date 2025-03-28
 *
 * Este módulo permite detetar interferências entre antenas com base na
 * distância mínima configurada. Sempre que duas antenas com a mesma frequência
 * estiverem demasiado próximas, são gerados efeitos nefastos ('#') nas suas
 * imediações.
 *
 * @note Os efeitos são representados por nós com frequência '#' e podem coexistir
 * com antenas na mesma posição.
 */

#pragma once
#include "geometry.h"
#include "ed.h"

/**
 * @brief Gera a lista completa de efeitos nefastos com base nas antenas.
 *
 * Percorre todos os pares de antenas com a mesma frequência (case-insensitive),
 * calcula a distância entre elas e, se for inferior à distância mínima, insere
 * dois efeitos nefastos nas direções opostas.
 *
 * @param antennas Lista ligada de antenas.
 * @param dim Dimensões da matriz.
 * @param effects Apontador para a lista onde os efeitos serão armazenados.
 * @return Número de efeitos gerados ou -1 em caso de erro.
 *
 * @note A lista de efeitos anterior é libertada automaticamente se já existir.
 * @warning Esta função pode ser custosa para grandes quantidades de antenas (O(n²)).
 */
int generate_all_effects(ED *antennas, Dimensions *dim, ED **effects);

/**
 * @brief Gera os efeitos nefastos causados por uma antena recém-inserida.
 *
 * Compara a nova antena com todas as restantes para identificar pares problemáticos
 * e, se necessário, insere os efeitos correspondentes.
 *
 * @param node Nova antena inserida.
 * @param antennas Lista total de antenas.
 * @param dim Dimensões da matriz.
 * @param effects Lista de efeitos a ser atualizada.
 * @return Número de efeitos gerados ou -1 em caso de erro.
 *
 * @note Útil após inserções dinâmicas. Não limpa efeitos anteriores.
 * @see insert_effect_at
 */
int detect_effects_for_node(ED *node, ED *antennas, Dimensions *dim, ED **effects);

/**
 * @brief Remove os efeitos causados por uma determinada antena.
 *
 * @param node Antena a ser removida.
 * @param antennas Lista atual de antenas.
 * @param dim Dimensões da matriz.
 * @param effects Lista de efeitos a atualizar.
 * @return Número de efeitos removidos.
 */
int remove_effects_for_node(ED *node, ED *antennas, Dimensions *dim, ED **effects);
