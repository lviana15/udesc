// Necessario instalar 'rand' para algoritmo probabilistico
pub mod lista;
pub mod tree;

use rand;
use std::u128;

fn conversao_fahrenheit(celsius: f64) -> f64 {
    (celsius * 9.0 / 5.0) + 32.0
}

fn fibonacci(n: u32) -> u32 {
    match n {
        0 => 0,
        1 => 1,
        _ => fibonacci(n - 1) + fibonacci(n - 2),
    }
}

fn maior_vetor(v: &[i32]) -> Option<&i32> {
    if v.is_empty() {
        return None;
    }

    v.iter().max()
}

fn mod_exp(base: u128, exp: u128, modulus: u128) -> u128 {
    let mut result = 1;
    let mut base = base % modulus;
    let mut exp = exp;

    while exp > 0 {
        if exp % 2 == 1 {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exp /= 2;
    }
    result
}

fn primo_prob(n: u128) -> bool {
    let iterations = 5;
    match n {
        0 | 1 => false,
        2 | 3 => true,
        _ if (n % 2 == 0) => false,
        _ => (0..iterations).all(|_| {
            let a = rand::random_range(2..n - 1);
            mod_exp(a, n - 1, n) == 1
        }),
    }
}

fn primo_determ(n: u128) -> bool {
    match n {
        0 | 1 => false,
        _ => (2..n).into_iter().all(|x| n % x != 0),
    }
}

fn palindromo(s: String) -> bool {
    s == s.chars().rev().collect::<String>()
}

fn primos(v: Vec<u128>) -> Vec<u128> {
    v.into_iter().filter(|&x| primo_determ(x)).collect()
}

fn main() {
    assert_eq!(conversao_fahrenheit(0.0), 32.0);
    assert_eq!(conversao_fahrenheit(100.0), 212.0);
    assert_eq!(conversao_fahrenheit(-40.0), -40.0);

    assert_eq!(fibonacci(0), 0);
    assert_eq!(fibonacci(5), 5);
    assert_eq!(fibonacci(10), 55);

    assert_eq!(maior_vetor(&[1, 2, 3]), Some(&3));
    assert_eq!(maior_vetor(&[5]), Some(&5));
    assert_eq!(maior_vetor(&[]), None);

    assert_eq!(palindromo("tokyo".to_string()), false);
    assert_eq!(palindromo("ana".to_string()), true);
    assert_eq!(palindromo("a".to_string()), true);

    assert_eq!(primo_determ(2), true);
    assert_eq!(primo_determ(7), true);
    assert_eq!(primo_determ(53), true);
    assert_eq!(primo_determ(36), false);

    assert_eq!(primo_prob(2), true);
    assert_eq!(primo_prob(3), true);
    assert_eq!(primo_prob(61), true);
    assert_eq!(primo_prob(104729), true);

    assert_eq!(primo_prob(4), false);
    assert_eq!(primo_prob(561), false); // Pode falhar
    assert_eq!(primo_prob(1024), false);

    assert_eq!(primos(vec![1, 2, 3, 4, 5]), vec![2, 3, 5]);
    assert_eq!(primos(vec![6, 15, 21, 39]), vec![]);

    tree::main();
}
