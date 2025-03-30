## 3. Regras Definidas

Durante o desenvolvimento deste projeto, foi necessário estabelecer um conjunto de regras e restrições adicionais que não estavam explícitas no enunciado original, com o objetivo de tornar o comportamento da estrutura mais consistente e realista face ao problema modelado.

As principais regras definidas foram as seguintes:

- **Frequência case-insensitive:** As frequências das antenas são tratadas de forma insensível a maiúsculas e minúsculas. Por exemplo, uma antena com frequência `'A'` será considerada igual a uma com frequência `'a'`.
- **Carácter reservado `'#'`:** O carácter `'#'` está reservado para representar zonas de interferência ou efeitos nefastos, e não pode ser utilizado como frequência de uma antena.
- **Proibição de coordenadas duplicadas:** Não é permitida a existência de duas antenas na mesma posição (coordenadas x e y). No entanto, uma posição já ocupada por uma antena pode conter adicionalmente um efeito nefasto, caso este ocorra.
- **Distância mínima entre antenas da mesma frequência:** Foi definido um limite mínimo de distância entre antenas com a mesma frequência. Se duas antenas violarem essa distância mínima, considera-se que existe interferência, sendo gerado um efeito nefasto entre elas.
- **Área afetada pelo efeito nefasto:** Quando ocorre interferência, é registado um conjunto de posições afetadas ao redor da zona central do conflito. A extensão dessa área pode variar consoante a distância entre as antenas em conflito.
- **Modularização e separação de responsabilidades:** O projeto foi organizado em múltiplos módulos (`ed_io`, `ed_validator`, `ed_effects`, etc.), sendo utilizadas funções auxiliares `static` para validações internas, garantindo encapsulamento e reutilização de código.