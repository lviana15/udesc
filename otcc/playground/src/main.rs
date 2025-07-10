use std::f64::consts::PI;

#[derive(Debug, Clone, Copy)]
enum Forma {
    Circulo { raio: f64 },
    Retangulo { alt: f64, compr: f64 },
}

impl Forma {

    fn area(f: &Forma) -> f64 {
        match *f {
            Self::Circulo { raio: r } => r * r * PI,
            Self::Retangulo { alt: a, compr: c } => a * c,
        }
    }
}

fn main() {
    let r = Forma::Retangulo {
        alt: 10f64,
        compr: 5f64,
    };

    println!("{r:?}");
    println!("{}", Forma::area(&r));
    println!("{r:?}");
}
