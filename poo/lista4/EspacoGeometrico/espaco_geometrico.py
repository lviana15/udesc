from objeto_sobreposto_exception import ObjetoSobrepostoException
from ponto2d import Ponto2D
from reta import Reta


class EspacoGeometrico:
    def __init__(self):
        self.retas = []
        self.pontos = []

    def adicionarReta(self, nova_reta: Reta):
        for reta in self.retas:
            if reta.intercepta(nova_reta):
                raise ObjetoSobrepostoException
            self.retas.append(reta)

    def adicionarPonto(self, novo_ponto: Ponto2D):
        for reta in self.retas:
            if reta.estaNaReta(novo_ponto):
                raise ObjetoSobrepostoException
            self.pontos.append(novo_ponto)
