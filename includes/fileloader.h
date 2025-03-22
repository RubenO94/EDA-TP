/**
 * @file fileloader.h
 * @author Rúben Oliveira (a24861@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 2025-03-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include "antenna.h"

/**
 * @brief Carrega uma matriz de antenas a partir de um ficheiro.
 * @param filename Nome do ficheiro.
 * @return Lista ligada com as antenas encontradas.
 */
ED* load_antennas_from_file(const char* filename);
