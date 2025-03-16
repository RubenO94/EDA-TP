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


 typedef struct ED {
     char frequency;      /**< Frequência da antena */
     int x, y;           /**< Coordenadas da antena na matriz */
     struct ED *next; /**< Apontador para a próxima antena na lista */
 } ED;
 

/**
 * @brief Cria um novo nó na estrutura ED.
 * @param type Tipo do nó ('A-Z, a-z' para antena, '#' para efeito nefasto).
 * @param x Coordenada X.
 * @param y Coordenada Y.
 * @return Apontador para o novo nó criado.
 */
ED* createED(char type, int x, int y);


/**
 * @brief Insere um nó já criado na estrutura ED.
 * @param head Apontador para a cabeça da lista ED.
 * @param newNode Apontador para o nó criado previamente.
 * @return Apontador atualizado da estrutura ED.
 */
ED* insertED(ED* head, ED* newNode);



 ED* insertAntenna(ED* head, char frequency, int x, int y);
 ED* removeAntenna(ED* head, int x, int y);
 void listAntennas(ED* head);
 void freeAntennaList(ED* head);