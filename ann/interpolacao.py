def lagrange(pontos: (float, float), c: float) -> float:
    n: int = len(pontos)
    pc = 0

    for i in range(n):
        xi, yi = pontos[i]

        li = 1
        for j in range(n):
            if i != j:
                xj, _ = pontos[j]
                li *= (c - xj) / (xi - xj)

        pc += yi * li

    return pc


pontos1 = [(3, 5), (8, 10)]
c1 = 5

pontos2 = [(-6, 3296), (-5, 912), (-3, -70), (2, -40), (3, -376), (5, -4558)]
c2 = -1

print(f"{lagrange(pontos1, c1)}")
print(f"{lagrange(pontos2, c2)}")
