### Arquivos no projeto
- graph.h: Interface com estruturas e funcoes implementadas
- graph.c: Funcoes implementadas para execucao do projeto
- main.c: Arquivo principal
- db_205x3_v0.csv: Arquivo usado como base de dados
- output.csv: CSV com cabecalho e dados como especificado na descricao da tarefa
- grafo.txt: Arquivo com arestas geradas no formato de sequencia de arestas (vi vj)

### Compilacao do projeto
- Desenvolvido em sistema Linux Ubuntu x86_64
- Comando usado para compilacao: 

```bash
gcc -Wall -Wextra -o grafos main.c graph.c -lm
```

- Comando para Execucao do projeto
```bash
./grafos db_205x3_v0.csv
```
- Bibliotecas utilizadas no projeto:
    - math.h
    - stdbool.h
    - stdio.h
    - stdlib.h

### Execucao do projeto
- Entrada: arquivo csv como no exemplo
- Comentarios no codigo
1. Percorre arquivo csv e gera vetor de vertices
2. Gera uma matriz intermediaria (DistanceMatrix) designando distancia entre cada vertice
3. Percorre matriz de distancias, normalizando os valores e adicionando os vertices do grafo
4. Utiliza DFS para verificar numero de componentes conexos e seus tamanhos
5. Gera arquivo CSV seguinto formato especificado na descricao da tarefa 
6. Gera arquivo TXT apenas com arestas (vi vj) para visualizacao 3D do grafo gerado

