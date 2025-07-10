-- 1)
CREATE OR REPLACE FUNCTION insere_mecanico(pcpf varchar, pnome varchar, pidade int) RETURNS void AS
$$
	INSERT INTO mecanico (cpf, nome, idade) VALUES (pcpf, pnome, pidade);
$$
LANGUAGE sql;

-- 2)
CREATE OR REPLACE FUNCTION remove_mecanico(pcodm int) RETURNS int AS
$$
DECLARE linhas int DEFAULT 0;
BEGIN
	DELETE FROM mecanico WHERE codm = pcodm;
	GET DIAGNOSTICS linhas = ROW_COUNT;
	RETURN linhas;
END;
$$
LANGUAGE plpgsql;

-- 3)
CREATE OR REPLACE FUNCTION manipula_cliente(
	acao varchar, pcodc int, pcpf varchar, pnome varchar, pidade int, pendereco varchar, pcidade varchar)
RETURNS void AS
$$
BEGIN
	IF upper(acao) = 'INSERT' THEN
		INSERT INTO cliente (codc, cpf, nome, idade, endereco, cidade) VALUES (pcodc, pcpf, pnome, pidade, pendereco, pcidade);
	ELSIF upper(acao) = 'UPDATE' THEN
		UPDATE cliente
		SET
			cpf = pcpf,
			nome = pnome,
			idade = pidade,
			endereco = pendereco,
			cidade = pcidade
		WHERE
			codc = pcodc;
	ELSIF upper(acao) = 'DELETE' THEN
		DELETE FROM cliente WHERE codc = pcodc;
	ELSE
		RAISE EXCEPTION 'Comando Inválido';
	END IF;

	RETURN;
END;
$$
LANGUAGE plpgsql;

-- 4)
CREATE OR REPLACE FUNCTION limita_setores(pcods int, pnome varchar) RETURNS void AS
$$
DECLARE
    contador int DEFAULT 0;
BEGIN
	SELECT count(*) INTO contador FROM setor;
	IF  contador >= 10 THEN
		RAISE EXCEPTION 'Limite atingido';
	ELSIF contador < 10 THEN
		INSERT INTO setor VALUES (pcods, pnome);
	END IF;
END;
$$
LANGUAGE plpgsql;

-- 5)
CREATE OR REPLACE FUNCTION cadastra_conserto(pcodm INT, pcodv INT, pdata DATE, phora TIMESTAMP) RETURNS void AS
$$
DECLARE
    contador int DEFAULT 0;
BEGIN
    SELECT count(*) FROM conserto WHERE codm = pcodm AND data = pdata INTO contador;
 	IF contador < 3 THEN
		INSERT INTO conserto (codm, codc, data, hora) VALUES (pcodm, pcodvm, pdata, phora);
	ELSE
		RAISE EXCEPTION 'Limite diario atingido';
	END IF;
END;
$$
LANGUAGE plpgsql;


--6)
CREATE OR REPLACE FUNCTION calcula_media_idade_geral() RETURNS numeric AS
$$
DECLARE
	media_mecanicos numeric;
	media_clientes numeric;
	media_geral numeric;
BEGIN
	SELECT avg(idade) INTO media_mecanicos FROM mecanico;
	SELECT avg(idade) INTO media_clientes FROM cliente;

	media_geral := (media_mecanicos + media_clientes) / 2;

	RETURN media_geral;
END;
$$
LANGUAGE plpgsql;


--7)
CREATE OR REPLACE FUNCTION exclui_entidade(
	tipo varchar, pident int) RETURNS int AS
$$
DECLARE
	linhas int DEFAULT 0;
BEGIN
	IF upper(tipo) = 'SETOR' THEN
		DELETE FROM setor WHERE cods = pident;
		GET DIAGNOSTICS linhas = ROW_COUNT;
	ELSIF upper(tipo) = 'MECANICO' THEN
		DELETE FROM mecanico WHERE codm = pident;
		GET DIAGNOSTICS linhas = ROW_COUNT;
	ELSIF upper(tipo) = 'CLIENTE' THEN
		DELETE FROM cliente WHERE codc = pident;
		GET DIAGNOSTICS linhas = ROW_COUNT;
	ELSIF upper(tipo) = 'VEICULO' THEN
		DELETE FROM veiculo WHERE codv = pident;
		GET DIAGNOSTICS linhas = ROW_COUNT;
	ELSE
		RAISE EXCEPTION 'Tipo de entidade inválido';
	END IF;

	RETURN linhas;
END;
$$
LANGUAGE plpgsql;

--8)
CREATE OR REPLACE FUNCTION remove_clientes_repetidos() RETURNS void AS
$$
DECLARE
    cpf_repetido varchar;
BEGIN
    FOR cpf_repetido IN
        SELECT cpf
        FROM cliente
        GROUP BY cpf
        HAVING COUNT(*) > 1
    LOOP
        DELETE FROM cliente
        WHERE cpf = cpf_repetido
        AND codc NOT IN (
            SELECT codc
            FROM cliente
            WHERE cpf = cpf_repetido
            ORDER BY idade ASC
            LIMIT 1
        );
    END LOOP;
END;
$$
LANGUAGE plpgsql;

--9)
CREATE OR REPLACE FUNCTION valida_cpf() RETURNS TRIGGER AS
$$
DECLARE
    cpf varchar(11);
    digito1 int;
    digito2 int;
    soma int;
    resto int;
BEGIN
    cpf := regexp_replace(NEW.cpf, '[^\d]', '', 'g');

    IF length(cpf) != 11 THEN
        RAISE EXCEPTION 'CPF Inválido'
    END IF;

    soma := (substring(cpf from 1 for 1)::int * 10) +
            (substring(cpf from 2 for 1)::int * 9) +
            (substring(cpf from 3 for 1)::int * 8) +
            (substring(cpf from 4 for 1)::int * 7) +
            (substring(cpf from 5 for 1)::int * 6) +
            (substring(cpf from 6 for 1)::int * 5) +
            (substring(cpf from 7 for 1)::int * 4) +
            (substring(cpf from 8 for 1)::int * 3) +
            (substring(cpf from 9 for 1)::int * 2);

    resto := soma % 11;
    digito1 := CASE
                   WHEN resto < 2 THEN 0
                   ELSE 11 - resto
               END;

    soma := (substring(cpf from 1 for 1)::int * 11) +
            (substring(cpf from 2 for 1)::int * 10) +
            (substring(cpf from 3 for 1)::int * 9) +
            (substring(cpf from 4 for 1)::int * 8) +
            (substring(cpf from 5 for 1)::int * 7) +
            (substring(cpf from 6 for 1)::int * 6) +
            (substring(cpf from 7 for 1)::int * 5) +
            (substring(cpf from 8 for 1)::int * 4) +
            (substring(cpf from 9 for 1)::int * 3) +
            (substring(cpf from 10 for 1)::int * 2) +
            (digito1 * 1);

    resto := soma % 11;
    digito2 := CASE
                   WHEN resto < 2 THEN 0
                   ELSE 11 - resto
               END;

    IF (substring(cpf from 10 for 1)::int != digito1 OR
        substring(cpf from 11 for 1)::int != digito2) THEN
        RAISE EXCEPTION 'CPF Inválido';
    END IF;

    RETURN NEW;
$$
LANGUAGE plpgsql;

--10)
CREATE OR REPLACE FUNCTION calcula_horas_extras(pcodm int, pmes int, pano int) RETURNS int AS
$$
DECLARE
    total_horas_trabalhadas int;
    horas_extras int;
BEGIN
    SELECT count(*) INTO total_horas_trabalhadas
    FROM conserto
    WHERE codm = pcodm
    AND EXTRACT(MONTH FROM data) = pmes
    AND EXTRACT(YEAR FROM data) = pano;

    IF total_horas_trabalhadas > 160 THEN
        horas_extras := total_horas_trabalhadas - 160;
    ELSE
        horas_extras := 0;
    END IF;

    RETURN horas_extras;
END;
$$
LANGUAGE plpgsql;

