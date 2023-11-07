from objeto_sobreposto_exception import ObjetoSobrepostoException
from espaco_geometrico import EspacoGeometrico
from reta import Reta
from ponto2d import Ponto2D

espaco = EspacoGeometrico()
reta1 = Reta(1, 2)

try:
    espaco.adicionarReta(reta1)
except ObjetoSobrepostoException as e:
    print(e)

reta2 = Reta(1, 1)
try:
    espaco.adicionarReta(reta2)
except ObjetoSobrepostoException as e:
    print(e)

reta3 = Reta(2, -2)
try:
    espaco.adicionarReta(reta3)
except ObjetoSobrepostoException as e:
    print(e)

try:
    espaco.adicionarPonto(Ponto2D(3, 4))
except ObjetoSobrepostoException as e:
    print(e)

try:
    espaco.adicionarPonto(Ponto2D(2, 3))
except ObjetoSobrepostoException as e:
    print(e)

try:
    espaco.adicionarPonto(Ponto2D(4, 6))
except ObjetoSobrepostoException as e:
    print(e)

try:
    espaco.adicionarPonto(Ponto2D(3, 2))
except ObjetoSobrepostoException as e:
    print(e)
