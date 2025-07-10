--1) Gatilho para impedir a inserção ou atualização de Clientes com o mesmo CPF.
CREATE OR REPLACE FUNCTION valida_cliente() RETURNS TRIGGER AS
$$
BEGIN
	IF TG_OP = 'INSERT' THEN
		IF (SELECT 1 FROM cliente WHERE cpf = NEW.cpf) THEN
				RAISE EXCEPTION 'CPF já existente';
		END IF;
	ELSIF TG_OP = 'UPDATE' THEN
		IF (SELECT 1 FROM cliente WHERE cpf = NEW.cpf AND NEW.cpf <> OLD.cpf) THEN
				RAISE EXCEPTION 'CPF já existente';
		END IF;
	END IF;
	RETURN NEW;
END;
$$
LANGUAGE plpgsql;

CREATE TRIGGER valida_cliente BEFORE INSERT OR UPDATE ON cliente FOR EACH ROW EXECUTE PROCEDURE valida_cliente()


--2) Gatilho para impedir a inserção ou atualização de Mecânicos com idade menor que 20 anos.
CREATE OR REPLACE FUNCTION valida_idade() RETURNS TRIGGER AS
$$
BEGIN
	IF NEW.idade < 20 THEN
		RAISE EXCEPTION 'Mecanico deve ter 20 anos ou mais';
	END IF;
	RETURN NEW;
END;
$$
LANGUAGE plpgsql;

CREATE TRIGGER valida_idade BEFORE INSERT OR UPDATE ON mecanico FOR EACH ROW EXECUTE PROCEDURE valida_idade()

--3) Gatilho para atribuir um cods (sequencial) para um novo setor inserido.
CREATE SEQUENCE setor_cods_seq START 10;

CREATE OR REPLACE FUNCTION new_cods() RETURNS TRIGGER AS
$$
BEGIN
	NEW.cods := nextval('setor_cods_seq');
	RETURN NEW;
END;
$$
LANGUAGE plpgsql;

CREATE TRIGGER new_cods BEFORE INSERT ON setor FOR EACH ROW EXECUTE PROCEDURE new_cods()

--4) Gatilho para impedir a inserção de um mecânico ou cliente com CPF inválido.
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
        RAISE EXCEPTION 'CPF Inválido';
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
END;
$$
LANGUAGE plpgsql;


CREATE TRIGGER valida_cpf_mecanico BEFORE INSERT OR UPDATE ON mecanico FOR EACH ROW EXECUTE PROCEDURE valida_cpf()
CREATE TRIGGER valida_cpf_cliente BEFORE INSERT OR UPDATE ON cliente FOR EACH ROW EXECUTE PROCEDURE valida_cpf()

--5) Gatilho para impedir que um mecânico seja removido caso não exista outro mecânico com a mesma função.
CREATE OR REPLACE FUNCTION mec_funcao() RETURNS TRIGGER AS
$$
DECLARE
	total_mecanicos int;
BEGIN
	SELECT count(*) INTO total_mecanicos FROM mecanico WHERE funcao ILIKE OLD.funcao;

	IF TG_OP = 'UPDATE' THEN
		IF total_mecanicos <= 1 AND OLD.funcao <> NEW.funcao THEN
			RAISE EXCEPTION 'Número mínimo de mecanicos no setor';
		END IF;
		RETURN NEW;

	ELSIF TG_OP = 'DELETE' THEN
		IF total_mecanicos <= 1 THEN
			RAISE EXCEPTION 'Número mínimo de mecanicos no setor';
		END IF;
		RETURN OLD;
	END IF;
END;
$$
LANGUAGE plpgsql;

CREATE TRIGGER mec_funcao BEFORE UPDATE OR DELETE ON mecanico FOR EACH ROW EXECUTE PROCEDURE mec_funcao()

--6) Gatilho que ao inserir, atualizar ou remover um mecânico, reflita as mesmas modificações na tabela de Cliente.
--Em caso de atualização, se o mecânico ainda não existir na tabela de Cliente, deve ser inserido.
CREATE OR REPLACE FUNCTION atualiza_cliente() RETURNS TRIGGER AS
$$
BEGIN
	IF (TG_OP = 'INSERT') THEN
		INSERT INTO cliente (cpf, nome, idade, endereco, cidade)
		VALUES (NEW.cpf, NEW.nome, NEW.idade, NEW.endereco, NEW.cidade)
		ON CONFLICT (cpf)
		DO UPDATE SET
			cpf = EXCLUDED.cpf,
			nome = EXCLUDED.nome,
			idade = EXCLUDED.idade,
			endereco = EXCLUDED.endereco,
			cidade = EXCLUDED.cidade;
	ELSIF TG_OP = 'UPDATE' THEN
		UPDATE cliente SET
			cpf = NEW.cpf,
			nome = NEW.nome,
			idade = NEW.idade,
			endereco = NEW.endereco,
			cidade = NEW.cidade
		WHERE cpf = NEW.cpf;
	ELSIF TG_OP = 'DELETE' THEN
		DELETE FROM cliente WHERE cpf = OLD.cpf;
	END IF;
END;
$$
LANGUAGE plpgsql;

CREATE TRIGGER atualiza_cliente
AFTER INSERT OR UPDATE OR DELETE ON mecanico
FOR EACH ROW EXECUTE PROCEDURE atualiza_cliente();

--7) Gatilho para impedir que um conserto seja inserido na tabela Conserto
--se o mecânico já realizou mais de 20 horas extras no mês.
CREATE OR REPLACE FUNCTION calcula_horas_extras(pcodm int, pdata date) RETURNS int AS
$$
DECLARE
    total_horas_trabalhadas int;
    horas_extras int;
    pmes int;
    pano int;
BEGIN
    pmes := EXTRACT(MONTH FROM pdata);
    pano := EXTRACT(YEAR FROM pdata);

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

CREATE OR REPLACE FUNCTION verifica_horas_extras() RETURNS TRIGGER AS
$$
BEGIN
	IF (calcula_horas_extras(NEW.codm, NEW.data) > 20) THEN
		RAISE EXCEPTION 'Limite de Horas Extras';
	ELSE
		RETURN NEW;
	END IF;
END;
$$
LANGUAGE plpgsql;

CREATE TRIGGER verifica_horas_extras
BEFORE INSERT OR UPDATE ON conserto
FOR EACH ROW EXECUTE PROCEDURE verifica_horas_extras();

--8) Gatilho para impedir que mais de 1 conserto seja agendado no mesmo setor na mesma hora.
CREATE OR REPLACE FUNCTION verifica_conserto_no_mesmo_setor() RETURNS TRIGGER AS
$$
DECLARE
    setor_existente int;
BEGIN
    SELECT 1 INTO setor_existente
    FROM conserto c
    JOIN mecanico m ON c.codm = m.codm
    WHERE m.cods = (SELECT cods FROM mecanico WHERE codm = NEW.codm)
    AND c.data = NEW.data
    AND c.hora = NEW.hora;

    IF setor_existente IS NOT NULL THEN
        RAISE EXCEPTION 'Já existe um conserto agendado para o mesmo setor, data e hora.';
    END IF;

    RETURN NEW;
END;
$$
LANGUAGE plpgsql;

CREATE TRIGGER verifica_conserto
BEFORE INSERT ON conserto
FOR EACH ROW EXECUTE PROCEDURE verifica_conserto_no_mesmo_setor();
