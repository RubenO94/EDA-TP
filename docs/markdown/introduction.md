# Relatório do Projeto – Estruturas de Dados Avançadas

### Fase 1 – Listas Ligadas

## Índice

- [Introdução](#introdução)
- [Apresentação do Problema](#apresentação-do-problema)
- [Regras Definidas](#regras-definidas)
- [Estrutura de Dados Utilizada](#estrutura-de-dados-utilizada)
- [Funcionalidades Implementadas](#funcionalidades-implementadas)
- [Casos de Teste](#casos-de-teste)
- [Conclusão](#conclusão)

## Introdução

O presente trabalho foi desenvolvido no âmbito da unidade curricular de **Estruturas de Dados Avançadas**, inserida no curso de Engenharia de Sistemas Informáticos. O principal objetivo deste projeto é a aplicação prática de estruturas de dados dinâmicas, em particular listas ligadas, para resolver um problema computacional com múltiplos elementos, relações e operações sobre uma estrutura que evolui ao longo do tempo.

## Apresentação do Problema

O problema proposto consiste no desenvolvimento de um sistema para representar uma rede de antenas de transmissão, onde cada antena possui uma frequência e uma localização definida por coordenadas num plano bidimensional.

A estrutura de dados deve permitir a gestão dinâmica dessa rede, com funcionalidades como inserção, remoção e análise de possíveis interferências entre antenas. Para além das antenas, o sistema deverá ser capaz de representar zonas afetadas por interferência, de acordo com critérios previamente definidos.

O sistema deve ainda ser capaz de carregar e guardar a informação da rede num ficheiro de texto, permitindo o armazenamento de diferentes versões ou estados da estrutura ao longo do tempo.

## Regras Definidas

Durante o desenvolvimento deste projeto, foi necessário estabelecer um conjunto de regras e restrições adicionais que não estavam explícitas no enunciado original, com o objetivo de tornar o comportamento da estrutura mais consistente e realista face ao problema modelado.

As principais regras definidas foram as seguintes:

- **Frequência case-insensitive:** As frequências das antenas são tratadas de forma insensível a maiúsculas e minúsculas. Por exemplo, uma antena com frequência `'A'` será considerada igual a uma com frequência `'a'`.
- **Carácter reservado `'#'`:** O carácter `'#'` está reservado para representar zonas de interferência ou efeitos nefastos, e não pode ser utilizado como frequência de uma antena.
- **Proibição de coordenadas duplicadas:** Não é permitida a existência de duas antenas na mesma posição (coordenadas x e y). No entanto, uma posição já ocupada por uma antena pode conter adicionalmente um efeito nefasto, caso este ocorra.
- **Distância mínima entre antenas da mesma frequência:** Foi definido um limite mínimo de distância entre antenas com a mesma frequência. Se duas antenas violarem essa distância mínima, considera-se que existe interferência, sendo gerado um efeito nefasto entre elas.
- **Área afetada pelo efeito nefasto:** Quando ocorre interferência, é registado um conjunto de posições afetadas ao redor da zona central do conflito. A extensão dessa área pode variar consoante a distância entre as antenas em conflito.
- **Modularização e separação de responsabilidades:** O projeto foi organizado em múltiplos módulos (`ed_io`, `ed_validator`, `ed_effects`, etc.), sendo utilizadas funções auxiliares `static` para validações internas, garantindo encapsulamento e reutilização de código.

