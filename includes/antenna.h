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


 typedef struct Antenna {
     char frequency;      /**< Frequência da antena */
     int x, y;           /**< Coordenadas da antena na matriz */
     struct Antenna *next; /**< Apontador para a próxima antena na lista */
 } Antenna;
 
 Antenna* createAntenna(char frequency, int x, int y);
 Antenna* insertAntenna(Antenna* head, char frequency, int x, int y);
 Antenna* removeAntenna(Antenna* head, int x, int y);
 void listAntennas(Antenna* head);
 void freeAntennaList(Antenna* head);