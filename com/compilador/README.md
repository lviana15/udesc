Comando para gerar parser
alex Lexer
happy NParser.y

Compilar programa
ghc --make Main.hs -o Main

Executar
./Main <arquivo>
