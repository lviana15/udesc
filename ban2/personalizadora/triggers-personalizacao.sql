-- Validar cpf cliente
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

CREATE TRIGGER valida_cpf_cliente BEFORE INSERT OR UPDATE ON cliente FOR EACH ROW EXECUTE PROCEDURE valida_cpf()


-- Atualizar status do contrato conforme data atual
CREATE OR REPLACE FUNCTION atualizar_status_contrato()
RETURNS TRIGGER AS $$
BEGIN
    IF NEW.data_contrato < CURRENT_DATE THEN
        NEW.status_contrato := 'Vencido';
    ELSE
        NEW.status_contrato := 'Ativo';
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER atualizar_status_contrato
BEFORE INSERT OR UPDATE ON public.contrato
FOR EACH ROW EXECUTE FUNCTION atualizar_status_contrato();

-- Gerar pedido de compra
ALTER TABLE componente
ADD COLUMN qtd_minima INTEGER DEFAULT 0;

CREATE OR REPLACE FUNCTION gerar_pedido_compra()
RETURNS TRIGGER AS $$
DECLARE
    estoque_atual INTEGER;
    quantidade_minima INTEGER;
BEGIN
    SELECT qtd_estoque, qtd_minima INTO estoque_atual, quantidade_minima
    FROM componente
    WHERE id_componente = NEW.id_componente;

    IF (TG_OP = 'INSERT' OR TG_OP = 'UPDATE') THEN
        estoque_atual := estoque_atual - NEW.quantidade_item_pedido;

        IF estoque_atual < quantidade_minima THEN
            INSERT INTO pedido_compra (id_departamento, id_fornecedor)
            VALUES (1, 1);

            RAISE NOTICE 'Pedido de compra gerado para o componente %', NEW.id_componente;
        END IF;

    ELSIF (TG_OP = 'DELETE') THEN
        estoque_atual := estoque_atual + OLD.quantidade_item_pedido;

        IF estoque_atual < quantidade_minima THEN
            INSERT INTO pedido_compra (id_departamento, id_fornecedor)
            VALUES (1, 1);

            RAISE NOTICE 'Pedido de compra gerado para o componente %', OLD.id_componente;
        END IF;
    END IF;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER gerar_pedido_compra
AFTER INSERT OR UPDATE OR DELETE ON item_pedido
FOR EACH ROW EXECUTE FUNCTION gerar_pedido_compra();

-- Gerar relatório despesa
CREATE FUNCTION calcular_valor_despesa(p_id_pedido_compra INT)
RETURNS DECIMAL(10, 2) AS $$
DECLARE
    valor DECIMAL(10, 2);
BEGIN
    SELECT COALESCE(SUM(preco_componente * quantidade), 0) INTO valor
    FROM itens_pedido_compra
    WHERE id_pedido_compra = p_id_pedido_compra;

    RETURN valor;
END; $$ LANGUAGE plpgsql;

CREATE FUNCTION gerar_relatorio_despesa()
RETURNS TRIGGER AS $$
DECLARE
    valor_despesa DECIMAL(10, 2);
BEGIN
    valor_despesa := calcular_valor_despesa(NEW.id_pedido_compra);

    INSERT INTO despesa (id_pedido_compra, valor_despesa, data_despesa)
    VALUES (NEW.id_pedido_compra, valor_despesa, CURRENT_DATE)
    ON CONFLICT (id_pedido_compra)
    DO UPDATE SET valor_despesa = EXCLUDED.valor_despesa;
    RETURN NEW;
END; $$ LANGUAGE plpgsql;

CREATE TRIGGER gerar_relatorio_despesa
AFTER INSERT OR UPDATE ON pedido_compra
FOR EACH ROW EXECUTE FUNCTION gerar_relatorio_despesa();

-- Gerar relatorio receita
CREATE FUNCTION calcular_valor_receita(p_id_contrato INT)
RETURNS DECIMAL(10, 2) AS $$
DECLARE
    valor DECIMAL(10, 2);
BEGIN
    SELECT COALESCE(valor_contrato, 0) INTO valor
    FROM contrato
    WHERE id_contrato = p_id_contrato;

    RETURN valor;
END; $$ LANGUAGE plpgsql;

CREATE FUNCTION gerar_relatorio_receita()
RETURNS TRIGGER AS $$
DECLARE
    valor_receita DECIMAL(10, 2);
BEGIN
    valor_receita := calcular_valor_receita(NEW.id_contrato);

    INSERT INTO receita (id_contrato, valor_receita, data_receita)
    VALUES (NEW.id_contrato, valor_receita, CURRENT_DATE)
    ON CONFLICT (id_contrato)
    DO UPDATE SET valor_receita = EXCLUDED.valor_receita;
    RETURN NEW;
END; $$ LANGUAGE plpgsql;

CREATE TRIGGER after_insert_update_contrato
AFTER INSERT OR UPDATE ON contrato
FOR EACH ROW EXECUTE FUNCTION gerar_relatorio_receita();

