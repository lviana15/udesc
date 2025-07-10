### Arquivos no projeto

- `volume_TAC`: Arquivo contendo matriz tridimensional (3D) representando diferentes tecidos/células.
- `main.py`: Arquivo com todo código utilizado para geração da analise
- `requirements.txt`: Arquivo com especificação das dependencias

##### Arquivos gerados após execução do script
- `proliferativa.npy`: Arquivo gerado contendo o maior agrupamento identificado de células proliferativas.
- `quiescente.npy`: Arquivo gerado contendo o maior agrupamento identificado de células quiescentes.
- `necrotica.npy`: Arquivo gerado contendo o maior agrupamento identificado de células necróticas.
- `resultado.txt`: Arquivo com resultado da análise utilizando vizinhança C26 (Equivalente 3D para C8)

### Execução do projeto

- **Sistema utilizado**: Desenvolvido e testado em sistema GNU/Linux x86_64
- **Bibliotecas utilizadas**:
  - `numpy`
  - `pickle`
  - `collections.deque`
  - `plotly.graph_objects`
  - `plotly.express`
  - `numpy.typing` (para tipagem)

- **Configuraçao de ambiente**: Ambiente virtual para lidar com dependencias
```bash
   python -m venv venv
   source venv/bin/activate
   pip install -r requirements.txt
```
- **Comando para execução**:
```bash
python3 main.py
```

> Arquivo `volume_TAC` deve estar no mesmo diretório antes de rodar o script.

### Estrutura e funcionalidades do projeto

1. **Leitura do volume**: Carrega um volume 3D de voxels a partir de um arquivo binário (`volume_TAC`), onde cada valor representa um tipo celular:
   - 255: Células proliferativas  
   - 200: Células quiescentes  
   - 140: Células necróticas  

2. **Segmentação por componentes conectados**:
   - Usa busca em largura (BFS) para agrupar voxels adjacentes com o mesmo valor, baseando-se em vizinhança 3D (C26 — 26 vizinhos).
   - Voxels isolados (grupos com apenas 1 voxel) são ignorados.

3. **Extração do maior grupo**:
   - Para cada tipo celular, é extraído apenas o maior agrupamento conectado.

4. **Salvamento dos volumes extraídos**:
   - Os três maiores grupos segmentados são salvos como arquivos `.npy`, permitindo fácil reutilização posterior.

5. **Renderização 3D (opcional)**:
   - O maior agrupamento de células proliferativas é renderizado em 3D com Plotly.
   - A visualização é interativa e será aberta automaticamente no navegador padrão.

### Comentários adicionais

- Ao executar arquivo gera resultados e renderiza o volume selecionado no navegador (Pode levar algum tempo para renderizar)
- A função `segment_groups` realiza rotulagem dos grupos conectados com BFS e retorna matriz 3D rotulada e um dicionário com tamanhos dos grupos.
- A função `extract_largest_group` é usada para filtrar a matriz 3D apenas com voxels do maior agrupamento.
- O script pode ser adaptado facilmente para tipo de vizinhança C6 mudando variavel `offsets` na função main.
- Também é possível renderizar outro tipo de célula mudando parametro na funçao `render_volume`.
- Script ignora 'grupos' de tamanho 1, onde é apenas uma célula isolada

