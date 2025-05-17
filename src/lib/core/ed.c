/**
 * @file ed.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-03-29
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "core/ed.h"

ED *create_ed(char frequency, int x, int y)
{
  ED *new_node = (ED *)malloc(sizeof(ED));

  if (!new_node)
    return NULL;

  new_node->frequency = frequency;
  new_node->x = x;
  new_node->y = y;
  new_node->next = NULL;

  return new_node;
}

int insert_ed(ED **head, ED *new_node)
{
  if (!head || !new_node)
    return 0;

  if (*head == NULL ||
      new_node->y < (*head)->y ||
      (new_node->y == (*head)->y && new_node->x < (*head)->x))
  {
    // Insere no início
    new_node->next = *head;
    *head = new_node;
    return 1;
  }

  ED *current = *head;
  while (current->next &&
         (current->next->y < new_node->y ||
          (current->next->y == new_node->y && current->next->x < new_node->x)))
  {
    current = current->next;
  }

  // Insere entre current e current->next (pode ser fim)
  new_node->next = current->next;
  current->next = new_node;
  return 1;
}

ED *find_ed(ED *head, int x, int y)
{
  ED *current = head;
  while (current != NULL)
  {
    if (current->x == x && current->y == y)
      return current;
    current = current->next;
  }
  return NULL;
}

int remove_ed(ED **head, int x, int y)
{
  if (!head || !(*head))
    return 0;

  ED *current = *head;
  ED *previous = NULL;

  while (current != NULL)
  {
    if (current->x == x && current->y == y)
    {
      if (previous == NULL)
      {
        // remover o primeiro
        *head = current->next;
      }
      else
      {
        previous->next = current->next;
      }

      free(current);
      return 1;
    }

    previous = current;
    current = current->next;
  }

  return 0; // não foi encontrado
}

int free_ed_list(ED **head)
{
  if (!head || !(*head))
    return 0;

  ED *current = *head;
  while (current != NULL)
  {
    ED *temp = current;
    current = current->next;
    free(temp);
  }

  *head = NULL;
  return 1;
}
