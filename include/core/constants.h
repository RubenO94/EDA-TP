/**
 * @file constants.h
 * @author Rúben Oliveira (a24861@alunos.ipca.pt)
 * @brief Constantes globais utilizadas em todo o projeto.
 * @version 1.0
 * @date 2025-03-28
 *
 * Este ficheiro centraliza todas as definições de constantes que são
 * reutilizadas ao longo do sistema, permitindo uma fácil manutenção.
 *
 * @copyright Copyright (c) 2025
 */

#pragma once

/**
 * @brief Tamanho máximo de uma linha lida de um ficheiro .txt.
 *
 * Usado na leitura da matriz a partir de ficheiros de texto.
 */
#define MAX_LINE_LENGTH 1024

/**
 * @brief Tamanho máximo permitido para nomes de ficheiros.
 *
 * Inclui o nome base e extensão, por exemplo: "projeto1.bin".
 */
#define MAX_FILENAME_LENGTH 100

/**
 * @brief Distância mínima aceitável entre antenas da mesma frequência.
 *
 * Caso duas antenas estejam mais próximas do que este valor e tenham
 * a mesma frequência (ignorando maiúsculas/minúsculas), será gerado
 * um efeito nefasto entre elas.
 *
 * @note O valor deve ser >= 1 para garantir comportamentos válidos.
 */
#define MIN_EFFECT_DISTANCE 2

/**
 * @brief Carácter que representa um efeito nefasto na matriz.
 *
 * Usado na impressão da matriz e ao guardar os dados no sistema.
 */
#define EFFECT_SYMBOL '#'

/**
 * @brief Caminho padrão para o ficheiro .txt com a matriz inicial.
 *
 * Utilizado quando não é especificado outro caminho pelo utilizador.
 */
#define DEFAULT_MATRIX_PATH "input/matriz.txt"

/**
 * @brief Diretório onde os projetos (ficheiros .bin) são guardados.
 *
 * @note Este diretório deve existir previamente ou ser criado manualmente.
 */
#define PROJECTS_PATH "data/"

/**
 * @brief Tamanho máximo do caminho de um ficheiro (path).
 *
 * Inclui diretório, nome do ficheiro e extensão.
 */
#define MAX_PATH 256

/**
 * @brief
 *
 */
#define MAX_VERTICES 1000

#define VERTEX_END_MARKER 9999
