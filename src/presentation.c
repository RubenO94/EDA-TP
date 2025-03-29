#include <stdio.h>
#include "presentation.h"

void print_ed_list(ED *head, const char *titulo)
{
    printf("\n--- %s ---\n", titulo);
    printf("Símbolo    |  X  |  Y\n");
    printf("-----------|-----|-----\n");

    while (head != NULL)
    {
        printf("     %c     | %3d | %3d\n", head->frequency, head->x, head->y);
        head = head->next;
    }
}

void print_menu(void)
{
    printf("\n=== Antena Analyzer ===\n");
    printf("1. Carregar matriz\n");
    printf("2. Apresentar matriz\n");
    printf("6. Inserir nova antena\n");
    printf("3. Remover antena\n");
    printf("4. Detetar efeitos nefastos\n");
    printf("5. Listar efeitos nefastos\n");
    printf("7. Sair\n");
    printf("Escolha uma opção: ");
}
