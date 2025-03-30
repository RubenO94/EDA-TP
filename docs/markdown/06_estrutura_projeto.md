## 5. Estrutura do Projeto e Arquitetura

### 5.1 Convenções e Estilo de Código

Durante o desenvolvimento do projeto, optei por adotar o estilo de nomeação `snake_case` para funções e variáveis, em detrimento do `CamelCase`. Esta escolha prende-se com o facto de `snake_case` ser amplamente utilizado em projetos escritos em linguagem C, por oposição a `CamelCase`, mais comum em linguagens orientadas a objetos como Java ou C#.

Algumas convenções utilizadas:

- **Funções e variáveis:** `snake_case`, ex: `insert_ed`, `load_from_file`
- **Estruturas e tipos personalizados:** `CamelCase`, ex: `ED`, `Dimensions`
- **Constantes:** Maiúsculas com underscore, ex: `MAX_ROWS`, `MIN_DISTANCE`
- **Ficheiros `.c` e `.h`:** nomes em minúsculas com underscore, ex: `ed_utils.c`, `ed_io.h`

Esta padronização melhora a legibilidade do código, facilita a navegação entre funções e permite distinguir visualmente os diferentes tipos de elementos presentes no projeto.

Embora o professor recomende o uso de `CamelCase`, considerei importante manter coerência com práticas mais comuns na comunidade C, especialmente em projetos que seguem filosofia de baixo nível e maior proximidade ao sistema.

### 5.2 Organização Modular

O projeto foi desenvolvido com uma abordagem modular, de forma a garantir a organização, manutenibilidade e reutilização do código. Seguindo princípios de **Clean Code**, as funções foram nomeadas de forma clara, os ficheiros foram separados conforme as suas responsabilidades, e a lógica foi dividida por módulos bem definidos.

A estrutura de diretórios segue uma organização clássica para projetos em C:

```txt
├── src/             # Código-fonte principal (implementações .c)
├── include/         # Ficheiros de cabeçalho (.h)
├── input/            # Exemplos de ficheiros de entrada
├── docs/            # Documentação e relatório
├── bin/           # Binários e ficheiros gerados
├── Doxyfile         # Configuração do Doxygen
└── README.md        # Guia de utilização e explicação do projeto
```

### Módulos e Responsabilidades

- **`main.c`** – Ponto de entrada da aplicação. Inicializa o programa, apresenta o menu e gere o ciclo principal da aplicação.
- **`controller.c / controller.h`** – Responsável pela ligação entre o menu e os módulos funcionais. Gere a lógica de controlo de fluxo do programa.
- **`menu.c / menu.h`** – Apresenta e gere o menu principal e as interações com o utilizador.
- **`display.c / display.h`** – Responsável pela apresentação formatada dos dados no terminal, como listagens tabulares e mensagens.
- **`terminal_colors.h`** – Define macros e constantes para personalização de cores no terminal (ex: ANSI escape codes).
- **`ed.c / ed.h`** – Implementa a estrutura de dados ED (lista ligada) e as operações sobre a mesma (inserção, remoção, criação de nós, etc).
- **`ed_io.c / ed_io.h`** – Responsável pelo carregamento e gravação da estrutura ED a partir de ficheiros de texto (input/output).
- **`ed_validator.c / ed_validator.h`** – Módulo com funções de validação de dados, como verificação de coordenadas duplicadas, frequências inválidas, etc.
- **`effect.c / effect.h`** – Implementa a lógica de deteção de interferências e geração de efeitos nefastos (caracter `#`).
- **`geometry.c / geometry.h`** – Contém funções relacionadas com cálculo de distâncias, alinhamentos e regras geométricas que suportam a lógica dos efeitos nefastos.
- **`constants.h`** – Define constantes globais utilizadas por vários módulos (ex: distância mínima entre antenas).

### Princípios de Clean Code aplicados

- Separação de responsabilidades por ficheiro
- Nomes de funções e variáveis descritivos e em inglês
- Utilização de funções pequenas e coesas
- Eliminação de código duplicado através de funções auxiliares `static`
- Comentários apenas onde o código não for autoexplicativo
- Documentação automática com Doxygen sobre funções públicas

Esta arquitetura permite que o projeto seja facilmente escalado ou adaptado para a Fase 2, onde será necessária a introdução de grafos.
