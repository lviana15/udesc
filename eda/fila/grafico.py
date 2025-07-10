import matplotlib.pyplot as plt

# Dados
casos = [500, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500,
         5000, 5500, 6000, 6500, 7000, 7500, 8000, 8500, 9000]
media_referencia_movel = [1.80, 1.90, 1.93, 1.95, 1.96, 1.96, 1.97,
                          1.97, 1.97, 1.97, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98]
media_fila_dupla_encadeada = [2.80, 5.20, 8.00, 10.50, 13.50, 16.30, 18.73,
                              21.64, 24.49, 27.23, 29.72, 32.85, 35.31, 37.95, 40.53, 43.31, 46.02, 48.62]

# Criar o gráfico
plt.figure(figsize=(10, 6))
plt.plot(casos, media_referencia_movel, marker='o',
         label='Fila com Referência Móvel')
plt.plot(casos, media_fila_dupla_encadeada,
         marker='o', label='Fila Duplamente Encadeada')
plt.xlabel('Número de Casos')
plt.ylabel('Média')
plt.title('Média em Função do Número de Casos')
plt.legend()
plt.grid(True)

# Exibir o gráfico
plt.show()
