use std::mem::replace;
use NoLista::*;

#[derive(Debug)]
enum NoLista {
    Cons(i32, Box<NoLista>),
    Nil,
}

#[derive(Debug)]
struct Lista {
    cab: Box<NoLista>,
}

impl Lista {
    fn ins_cab(&mut self, e: i32) {
        let n = Box::new(Cons(e, replace(&mut self.cab, Box::new(Nil))));
        self.cab = n;
    }

    fn remove_cab(&mut self) -> Option<i32> {
        match *replace(&mut self.cab, Box::new(Nil)) {
            Nil => None,
            Cons(x, xs) => {
                self.cab = xs;
                Some(x)
            }
        }
    }

    fn inserir_final(no: &mut Box<NoLista>, valor: i32) {
        match no.as_mut() {
            NoLista::Nil => {
                *no = Box::new(NoLista::Cons(valor, Box::new(NoLista::Nil)));
            }
            NoLista::Cons(_, prox) => {
                Self::inserir_final(prox, valor);
            }
        }
    }

    fn remover_ultimo(no: &mut Box<NoLista>) {
        match no.as_mut() {
            NoLista::Nil => {}
            NoLista::Cons(_, prox) => match prox.as_mut() {
                NoLista::Nil => {
                    *no = Box::new(NoLista::Nil);
                }
                _ => Self::remover_ultimo(prox),
            },
        }
    }

    fn ins_pos(&mut self, e: i32, pos: usize) {}
}
