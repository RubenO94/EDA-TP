/**
 * @file antenna.h
 * @author Rúben Oliveira (a24861@alunos.ipca.pt)
 * @brief Definição da estrutura e funções para a antena (lista ligada)
 * @version 0.1
 * @date 2025-03-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */


 #pragma once

/**
 * @brief 
 * 
 */
 typedef struct ED {
     char frequency;      /** Frequência da antena */
     int x, y;           /** Coordenadas da antena na matriz */
     struct ED *next; /** Apontador para a próxima antena na lista */
 } ED;
 
 /**
  * @brief 
  * 
  */
 typedef struct {
    ED* head;
    ED* tail;
} ED_List;

/**
 * @brief Cria um novo nó na estrutura ED.
 * @param frequency Tipo do nó ('A-Z, a-z' para antena, '#' para efeito nefasto).
 * @param x Coordenada X.
 * @param y Coordenada Y.
 * @return Apontador para o novo nó criado.
 */
ED* create_ed(char frequency, int x, int y);

/**
 * @brief Insere um nó já criado na estrutura ED.
 * @param head Apontador para a cabeça da lista ED.
 * @param newNode Apontador para o nó criado previamente.
 * @return Apontador atualizado da estrutura ED.
 */
ED* insert_ed(ED* head, ED* newNode);


/**
 * @brief 
 * 
 * @param head 
 * @param x 
 * @param y 
 * @return ED* 
 */
ED* remove_ed(ED* head, int x, int y);