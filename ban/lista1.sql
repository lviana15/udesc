-- Retorne nome dos autores que publicaram em toad as edições que ocorreram no estado do Paraná (PR)
SELECT a.nome FROM autroes a WHERE NOT EXISTS
    (SELECT e.edicaoid FROM edicoes e WHERE e.uf = 'PR')
EXCEPT
SELECT art.edicaoid FROM artigos art
JOIN autoresartigo aa ON art.artigoid = aa.artigoid
WHERE aa.autorid = a.autorid
