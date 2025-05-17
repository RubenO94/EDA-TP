/**
 * @file graph.h
 * @author Rúben Oliveira (24861)
 * @brief Estruturas e funções para criação e manipulação de grafos dinâmicos de antenas.
 * @version 1.0
 * @date 2025-05-16
 *
 * Este módulo permite representar uma cidade como um grafo onde cada vértice corresponde a uma antena
 * com coordenadas e frequência, e as ligações representam conexões entre antenas com a mesma frequência.
 */

#pragma once

// === Enum de validação de vértices ===

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

// === Estruturas de dados ===

// Declaração antecipada para usar apontadores cruzados
struct Vertex;

/**
 * @brief Representa uma aresta (ligação) entre dois vértices.
 */
typedef struct Adj_Node
{
  struct Vertex *dest;   /** Vértice de destino da ligação */
  struct Adj_Node *next; /** Próxima ligação na lista de adjacências */
} Adj_Node;

/**
 * @brief Representa um vértice no grafo (antena com frequência e posição).
 */
typedef struct Vertex
{
  char frequency;      /** Frequência da antena (A-Z ou a-z) */
  int x, y;            /** Coordenadas da antena na matriz */
  int visited;         /** 0 = não visitado, 1 = visitado */
  Adj_Node *adj_list;  /** Lista ligada de adjacências (arestas) */
  struct Vertex *next; /** Próximo vértice na lista de vértices do grafo */
} Vertex;

/**
 * @brief Representa o grafo completo (lista de vértices + contador).
 */
typedef struct GR
{
  Vertex *head;     /** Cabeça da lista de vértices */
  int vertex_count; /** Número total de vértices no grafo */
} GR;

// === Funções de manipulação do grafo ===

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
 * @return Apontador para o novo vértice criado, ou NULL em caso de erro ou dados inválidos.
 */
Vertex *graph_create_vertex(char frequency, int x, int y);

/**
 * @brief Adiciona um vértice previamente criado ao grafo.
 *
 * @param g Grafo onde será adicionado.
 * @param v Vértice criado com graph_create_vertex.
 * @return 1 em caso de sucesso, 0 se já existir vértice com as mesmas coordenadas.
 */
int graph_add_vertex(GR *g, Vertex *v);

/**
 * @brief Procura um vértice no grafo com base nas coordenadas.
 *
 * @param g Grafo a pesquisar.
 * @param x Coordenada X.
 * @param y Coordenada Y.
 * @return Apontador para o vértice encontrado ou NULL se não existir.
 */
Vertex *graph_find_vertex(GR *g, int x, int y);

/**
 * @brief Adiciona uma aresta entre dois vértices (ligações unidirecional).
 *
 * @param from Vértice de origem.
 * @param to Vértice de destino.
 * @return 1 em caso de sucesso, 0 se as frequências forem diferentes ou erro de alocação.
 */
int graph_add_edge(Vertex *from, Vertex *to);

/**
 * @brief Liberta toda a memória associada ao grafo.
 *
 * @param g Grafo a libertar.
 * @return 1 se a limpeza foi bem-sucedida, 0 se o grafo já estava vazio ou inválido.
 */
int graph_free(GR *g);

/**
 * @brief Imprime todos os vértices do grafo e suas conexões.
 *
 * @param g Grafo a imprimir.
 */
void graph_print(GR *g);

// === Validação ===

/**
 * @brief Valida os dados de um novo vértice antes de o criar/adicionar.
 *
 * @param g Grafo onde o vértice será inserido.
 * @param frequency Letra da frequência da antena.
 * @param x Posição X.
 * @param y Posição Y.
 * @return Código de validação (enum VertexValidation).
 */
int graph_validate_vertex(GR *g, char frequency, int x, int y);
