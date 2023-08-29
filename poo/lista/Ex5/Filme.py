class Filme:

    def __init__(self):
        self.titulo = ''
        self.estrela = None
        self.ano = 0

    def __str__(self):
        return 'Titulo: {}, Estrela: {}, Ano: {}'.format(self.titulo, self.estrela, self.ano)
