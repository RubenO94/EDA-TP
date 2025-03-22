#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "ED.h"

ED* create_ed(char frequency, int x, int y){
    ED * newNode = (ED*) malloc(sizeof(ED));

    if(!newNode) return NULL;

    newNode->frequency = frequency;
    newNode->x = x;
    newNode->y = y;
    newNode->next = NULL;

    return newNode;
}

ED* insert_ed(ED* head, ED* newNode) {
    if (!newNode) return head;
    newNode->next = head;
    return newNode;
}


ED* remove_ed(ED* head, int x, int y){

    // TODO: algoritmo para remover um node
    return head;
}