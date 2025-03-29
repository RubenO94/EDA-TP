/**
 * @file ed_io.h
 * @author Rúben Oliveira (a24861@alunos.ipca.pt)
 * @brief Funções responsáveis por carregar, guardar e apresentar listas ED e metadados da matriz.
 * @version 0.1
 * @date 2025-03-21
 * @copyright Copyright (c) 2025
 */

#pragma once

#include "ed.h"
#include "dimensions.h"
#include "constants.h"

/**
 * @brief Modo de impressão da matriz.
 */
typedef enum
{
    PRINT_ANTENNAS_ONLY, // Imprime apenas as antenas
    PRINT_WITH_EFFECTS   // Imprime antenas e efeitos nefastos (se existirem)
} PrintMode;

/**
 * @brief Guarda a lista ligada ED num ficheiro binário.
 *
 * @param head Apontador para a cabeça da lista a guardar.
 * @param filename Nome do ficheiro binário de destino.
 * @return 1 em caso de sucesso, 0 em caso de erro (ex: erro de escrita ou ficheiro).
 */
int save_ed_to_bin(ED *head, const char *filename);

/**
 * @brief Carrega uma lista ligada ED a partir de um ficheiro binário.
 *
 * @param filename Nome do ficheiro binário de origem.
 * @return Apontador para a cabeça da nova lista carregada ou NULL em caso de erro.
 */
ED *load_ed_from_bin(const char *filename);

/**
 * @brief Carrega uma matriz de antenas a partir de um ficheiro de texto.
 *
 * Apenas os caracteres válidos (A-Z, a-z) são inseridos na lista. O caractere '#' é ignorado por representar efeitos e será gerado posteriormente.
 * A função também determina as dimensões da matriz (linhas e colunas).
 *
 * @param filepath Caminho para o ficheiro .txt com a matriz.
 * @param head Apontador para onde será guardada a cabeça da lista de antenas.
 * @param dim Estrutura onde serão guardadas as dimensões da matriz carregada.
 * @return 1 em caso de sucesso, 0 em caso de falha (ex: ficheiro inválido).
 */
int load_matrix(const char *filepath, ED **head, Dimensions *dim);

/**
 * @brief Imprime a matriz no terminal com base nas antenas e (opcionalmente) nos efeitos.
 *
 * A matriz é impressa no formato linha × coluna com as seguintes representações:
 * - '.' para posição vazia
 * - 'A-Z' para antenas
 * - '#' para efeitos
 * - '#A' quando há efeito e antena na mesma posição
 *
 * @param antennas Lista ligada de antenas (obrigatória).
 * @param effects Lista ligada de efeitos (opcional, consoante o modo).
 * @param dim Estrutura com as dimensões da matriz.
 * @param mode Modo de impressão (somente antenas ou antenas + efeitos).
 */
void print_matrix(ED *antennas, ED *effects, Dimensions *dim, PrintMode mode);
