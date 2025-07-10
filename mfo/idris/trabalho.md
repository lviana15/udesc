### Intoducao
- Linguagem de programacao funcional
- Type-driven development
- Tipos Dependentes
- Totality Checker
- REPL - Desenvolvimento Interativo
    1. Holes
    2. Sugestao do que esta faltando
- Compila para C e JavaScript
- Se compila, funciona

- Quantitative Types
- erased keyword

---

### Tipos Dependentes
- Correct by construction
- Curry-Howard correspondence
- Tipos podem depender de valores
- Tipos sao 'First-Class Values'
- Invariants sao escritas usando tipos
- Verificacao de invariants pelo Type System

#### Exemplo
```rust
data Vect : Nat -> Type -> Type where
  Nil  : Vect 0
  (::) : (x : a) -> (xs : Vect k a) -> Vect (S k) a
```
1. Lista vazia e Tamanho 0
2. Cons e Sucessor de (Tamanho tail)

- Vect 1 Int /= Vect 2 Int

---

### Invariant (Propriedade) Check
- Algoritmo de Ordenacao
- Preserva o tamanho da lista

```rust
insSort : Ord elem => Vect len elem -> Vect len elem
insSort [] = []
insSort (x :: xs) = let xsSorted = insSort xs in
                        insert x xsSorted

                    where
                        insert : elem -> Vect k elem -> Vect (S k) elem
                        insert x [] = [x]
                        insert x (y :: xs) = case x < y of
                                                  False =>  y :: insert x xs
                                                  True => x :: y :: xs
```

--- 

### Totality Checker
- Funcao retorna para todo input bem-tipado em tempo finito
- Provas nao-total nao sao validas
- **Prova** que funcao soma o tamanho dos vetores

```rust
total
append : Vect n a -> Vect m a -> Vect (n + m) a
append Nil       ys = ys
append (x :: xs) ys = x :: append xs ys
```
---

### Pros
- Correct by Construction
- Fine-Grained property Verification (Prova cada funcao do sistema)
- Intregration proof <=> code
- Learn type theory, dependent types

### Cons
- Slow or hard (no automation) to write proofs
- Poor performance
- Concurrent or Distributed Systems
- Small ecosystem

### When to use
- Research
- Small projects
- Project would benefit from Dependent Types use

### Use Case - Qimaera: Type-safe (Variational) Quantum Programming in Idris
- Idris libraries for hybrid classical-quantum programming.
- Programacao hibrida entre logica classica e logica quantica
- Biblioteca para criacao dos algoritmos em Idris

#### Benefits
- Linear types: qubits are used once, preventing copies/clones
- Dependent types: help track states and structures
- Preventing runtime errors/bugs
- Logica classica e quantica no mesmo sistema

### Sources
- Type driven development with Idris
