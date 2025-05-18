/**
 * @file graph.h
 * @author Rúben Oliveira
 * @brief Estruturas e funções para criação e manipulação de grafos dinâmicos de antenas.
 * @version 1.0
 * @date 2025-05-10
 *
 * Este módulo permite representar uma cidade como um grafo onde cada vértice corresponde a uma antena
 * com coordenadas e frequência, e as ligações representam conexões entre antenas com a mesma frequência.
 */

#pragma once

// =========================
// ENUMS E ESTRUTURAS
// =========================

/**
 * @brief Códigos de validação para um novo vértice antes de ser inserido no grafo.
 */
typedef enum
{
  VALID = 0,           /** Vértice válido */
  INVALID_FREQUENCY,   /** Frequência inválida (não alfabética) */
  INVALID_COORDINATES, /** Coordenadas negativas */
  DUPLICATE_VERTEX     /** Já existe um vértice nessas coordenadas */
} VertexValidation;

// Declaração antecipada para apontadores cruzados
struct Vertex;

/**
 * @brief Representa uma aresta (ligação) entre dois vértices.
 */
typedef struct Adj_Node
{
  struct Vertex *dest;
  struct Adj_Node *next;
} Adj_Node;

/**
 * @brief Representa um vértice no grafo (antena com frequência e posição).
 */
typedef struct Vertex
{
  char frequency;
  int x, y;
  int visited; /** 0 = não visitado, 1 = visitado */
  Adj_Node *adj_list;
  struct Vertex *next;
} Vertex;

/**
 * @brief Representa o grafo completo (lista de vértices + contador).
 */
typedef struct GR
{
  Vertex *head;
  int vertex_count;
} GR;

// =========================
// CRIAÇÃO
// =========================

/**
 * @brief Cria um novo grafo vazio.
 * @return Apontador para o grafo criado, ou NULL em caso de erro.
 */
GR *graph_create();

/**
 * @brief Cria um novo vértice com os dados fornecidos (sem inseri-lo no grafo).
 *
 * @param frequency Carácter representando a frequência da antena.
 * @param x Coordenada X (coluna).
 * @param y Coordenada Y (linha).
 * @return Apontador para o novo vértice criado, ou NULL em caso de erro.
 */
Vertex *graph_create_vertex(char frequency, int x, int y);

// =========================
// INSERÇÃO E ESTRUTURAÇÃO
// =========================

/**
 * @brief Adiciona um vértice previamente criado ao grafo, mantendo a ordem por Y e X.
 *
 * @param g Grafo onde será adicionado.
 * @param v Vértice criado com graph_create_vertex.
 * @return 1 em caso de sucesso, 0 se já existir um vértice com as mesmas coordenadas.
 */
int graph_add_vertex(GR *g, Vertex *v);

/**
 * @brief Adiciona uma aresta entre dois vértices (ligação unidirecional).
 *
 * Só adiciona se ambos tiverem a mesma frequência e se a ligação ainda não existir.
 *
 * @param from Vértice de origem.
 * @param to Vértice de destino.
 * @return 1 em caso de sucesso, 0 em caso de erro.
 */
int graph_add_edge(Vertex *from, Vertex *to);

/**
 * @brief Liga automaticamente vértices adjacentes com a mesma frequência.
 *
 * Para cada vértice, verifica os 8 vizinhos na matriz (cima, baixo, lados e diagonais).
 * Se houver um vizinho com a mesma frequência e ainda não estiver ligado, cria uma ligação bidirecional.
 *
 * @param g Grafo a processar.
 * @return 1 em caso de sucesso, 0 se o grafo for inválido.
 */
int graph_connect_adjacent_nodes(GR *g);

// =========================
// BUSCAS E CONSULTAS
// =========================

/**
 * @brief Procura um vértice no grafo com base nas coordenadas.
 *
 * @param g Grafo a pesquisar.
 * @param x Coordenada X.
 * @param y Coordenada Y.
 * @return Apontador para o vértice encontrado ou NULL se não existir.
 */
Vertex *graph_find_vertex(GR *g, int x, int y);

// =========================
// VALIDAÇÃO
// =========================

/**
 * @brief Valida os dados de um novo vértice antes de o criar/adicionar.
 *
 * Verifica se a frequência é alfabética, se as coordenadas são válidas
 * e se já existe um vértice com as mesmas coordenadas.
 *
 * @param g Grafo onde o vértice será inserido.
 * @param frequency Letra da frequência da antena.
 * @param x Posição X.
 * @param y Posição Y.
 * @return Código de validação (enum VertexValidation).
 */
int graph_validate_vertex(GR *g, char frequency, int x, int y);

// =========================
// UTILITÁRIOS
// =========================

/**
 * @brief Limpa o campo `visited` de todos os vértices do grafo.
 * @param g Grafo a limpar.
 * @return 1 em caso de sucesso, 0 se o grafo for inválido.
 */
int graph_clear_visits(GR *g);

/**
 * @brief Liberta toda a memória associada ao grafo.
 * @param g Grafo a libertar.
 * @return 1 se a limpeza foi bem-sucedida, 0 se o grafo for inválido.
 */
int graph_free(GR *g);

/**
 * @brief Imprime todos os vértices do grafo e suas conexões.
 * @param g Grafo a imprimir.
 */
void graph_print(GR *g);

/**
 * @brief Imprime uma lista ligada de vértices visitados (ex: BFS, DFS).
 */
void graph_print_vertices(Vertex *list);
