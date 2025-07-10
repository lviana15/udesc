CREATE TABLE public.cliente (
    id_cliente integer NOT NULL,
    nome_cliente character varying(255) NOT NULL,
    cpf_cliente character varying(12) NOT NULL,
    endereco_cliente character varying(255) NOT NULL,
    tel_cliente character varying(255) NOT NULL
);

CREATE TABLE public.componente (
    id_componente integer NOT NULL,
    nome_componente character varying(255) NOT NULL,
    preco_componente numeric(10,2) NOT NULL,
    tipo_componente character varying(255) NOT NULL,
    id_tipo_componente integer NOT NULL,
    qtd_estoque integer DEFAULT 0 NOT NULL
);

CREATE TABLE public.contrato (
    id_contrato integer NOT NULL,
    id_cliente integer NOT NULL,
    id_veiculo integer NOT NULL,
    data_contrato date NOT NULL,
    valor_contrato numeric(10,2) NOT NULL,
    status_contrato character varying(50) NOT NULL
);

CREATE TABLE public.departamento (
    id_departamento integer NOT NULL,
    nome_departamento character varying(255) NOT NULL,
    descricao_departamento text,
    id_responsavel integer
);


CREATE TABLE public.despesa (
    id_despesa integer NOT NULL,
    id_pedido_compra integer NOT NULL,
    valor_despesa numeric(10,2) NOT NULL,
    data_despesa date NOT NULL
);

CREATE TABLE public.fornecedor (
    id_fornecedor integer NOT NULL,
    nome_fornecedor character varying(255) NOT NULL,
    endereco_fornecedor character varying(255) NOT NULL,
    tel_fornecedor character varying(255) NOT NULL,
    principal_fornecedor boolean DEFAULT false,
    cnpj_fornecedor character varying(15) NOT NULL
);

CREATE TABLE public.funcionario (
    id_funcionario integer NOT NULL,
    nome_funcionario character varying(255) NOT NULL,
    cpf_funcionario character varying(12) NOT NULL,
    id_departamento integer NOT NULL,
    cargo_funcionario character varying(255)
);

CREATE TABLE public.item_pedido (
    id_item_pedido integer NOT NULL,
    id_pedido_compra integer NOT NULL,
    id_componente integer NOT NULL,
    quantidade_item_pedido integer NOT NULL,
    preco_unitario_item_pedido numeric(10,2) NOT NULL
);

CREATE TABLE public.lista_componentes (
    id_lista_componentes integer NOT NULL,
    id_tipo_veiculo integer NOT NULL,
    id_componente integer NOT NULL
);

CREATE TABLE public.notificacao (
    id_notificacao integer NOT NULL,
    id_departamento integer NOT NULL,
    id_componente integer NOT NULL,
    quantidade_notificacao integer NOT NULL,
    data_notificacao date NOT NULL
);

CREATE TABLE public.pedido_compra (
    id_pedido_compra integer NOT NULL,
    data_pedido date NOT NULL,
    id_departamento integer NOT NULL,
    id_fornecedor integer NOT NULL
);

CREATE TABLE public.receita (
    id_receita integer NOT NULL,
    id_contrato integer NOT NULL,
    valor_receita numeric(10,2) NOT NULL,
    data_receita date NOT NULL
);

CREATE TABLE public.tipo_componente (
    id_tipo_componente integer NOT NULL,
    nome_tipo_componente character varying(255) NOT NULL,
    descricao_tipo_componente character varying(255) NOT NULL
);

CREATE TABLE public.tipo_veiculo (
    id_tipo_veiculo integer NOT NULL,
    nome_tipo character varying(255) NOT NULL
);

CREATE TABLE public.veiculo (
    id_veiculo integer NOT NULL,
    modelo_veiculo character varying(255) NOT NULL,
    ano_veiculo integer NOT NULL,
    id_cliente integer NOT NULL,
    id_tipo integer NOT NULL
);
