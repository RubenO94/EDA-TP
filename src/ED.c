#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "ED.h"

ED* createED(char frequency, int x, int y){
    ED * newNode = (ED*) malloc(sizeof(ED));

    if(!newNode) return NULL;

    newNode->frequency = frequency;
    newNode->x = x;
    newNode->y = y;
    newNode->next = NULL;

    return newNode;
}

ED* insertED(ED* head, ED* newNode) {
    if (!newNode) return head;
    newNode->next = head;
    return newNode;
}


