# Relatorio Trabalho Fila
 Aluno: Lucas Viana
 Arquitetura / SO: Linux Ubuntu x86_64

### Arquivos:
 - info.h: Cabecalho com estruturas compartilhadas entre implementacoes das filas
 - fde.h: Cabecalho da FDE sem referencia movel
 - fde.c: Implementação da FDE sem referencia movel
 - refMovel.h: Cabecalho da FDE com referencia movel
 - refMovel.c: Implementacao da FDE com referencia movel
 - main.c: Arquivo com aplicao do codigo

### Execução:
 A aplicação aceita dois argumentos:
 Um arquivo a ser considerado e o número de casos desejados.

 No inicio da execução deve-se selecionar qual aplicação deseja: Menu com operações ou leitura do arquivo.
 No menu a aplicação executa até o usuario desejar fechar.
 Caso escolha a leitura do arquivo, o arquivo é processado e ao fim da exeução é mostrado as medias de iterações para cada implementação

 Funcoes:
  - preencheFDE: Enfilera as linhas seleciondas na Fila Duplamente Encadeada
  - preencheFRM: Enfilera as linhas seleciondas na Fila com Referencia Movel
  - displayMenu: Mostra menu com operacoes sobre a Fila com Referencia Movel

### Resultado:
 - 500 Casos:
    Fila com Referencia Movel apresenta uma media de ~1.80
    Fila Duplamente Encadeada ~2.80
 - 1000 Casos:
    Fila com Referencia Movel apresenta uma media de ~1.90
    Fila Duplamente Encadeada ~5.20
 - 1500 Casos:
    Fila com Referencia Movel apresenta uma media de ~1.93
    Fila Duplamente Encadeada ~8.00
 - 2000 Casos:
    Fila com Referencia Movel apre$enta uma media de ~1.95
    Fila Duplamente Encadeada ~10.50
 - 2500 Casos:
    Fila com Referencia Movel apre$enta uma media de ~1.96
    Fila Duplamente Encadeada ~13.50
 - 3000 Casos:
    Fila com Referencia Movel apre$enta uma media de ~1.96
    Fila Duplamente Encadeada ~16.30
 - 3500 Casos:
    Fila com Referencia Movel apre$enta uma media de ~1.97
    Fila Duplamente Encadeada ~18.73
 - 4000 Casos:
    Fila com Referencia Movel apre$enta uma media de ~1.97
    Fila Duplamente Encadeada ~21.64
 - 4500 Casos:
    Fila com Referencia Movel apre$enta uma media de ~1.97
    Fila Duplamente Encadeada ~24.49
 - 5000 Casos:
    Fila com Referencia Movel apre$enta uma media de ~1.97
    Fila Duplamente Encadeada ~27.23
 - 5500 Casos:
    Fila com Referencia Movel apre$enta uma media de ~1.98
    Fila Duplamente Encadeada ~29.72
 - 6000 Casos:
    Fila com Referencia Movel apre$enta uma media de ~1.98
    Fila Duplamente Encadeada ~32.85
 - 6500 Casos:
    Fila com Referencia Movel apre$enta uma media de ~1.98
    Fila Duplamente Encadeada ~35.31
 - 7000 Casos:
    Fila com Referencia Movel apre$enta uma media de ~1.98
    Fila Duplamente Encadeada ~37.95
 - 7500 Casos:
    Fila com Referencia Movel apre$enta uma media de ~1.98
    Fila Duplamente Encadeada ~40.53
 - 8000 Casos:
    Fila com Referencia Movel apre$enta uma media de ~1.98
    Fila Duplamente Encadeada ~43.31
 - 8500 Casos:
    Fila com Referencia Movel apre$enta uma media de ~1.98
    Fila Duplamente Encadeada ~46.02
 - 9000 Casos:
    Fila com Referencia Movel apre$enta uma media de ~1.98
    Fila Duplamente Encadeada ~48.62
