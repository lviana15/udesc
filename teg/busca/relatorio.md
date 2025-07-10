### Arquivos no projeto
* graph.h: Interface com estruturas e funções implementadas, incluindo definição de vértices, grafo e matriz de distâncias.
* graph.c: Funções implementadas para execução do projeto, como cálculo de distâncias e construção do grafo.
* queue.h: Interface da estrutura de fila utilizada nos algoritmos (Dijkstra e Prim).
* queue.c: Implementação das funções de fila.
* main.c: Arquivo principal contendo a lógica principal do programa.
* db\_204x3\_v0.csv: Arquivo usado como base de dados com espécies e coordenadas.

### Compilacao do projeto

* Desenvolvido em sistema Linux Ubuntu x86\_64
* Comando usado para compilação:

```bash
gcc -Wall -Wextra main.c graph.c queue.c -lm
```

* Comando para Execução do projeto:

```bash
./a.out
```

* Bibliotecas utilizadas no projeto:

  * math.h
  * stdbool.h
  * stdio.h
  * stdlib.h
  * time.h

### Execucao do projeto

* Entrada: arquivo CSV contendo as espécies e suas coordenadas espaciais.
* Comentários no código:

1. Percorre o arquivo CSV e gera vetor de vértices com espaço tridimensional e espécie.
2. Gera uma matriz intermediária (`DistanceMatrix`) contendo as distâncias euclidianas entre os vértices.
3. Forma arestas do grafo tendo pesos com a distancia euclidiana encontrada.
4. Executa ambos algoritmos 10 vezes e printa tempo levado para cada um.
5. Após execução mostra a média de tempo para 10 execuções de cada algoritmo.

