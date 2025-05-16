## 4. Estrutura de Dados Utilizada

Para representar a rede de antenas e os efeitos nefastos, foi definida uma estrutura de dados dinâmica baseada numa **lista ligada simples**. Esta escolha deve-se à necessidade de uma estrutura flexível, que permita inserções e remoções dinâmicas sem a necessidade de reorganização da memória, como seria necessário em arrays tradicionais.

A estrutura principal utilizada é a seguinte:

```c
typedef struct ed {
    char frequency;   // Frequência da antena ou efeito nefasto
    int x;            // Coordenada X
    int y;            // Coordenada Y
    struct ed *next;  // Próximo elemento da lista
} ED;
```

Cada nó da lista representa uma antena ou uma localização com efeito nefasto. A distinção entre ambos é feita através do campo `frequency`, onde o valor especial `'#'` é utilizado para identificar um efeito nefasto.

Esta abordagem permite manter uma única estrutura comum para representar elementos de diferentes tipos (antenas e interferências), simplificando a lógica de gestão da lista.

Para além da estrutura base, foram implementadas funções auxiliares para criação de nós, inserção ordenada ou em posições específicas, verificação de duplicação de coordenadas e comparação de frequências.

A lista ligada é manipulada através de ponteiros, permitindo a sua expansão ou redução consoante as operações efetuadas, e garantindo uma gestão eficiente da memória.
