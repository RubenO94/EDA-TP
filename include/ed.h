/**
 * @file ed.h
 * @author Rúben Oliveira (a24861@alunos.ipca.pt)
 * @brief Definição da estrutura ED e funções associadas à gestão de antenas e efeitos.
 * @version 1.0
 * @date 2025-03-14
 *
 * Estrutura de dados reutilizável para representar elementos na matriz, como antenas ou efeitos nefastos,
 * com suporte para inserção, remoção e pesquisa numa lista ligada ordenada.
 */

#pragma once

#pragma region Structs

/**
 * @brief Estrutura que representa um elemento da lista ligada (antena ou efeito).
 *
 * Cada elemento contém uma frequência (carácter) e a sua posição na matriz (x, y).
 * A lista é mantida ordenada por coordenadas, para facilitar pesquisa e inserção.
 *
 * @note A frequência '#' representa um efeito nefasto.
 */
typedef struct ed
{
  char frequency;  /** Frequência da antena (A-Z, a-z) ou '#' para efeito nefasto. */
  int x, y;        /** Coordenadas (coluna x, linha y) na matriz. */
  struct ed *next; /** Apontador para o próximo nó na lista. */
} ED;

#pragma endregion Structs

#pragma region Function_Contracts

/**
 * @brief Cria um novo nó da estrutura ED com frequência e coordenadas especificadas.
 *
 * @param frequency Carácter da frequência ('A'-'Z', 'a'-'z' ou '#').
 * @param x Coordenada X (coluna).
 * @param y Coordenada Y (linha).
 * @return Apontador para o novo nó criado, ou NULL em caso de falha.
 */
ED *create_ed(char frequency, int x, int y);

/**
 * @brief Insere um nó na lista ligada, mantendo a ordem crescente por coordenadas (y, depois x).
 *
 * @param head Apontador para o início da lista.
 * @param new_node Nó previamente criado (não pode ser NULL).
 * @return 1 em caso de sucesso, 0 se falhar (ex: lista nula ou inserção inválida).
 *
 * @warning O nó não será inserido se as coordenadas já existirem na lista.
 * @note Útil para manter a matriz virtual consistente.
 */
int insert_ed(ED **head, ED *new_node);

/**
 * @brief Procura um nó na lista com as coordenadas indicadas.
 *
 * @param head Início da lista ligada.
 * @param x Coordenada X a procurar.
 * @param y Coordenada Y a procurar.
 * @return Apontador para o nó correspondente, ou NULL se não for encontrado.
 *
 * @see remove_ed
 */
ED *find_ed(ED *head, int x, int y);

/**
 * @brief Remove o nó com as coordenadas indicadas da lista ligada.
 *
 * @param head Apontador para o início da lista.
 * @param x Coordenada X.
 * @param y Coordenada Y.
 * @return 1 se o nó foi removido com sucesso, 0 se não for encontrado.
 *
 * @note Após a remoção, a memória é libertada.
 */
int remove_ed(ED **head, int x, int y);

/**
 * @brief Liberta toda a memória da lista ligada e define o apontador como NULL.
 *
 * @param head Apontador para o início da lista.
 * @return 1 em caso de sucesso, 0 se a lista já estiver vazia ou o apontador for inválido.
 *
 * @note Deve ser usado antes de recarregar ou sair da aplicação para evitar memory leaks.
 */
int free_ed_list(ED **head);

#pragma endregion Function_Contracts
