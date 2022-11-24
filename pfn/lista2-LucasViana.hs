import Data.Char

pertence x [] = False
pertence x (y:ys) = if x == y then True else pertence x ys

intersecao [] _ = []
intersecao (x:xs) (y:ys) = if pertence x (y:ys) then x : intersecao xs (y:ys) else intersecao xs ys


inverso [] = []
inverso (x:xs) = inverso xs ++ [x]

nUltimos n xs = inverso (take n (inverso xs))

soma2 [] _ = []
soma2 _ [] = []
soma2 (x:xs) (y:ys) = x + y : soma2 xs ys

pot2 0 = []
pot2 n = pot2' n 1
pot2' n i = if i < n+1 then 2^i : pot2' n (i + 1) else pot2 0

intercalacao xs [] = xs
intercalacao [] ys = ys
intercalacao (x:xs) (y:ys) = if x < y then x: intercalacao xs (y:ys) else y : intercalacao ys (x:xs)

-- menor (x:xs) = if x < menor xs then x else menor xs
menor [] = 0
menor [x] = x
menor (x:xs) = min x (menor xs)

removerElem n (x:xs) = if n /= x then x : removerElem n xs else removerElem n xs
removerElem _ [] = []
removerElem n (x:xs) = if n == x then xs else x : removerElem n xs

-- ordenar retorna lista dos menores elementos
ordenar [x] = [x]
ordenar x = menor x : ordenar(removerElem (menor x) x)

insereOrd n x = if pertence n x then x else ordenar (n : x)

enesimo n x = enesimo' 1 n x
enesimo' i n (x:xs) = if i == n then x else enesimo' (i+1) n xs

repetir n e = if n /= 1 then e : repetir (n-1) e else [e]
-- repetir' i n e = if i /= n then e : repetir' (i+1) n e else [e]

removeTab [] = []
removeTab (x:xs)  = if x == '\t' then ' ' : removeTab xs else x : removeTab xs

minusculas [] = []
minusculas (x:xs) = toLower x : (minusculas xs)

inversoDupla :: [(a,b)] -> [(b,a)]
inversoDupla [] = []
inversoDupla (x:xs) = inversoDupla' x : inversoDupla xs
inversoDupla' (a,b) = (b,a)

simetrico [] = []
simetrico (x:xs) = simetrico' x : simetrico xs
simetrico' (a,b) = if a == b then True else False

dig 0 = '0'
dig 1 = '1'
dig 2 = '2'
dig 3 = '3'
dig 4 = '4'
dig 5 = '5'
dig 6 = '6'
dig 7 = '7'
dig 8 = '8'
dig 9 = '9'

numString 0 = []
numString x = inverso (dig (rem x 10) : inverso(numString (div x 10)))

dig' '0' = 0
dig' '1' = 1
dig' '2' = 2
dig' '3' = 3
dig' '4' = 4
dig' '5' = 5
dig' '6' = 6
dig' '7' = 7
dig' '8' = 8
dig' '9' = 9

stringNum [] = 0
stringNum (x:xs) = inverso ((dig' x * 10) + 10 * (stringNum xs))


trocoCafe :: Int -> Int -> [(a,b)]
