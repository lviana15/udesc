# Formula de erro absoluto
def erro_iteracao(a: float, b: float, N: int):
    return (b - a) / 2 ** (N+1)


def ponto_medio(a: float, b: float):
    return a + (b - a) / 2


# Utilizando apenas Numero de iteracoes como criterio de parada
def bissecao(f, a: float, b: float, N: int):
    fa = f(a)
    for i in range(N + 1):
        x = ponto_medio(a, b)
        fx = f(x)

        if fa * fx > 0:
            a = x
            fa = fx
        else:
            b = x
    return x, f(x)


# Funcao dada pela questao
def funcao(x: float):
    return x ** 5 - 3072 * x + 2504


intervalo = [0, 1]
iteracoes = 8

aproximacao, f_aproximacao = bissecao(
    funcao, intervalo[0], intervalo[1], iteracoes)
print(aproximacao)
print(erro_iteracao(intervalo[0], intervalo[1], iteracoes))
print(f_aproximacao)
