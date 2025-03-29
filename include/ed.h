/**
 * @file ed.h
 * @author Rúben Oliveira (a24861@alunos.ipca.pt)
 * @brief Definição da estrutura e funções comuns para antenas e efeitos nefastos.
 * @version 0.1
 * @date 2025-03-14
 *
 * @copyright Copyright (c) 2025
 */

#pragma once

#include "constants.h"

#pragma region Structs

/**
 * @brief Estrutura que representa um elemento da matriz (antena ou efeito), com frequência e coordenadas.
 */
typedef struct ed
{
    char frequency;  /**< Frequência da antena (A-Z, a-z) ou '#' para efeito */
    int x, y;        /**< Coordenadas na matriz */
    struct ed *next; /**< Apontador para o próximo nó na lista */
} ED;

#pragma endregion Structs

#pragma region Function_Contracts

/**
 * @brief Cria um novo nó na estrutura ED.
 * @param frequency Tipo do nó ('A-Z, a-z' para antena, '#' para efeito nefasto).
 * @param x Coordenada X.
 * @param y Coordenada Y.
 * @return Apontador para o novo nó criado.
 */
ED *create_ed(char frequency, int x, int y);

/**
 * @brief Insere um nó já criado na estrutura ED.
 * @param head Apontador para a cabeça da lista ED.
 * @param new_node Apontador para o nó criado previamente.
 * @return 1 em caso de sucesso, 0 em caso de falha.
 */
int insert_ed(ED **head, ED *new_node);

/**
 * @brief Procura um nó com coordenadas (x, y) na lista ligada.
 * @param head Cabeça da lista ligada.
 * @param x Coordenada x a procurar.
 * @param y Coordenada y a procurar.
 * @return Apontador para o nó se existir, NULL caso contrário.
 */
ED *find_ed(ED *head, int x, int y);

/**
 * @brief Remove o nó com coordenadas (x, y) da lista ligada.
 * @param head Apontador para o apontador da cabeça da lista.
 * @param x Coordenada X a remover.
 * @param y Coordenada Y a remover.
 * @return 1 se for removido com sucesso, 0 se não for encontrado.
 */
int remove_ed(ED **head, int x, int y);

/**
 * @brief Liberta a lista e define o apontador como NULL.
 * @param head Apontador para apontador da lista.
 * @return 1 em caso de sucesso, 0 se a lista já estiver vazia ou head nulo.
 */
int free_ed_list(ED **head);

#pragma endregion Function_Contracts
