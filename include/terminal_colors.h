/**
 * @file terminal_colors.h
 * @author Rúben Oliveira (a24861@alunos.ipca.pt)
 * @brief Definições de macros ANSI para formatação colorida no terminal.
 * @version 1.0
 * @date 2025-03-29
 *
 * Este ficheiro contém definições de escape ANSI para aplicar cores e estilos
 * no texto impresso no terminal, melhorando a experiência de visualização.
 *
 * @note Compatível com a maioria dos terminais Unix/Linux e alguns terminais modernos no Windows.
 */

#pragma once

/// @name Estilos de texto
/// @{
#define ANSI_RESET "\x1b[0m" /** Remove todas as formatações ativas */
#define ANSI_BOLD "\x1b[1m"  /** Texto em negrito */
/// @}

/// @name Cores de texto
/// @{
#define ANSI_RED "\x1b[31m"    /** Texto vermelho (erros, alertas) */
#define ANSI_GREEN "\x1b[32m"  /** Texto verde (sucesso, confirmações) */
#define ANSI_YELLOW "\x1b[33m" /** Texto amarelo (avisos, destaques) */
/// @}
