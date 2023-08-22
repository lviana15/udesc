class Estrela:

    def __init__(self):
        self.nome = ''
        self.idade = 0
        self.nacionalidade = ''

    def __str__(self):
        return 'Nome: {}, Idade: {}, Nacionalidade: {}'.format(self.nome, self.idade, self.nacionalidade)
