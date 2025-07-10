import matplotlib.pyplot as plt
import pandas as pd
from datetime import datetime

# Dados extraídos manualmente das imagens
taee11_data = {
    "Date": [
        "2025-06-02", "2025-05-26", "2025-05-19", "2025-05-12", "2025-05-05",
        "2025-04-28", "2025-04-21", "2025-04-14", "2025-04-07", "2025-03-31",
        "2025-03-24", "2025-03-17", "2025-03-10", "2025-03-03", "2025-02-24",
        "2025-02-17", "2025-02-10", "2025-02-03", "2025-01-27"
    ],
    "Adj Close": [
        34.86, 35.38, 35.53, 34.85, 35.03,
        34.01, 34.56, 33.14, 32.67, 32.95,
        32.62, 33.23, 32.73, 31.93, 31.50,
        31.60, 32.21, 31.68, 32.19
    ]
}

sapr11_data = {
    "Date": [
        "2025-06-02", "2025-05-26", "2025-05-19", "2025-05-12", "2025-05-05",
        "2025-04-28", "2025-04-21", "2025-04-14", "2025-04-07", "2025-03-31",
        "2025-03-24", "2025-03-17", "2025-03-10", "2025-03-03", "2025-02-24",
        "2025-02-17", "2025-02-10", "2025-02-03", "2025-01-27"
    ],
    "Adj Close": [
        33.05, 32.77, 32.00, 30.63, 29.29,
        29.85, 29.73, 28.44, 27.59, 28.41,
        27.39, 28.31, 27.79, 28.15, 27.26,
        27.48, 27.43, 27.10, 25.65
    ]
}

# Criando DataFrames
df_taee11 = pd.DataFrame(taee11_data)
df_taee11["Date"] = pd.to_datetime(df_taee11["Date"])
df_taee11.sort_values("Date", inplace=True)
df_taee11["Delta"] = df_taee11["Adj Close"].diff().abs()

df_sapr11 = pd.DataFrame(sapr11_data)
df_sapr11["Date"] = pd.to_datetime(df_sapr11["Date"])
df_sapr11.sort_values("Date", inplace=True)
df_sapr11["Delta"] = df_sapr11["Adj Close"].diff().abs()

# Função para plotar com destaque
def plot_stock(df, title, filename):
    plt.figure(figsize=(10, 5))
    plt.plot(df["Date"], df["Adj Close"], label=title, marker="o")
    top_deltas = df.nlargest(4, "Delta")
    # plt.scatter(top_deltas["Date"], top_deltas["Adj Close"], color="red", label="Maiores variações")
    # for _, row in top_deltas.iterrows():
    #    plt.annotate(f"{row['Adj Close']:.2f}", (row["Date"], row["Adj Close"]), textcoords="offset points", xytext=(0,10), ha='center')
    plt.title(f"{title} - Preço Ajustado (com maiores variações)")
    plt.xlabel("Data")
    plt.ylabel("Preço (R$)")
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(filename)
    plt.close()

# Gráficos individuais
plot_stock(df_taee11, "TAEE11", "taee11.png")
plot_stock(df_sapr11, "SAPR11", "sapr11.png")

# Gráfico comparativo
plt.figure(figsize=(12, 6))
plt.plot(df_sapr11["Date"], df_sapr11["Adj Close"], label="SAPR11", marker="o")
plt.plot(df_taee11["Date"], df_taee11["Adj Close"], label="TAEE11", marker="s")
plt.title("Comparativo - TAEE11 vs SAPR11")
plt.xlabel("Data")
plt.ylabel("Preço Ajustado (R$)")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig("comparativo_taee11_sapr11.png")
plt.close()
