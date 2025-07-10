gerar opcodes para AST gerada pelo parser

-- identifier
geraE tf tv (IdVar i) = "\t iload" ++ show (pos i) ++ "\n"

-- CInt (iconst_n 0..5) (bipush 6..128) (ldc 129..)
geraE tf tv (Const (CInt i)) = "\t iconst_n"
geraE tf tv (Const (CInt i)) = "\t bipush" ++ show (pos i) ++ "\n"

-- CDouble (dconst_n)
geraE tf tv (Const (CDouble d)) = "\t dconst_n"
geraE tf tv (Const (CDouble d)) = "\t ldc2_w" ++ show (pos d) ++ "\n"


-- Add
gerarE tf tv (Add e1 e2) = gerarE tf tv e1 ++ gerarE tf tv e2 ++
                            ++ "\t iadd" -- Add int int

-- String Literal
ldc "string"
astore 7

-- IntDouble
gerarE tf tv (IntDouble e1) = gerarE tf tv e ++ "\t i2d"
