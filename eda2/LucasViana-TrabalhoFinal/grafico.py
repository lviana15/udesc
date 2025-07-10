import pandas as pd
import matplotlib.pyplot as plt

# Função para plotar o gráfico


def plot_data(file_path, title):
    try:
        # Ler o arquivo CSV em um DataFrame do pandas
        df = pd.read_csv(file_path)

        # Verificar as colunas disponíveis
        print(
            f"Colunas disponíveis no arquivo {file_path}: {df.columns.tolist()}")

        # Extrair dados das colunas
        N = df['N']
        avl = df['AVL']
        rubro_negra = df['Rubro-Negra']
        ordem1 = df['ArvoreB1']
        ordem5 = df['ArvoreB5']
        ordem10 = df['ArvoreB10']

        # Plotar os dados com diferentes estilos de linha para cada coluna
        plt.plot(N, avl, label='AVL', linestyle='-', marker='o')
        plt.plot(N, rubro_negra, label='Rubro-Negra',
                 linestyle='--', marker='o')
        plt.plot(N, ordem1, label='ArvoreB1', linestyle=':', marker='o')
        plt.plot(N, ordem5, label='ArvoreB5', linestyle='-.', marker='o')
        plt.plot(N, ordem10, label='ArvoreB10', linestyle='-.', marker='o')

        plt.xlabel('N')
        plt.ylabel('Comparacoes')
        plt.yscale('log')
        plt.title(title)
        plt.legend()
        plt.grid(True)
        plt.show()
    except KeyError as e:
        print(
            f"Erro: A coluna {e} não foi encontrada no arquivo {file_path}. Verifique os nomes das colunas.")


# Plotar gráfico para o arquivo insercao.csv
plot_data('insercao.csv', 'Insercao Arvores')

# Plotar gráfico para o arquivo remocao.csv
plot_data('remocao.csv', 'Remocao Arvores')
