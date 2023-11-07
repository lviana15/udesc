class ObjetoSobrepostoException(Exception):
    def __inti__(self):
        super().__init__()

    def __str__(self):
        return 'Objeto Sobreposto'
