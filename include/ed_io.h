/**
 * @file ed_io.h
 * @author Rúben Oliveira (a24861@alunos.ipca.pt)
 * @brief Operações de entrada/saída em ficheiros de antenas e efeitos.
 * @version 1.0
 * @date 2025-03-21
 *
 * Fornece funções para guardar e carregar listas ligadas de antenas e efeitos (ED)
 * em ficheiros binários, assim como carregar mapas de texto (.txt).
 */

#pragma once

#include "ed.h"
#include "geometry.h"
#include "constants.h"

/**
 * @brief Guarda todas as informações do projeto num ficheiro binário.
 *
 * Armazena:
 *
 * - Lista de antenas (com as suas frequências e posições)
 *
 * - Lista de efeitos nefastos
 *
 * - Dimensões da matriz
 *
 * @param antennas Lista ligada de antenas a guardar.
 * @param effects Lista ligada de efeitos a guardar.
 * @param dim Ponteiro para a estrutura Dimensions com o número de linhas e colunas.
 * @param filepath Caminho do ficheiro binário onde será guardado o projeto.
 * @return 1 em caso de sucesso, 0 em caso de falha (ex: erro de escrita).
 *
 * @note O formato do ficheiro é específico desta aplicação. Não deve ser editado manualmente.
 */
int save_all_to_bin(ED *antennas, ED *effects, Dimensions *dim, const char *filepath);

/**
 * @brief Carrega um projeto completo a partir de um ficheiro binário.
 *
 * Lê os dados binários previamente guardados com `save_all_to_bin` e preenche:
 *
 * - A lista de antenas
 *
 * - A lista de efeitos
 *
 * - As dimensões da matriz
 *
 * @param[out] antennas Apontador para a cabeça da lista de antenas (será preenchido).
 * @param[out] effects Apontador para a cabeça da lista de efeitos (será preenchido).
 * @param[out] dim Estrutura Dimensions onde serão armazenadas as dimensões da matriz.
 * @param filepath Caminho do ficheiro binário a carregar.
 * @return 1 em caso de sucesso, 0 se ocorrer algum erro (ex: ficheiro inválido ou corrompido).
 *
 * @warning Substitui os dados atualmente carregados nas estruturas fornecidas.
 * @note Certifique-se de libertar a memória anterior antes de carregar um novo projeto.
 */
int load_all_from_bin(ED **antennas, ED **effects, Dimensions *dim, const char *filepath);

/**
 * @brief Carrega uma matriz de antenas a partir de um ficheiro de texto (.txt).
 *
 * A função percorre linha a linha o ficheiro, interpretando cada carácter como uma possível antena.
 * Apenas letras alfabéticas (A-Z, a-z) são consideradas válidas e inseridas na lista ligada.
 * Carateres como espaços ou '#' (efeitos nefastos) são ignorados, pois os efeitos serão gerados automaticamente.
 *
 * Também calcula e preenche as dimensões da matriz com base no conteúdo do ficheiro.
 *
 * @param filepath Caminho para o ficheiro de texto com a matriz.
 * @param[out] head Apontador onde será guardada a cabeça da lista de antenas carregadas.
 * @param[out] dim Estrutura onde serão armazenadas as dimensões (linhas e colunas) da matriz.
 * @return 1 se a matriz for carregada com sucesso, 0 em caso de falha.
 *
 * @note O ficheiro .txt deve estar corretamente formatado com caracteres válidos por linha.
 */
int load_matrix(const char *filepath, ED **head, Dimensions *dim);
