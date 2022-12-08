type Doc = String
type Line = String
type Word' = String

lines' :: Doc -> [Line]
lines' x = lines x

numLines :: [Line] -> [(Int, Line)]
numLines (x:xs) = numLines' (x:xs) 1 
numLines' [] y = []
numLines' (x:xs) y = (y, x) : numLines' xs (y + 1) 
--[(1, "Departamento de Ciencia da Computacao"), (2,"Curso de Ciencia da Computacao"), (3, "Programacao Funcional")]

--[(1, "Departamento de Ciencia da Computacao") -> (1, "Departamento"), (1, "de"), (1, "Ciencia")]
--allNumWords :: [(Int, Line)] -> [(Int,Word')]
allNumWords [] = []
allNumWords ((y, x): t) = allNumWords' (y, (words x)) : allNumWords t
allNumWords' (y, []) = []
allNumWords' (y, (x:xs)) = (y, x) : allNumWords' (y, xs) 

{-[(1, "Departamento"), (1, "de"), (1, "ciencia") (1, "da"), (1, "Computacao"), 
(2, "Curso"), (2, "de"), (2, "Ciencia"), (2, "da"), (2, "Computacao")
(3, "Programacao"), (3, "Funcional")] -}

--sortLs :: [(Int,Word')] -> [(Int,Word')]
--[1, "Ciencia"), (6,"ciencia"), (1, "Computacao")]
