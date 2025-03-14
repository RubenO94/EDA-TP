#include <stdio.h>
#include <stdlib.h>
#include "antenna.h"

Antenna* createAntenna(char frequency, int x, int y) {
    Antenna* newAntenna = (Antenna*)malloc(sizeof(Antenna));
    if (!newAntenna) return NULL;
    newAntenna->frequency = frequency;
    newAntenna->x = x;
    newAntenna->y = y;
    newAntenna->next = NULL;
    return newAntenna;
}

Antenna* insertAntenna(Antenna* head, char frequency, int x, int y) {
    Antenna* newAntenna = createAntenna(frequency, x, y);
    if (!newAntenna) return head;
    newAntenna->next = head;
    return newAntenna;
}

Antenna* removeAntenna(Antenna* head, int x, int y) {
    Antenna *current = head, *previous = NULL;
    while (current) {
        if (current->x == x && current->y == y) {
            if (previous) previous->next = current->next;
            else head = current->next;
            free(current);
            return head;
        }
        previous = current;
        current = current->next;
    }
    return head;
}

void listAntennas(Antenna* head) {
    Antenna* current = head;
    printf("List of Antennas:\n");
    while (current) {
        printf("Frequency: %c | Position: (%d, %d)\n", current->frequency, current->x, current->y);
        current = current->next;
    }
}

void freeAntennaList(Antenna* head) {
    while (head) {
        Antenna* temp = head;
        head = head->next;
        free(temp);
    }
}
