ehTriangulo a b c = a < b + c && b < a + c && c < a + b

tipoTriangulo a b c | a == b && b == c = "Equilatero"
                    | a /= b && b /= c && a /= c = "Escaleno"
                    | otherwise = "Isoceles"

triangulo a b c = if (ehTriangulo a b c) then (tipoTriangulo a b c) else "Nao e triangulo"

somaPares 0 = 0
somaPares n = if rem n 2 == 0 then n + (somaPares(n - 2)) else somaPares (n-1)

somaPot2m m 0 = 1*m
somaPot2m m n = 2^n * m + somaPot2m m (n-1)

primo n = primoAux n (n-1)
primoAux n i = if i > 1  then if rem n i == 0 then False else primoAux n (i-1) else True

seriePI n = seriePi' n 1 1
seriePi' n i s = if 4/i > 4/n then s * 4/i + seriePi' n (i+2) (negate s) else s * 4/i + 0