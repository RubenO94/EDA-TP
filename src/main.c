/**
 * @file main.c
 * @author Rúben Oliveira
 * @brief Ponto de entrada da aplicação com execução estática para validação da Fase 2.
 * @version 1.0
 * @date 2025-03-14
 */

#include <stdio.h>
#include "core/graph.h"
#include "core/algorithms.h"
#include "io/graph_io.h"
#include "ui/menu.h"

/**
 * @brief Função principal que executa o ciclo estático do projeto (Happy Path).
 * @return 0 em caso de sucesso, 1 em caso de erro.
 */
int main(void)
{
  // !!! Descomentar para ativar o menu da Fase 1
  // start_menu();

  printf("== INÍCIO DO HAPPY PATH ==\n");

  // =========================
  // 1. Carregar grafo do .txt
  // =========================
  GR *g = graph_create();
  if (!graph_load_from_txt("input/matriz.txt", g))
  {
    fprintf(stderr, "Erro ao carregar input/matriz.txt\n");
    return 1;
  }

  // =========================
  // 2. Conectar vértices adjacentes com mesma frequência
  // =========================
  graph_connect_adjacent_nodes(g);

  // =========================
  // 3. Imprimir grafo carregado
  // =========================
  printf("\n--- Grafo carregado ---\n");
  graph_print(g);

  // =========================
  // 4. BFS e DFS a partir de um vértice conhecido
  // =========================
  Vertex *start = graph_find_vertex(g, 0, 0); // Exemplo: vértice 'B'
  if (!start)
  {
    fprintf(stderr, "Vértice de partida não encontrado.\n");
    graph_free(g);
    return 1;
  }

  printf("\n--- BFS a partir de (%d, %d) ---\n", start->x, start->y);
  Vertex *bfs_result = graph_bfs(start);
  graph_print_vertices(bfs_result);
  graph_clear_visits(g);

  printf("\n--- DFS a partir de (%d, %d) ---\n", start->x, start->y);
  Vertex *dfs_result = graph_dfs(start);
  graph_print_vertices(dfs_result);
  graph_clear_visits(g);

  // =========================
  // 5. Caminhos e interseções (opcional)
  // =========================
  /*
  Vertex *end = graph_find_vertex(g, 4, 2);
  if (end) {
    printf("\n--- Todos os caminhos de (%d,%d) para (%d,%d) ---\n", start->x, start->y, end->x, end->y);
    graph_find_all_paths(start, end);
    graph_clear_visits(g);
  }

  printf("\n--- Interseções entre frequências A e B ---\n");
  graph_list_frequency_intersections(g, 'A', 'B');
  */

  // =========================
  // 6. Guardar grafo em .bin
  // =========================
  printf("\n--- Guardar em grafo.bin ---\n");
  if (!graph_save_to_bin("grafo.bin", g))
  {
    fprintf(stderr, "Erro ao guardar grafo.bin\n");
    graph_free(g);
    return 1;
  }
  printf("Grafo guardado com sucesso.\n");

  // =========================
  // 7. Carregar grafo de .bin
  // =========================
  printf("\n--- Carregar grafo de grafo.bin ---\n");
  GR *g2 = graph_load_from_bin("grafo.bin");
  if (!g2)
  {
    fprintf(stderr, "Erro ao carregar grafo.bin\n");
    graph_free(g);
    return 1;
  }

  graph_print(g2);

  // =========================
  // 8. Limpeza
  // =========================
  graph_free(g);
  graph_free(g2);

  printf("\n== FIM DO HAPPY PATH ==\n");
  return 0;
}
