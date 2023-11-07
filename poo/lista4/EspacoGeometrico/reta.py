from ponto2d import Ponto2D


class Reta:
    def __init__(self, a, b):
        self.a = a
        self.b = b

    def intercepta(self, reta: 'Reta'):
        if self.a == reta.a and self.b == reta.b:
            return True
        elif self.a == reta.a:
            return False
        else:
            return True

    def estaNaReta(self, ponto: Ponto2D):
        return self.a * ponto.x + self.b == ponto.y
