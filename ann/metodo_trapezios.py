import math


def metodo_trapezio(f, a: float, b: float, n: int):
    h = (b - a) / n

    soma = f(a) + f(b)

    for i in range(1, n):
        xi = a + i * h
        soma += 2 * f(xi)

    integral = (h / 2) * soma
    return integral


def f(x: float) -> float:
    return x + math.tan(math.tan(abs(((1/8) * x) - 4/8)))


def v(t: float) -> float:
    g = 10
    m = 98
    c = 13

    return (g*m)/c * (1 - math.e**(-(c/m)*t))


resultado = metodo_trapezio(f, -4, 12, 19)
resultado2 = metodo_trapezio(v, 0, 26, 25)
print(round(resultado, 6))
print(round(resultado2, 6))
