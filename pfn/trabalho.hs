import Data.List
import Data.Char

type Doc = String
type Line = String
type Word' = String

lines' :: Doc -> [Line]
lines' x = lines x

numLines :: [Line] -> [(Int, Line)]
numLines (x:xs) = numLines' (x:xs) 1 
numLines' [] n = []
numLines' (x:xs) n = (n, x) : numLines' xs (n + 1) 

allNumWords [] = []
allNumWords ((n, x): t) = allNumWords' (n, (words x)) : allNumWords t
allNumWords' (n, []) = []
allNumWords' (n, (x:xs)) = (n, x) : allNumWords' (n, xs) 

sortLs :: [(Int,Word')] -> [(Int,Word')]
sortLs x = sortOn snd x

--shorten [] = []
--shorten ((n,x) : t) = (n, map toLower x): shorten t