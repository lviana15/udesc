### Indice Arquivos

- main.c: Arquivo de execução dos algoritmos, gera os dados usados nas comparações
- arvoreAVL.h / arvoreAVL.c: Header e implementação ArvoreAVL
- rubroNegra.h / rubroNegra.c: Header e implementação Arvore Rubro-Negra
- arvoreb.h / arvoreb.c: Header e implementação ArvoreB
- grafico.py: Codigo python para plotagem dos graficos
- insercao.csv / remocao.csv: Arquivos csv com dados gerados
- insercao.png / remocao.png: Printscreen dos graficos gerados

### Execucao
Compilar código e executar.

##### Exemplo:

`gcc -O3 -o programa arvoreAVL.c arvoreb.c rubroNegra.c main.c`

`./programa`

- flag -O3 gera otimizações no código
- Recomendado diminuir valores de N e/ou K ao executar. Programa gerado é bastante lento.

