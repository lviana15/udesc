from Filme import Filme
from Estrela import Estrela

estrela = Estrela()
filme = Filme()

estrela.nome = 'Tom Holland'
estrela.idade = 27
estrela.nacionalidade = 'Reino Unido'

filme.titulo = 'Spider-Man'
filme.estrela = estrela
filme.ano = 2023

print(filme)
