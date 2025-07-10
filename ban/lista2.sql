SELECT id, titulo FROM public.filmes WHERE ano IN(2002,2003) AND duracao between 90 AND 120 order by titulo;

SELECT f.id, f.nome FROM public.funcionarios f JOIN public.clientes JOIN public.reservas r ON r.cliente = c.id
    WHERE turno='N' AND dataRes='2006-10-01';


SELECT f.titulo, e.nome FROM public.filmes f JOIN public.estilos e ON f.estilo=e.id JOIN public.locacoes l ON l.filme=f.id
    WHERE datar IN('2006-30-11','2006-12-01')
    ORDER BY 2 desc, 1;

SELECT c.nome c.endereco FROM public clientes c
JOIN public.clientes d ON d.responsavel=c.id
WHERE c.cidade = 'Florianopolis';

SELECT c.nome, c.endereco FROM public.clientes c JOIN public.locacoes l ON c.id=l.cliente AND datad > datapd
JOIN public.copias cp ON cp.id=l.id AND cp.filme=l.filme
WHERE midia='DVD';

SELECT nome, cidade, endereco FROM public.funcionarios
WHERE turno IN('M', 'T')
UNION
SELECT nome, cidade, endereco FROM public.clientes
WHERE id IN(SELECT cliente FROM public.reservas);

SELECT cp.id, cp.filme FROM public.copias cp
WHERE filme IN(SELECT id FROM public.filmes WHERE titulo='X-Men 3')
AND NOT EXISTS(SELECT * FROM public.locacoes l WHERE l.datar <= '2006-11-30' AND datapd > '2006-11-30' AND l.filme=cp.filme AND cp.id=l.id)
AND NOT EXISTS(SELECT * FROM public.reservas r WHERE r.datar <= '2006-11-30' AND datapd > '2006-11-30' AND r.filme=cp.filme AND cp.id=r.id);

SELECT cp.id, cp.filme cp2.id, cp2.filmes FROM public.copias cp
JOIN public.copias cp2 ON cp.id<cp2.id AND cp.filme=cp2.filme;

-- 12
SELECT id,titulo FROM public.filmes estilo IN(SELECT id FROM public.estilos WHERE nome='ação')
AND duracao > ALL (SELECT duracao FROM public.filmes WHERE estilo
IN(SELECT * FROM public.filmes WHERE estilo IN(SELECT id FROM public.estilos WHERE nome IN('suspense', 'terror', 'drama')));
