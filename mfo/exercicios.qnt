module exercicios {
    // Fold inicia com 0 já que todos elementos no conjunto são positivos
    pure def maior(s: Set[int]): int = fold(s, 0, (acc, x) => if (x > acc) x else acc)

    // Operador auxiliar para diferença de idade
    pure def menor(s: Set[int]): int = fold(s, 0, (acc, x) => if (acc == 0 or x < acc) x else acc)

    pure def diff_idade(s: Set[{nome: str, idade: int}]): int = 
        s.map(x => x.idade).maior() - s.map(x => x.idade).menor()

    pure val conjuntos = 1.to(10).powerset().filter(s => s.size() > 2 and s.size() < 5)

    pure def fatorial(n: int): int = 1.to(n).fold(1, (acc, x) => acc * x)

    pure def contaLista(l: List[int]): int -> int = l.foldl(
        Map(), 
        (acc, x) => 
        if (x.in(acc.keys()))
            acc.set(x, acc.get(x) + 1)
        else 
            acc.put(x, 1)
    )

    run maiorTest = all {
        assert(maior(Set(1, 2, 3)) == 3),
        assert(maior(Set(1, 4, 8)) == 8),
    }

    run diffIdadeTest = all {
        assert(diff_idade(Set({nome: "Lucas", idade: 20}, {nome: "João", idade: 30})) == 10),
        assert(diff_idade(Set({nome: "Lucas", idade: 20}, {nome: "João", idade: 30}, {nome: "Maria", idade: 25})) == 10),
    }

    run fatorialTest = all {
        assert(fatorial(5) == 120),
        assert(fatorial(0) == 1),
        assert(fatorial(1) == 1),
    }
    run contaListaTest = all {
        assert(contaLista(List(1, 2, 3, 1, 2, 1)).get(1) == 3),
        assert(contaLista(List(1, 2, 3, 1, 2, 1)).get(2) == 2),
        assert(contaLista(List(1, 2, 3, 1, 2, 1)).get(3) == 1),
        // assert(contaLista(List(1, 2, 3)).get(4) == null), -> runtime error
    }
}