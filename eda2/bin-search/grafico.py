import pandas as pd
import matplotlib.pyplot as plt

# Função para plotar o gráfico


def plot_data(file_path, title):
    # Ler o arquivo CSV em um DataFrame do pandas
    df = pd.read_csv(file_path)

    # Extrair dados das colunas
    N = df['N']
    avl = df['AVL']
    rubro_negra = df['Rubro-Negra']
    ordem1 = df['ArvoreB-1']
    ordem5 = df['ArvoreB-5']
    ordem10 = df['ArvoreB-10']

    # Plotar os dados com diferentes estilos de linha para cada coluna
    plt.plot(N, avl, label='AVL', linestyle='-', marker='o')
    plt.plot(N, rubro_negra, label='Rubro-Negra', linestyle='--', marker='o')
    plt.plot(N, ordem1, label='ArvoreB-1', linestyle=':', marker='o')
    plt.plot(N, ordem5, label='ArvoreB-5', linestyle='-.', marker='o')
    plt.plot(N, ordem10, label='ArvoreB-10', linestyle='-.', marker='o')

    plt.xlabel('N')
    plt.ylabel('Comparacoes')
    plt.yscale('log')
    plt.title(title)
    plt.legend()
    plt.grid(True)
    plt.show()


# Plotar gráfico para o arquivo insercao.csv
plot_data('insercao.csv', 'Insercao Arvores')

# Plotar gráfico para o arquivo remocao.csv
plot_data('remocao.csv', 'Remocao Arvores')

