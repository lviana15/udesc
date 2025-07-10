--
-- PostgreSQL database dump
--

-- Dumped from database version 15.8 (Ubuntu 15.8-1.pgdg22.04+1)
-- Dumped by pg_dump version 15.8 (Ubuntu 15.8-1.pgdg22.04+1)

-- Started on 2024-09-23 20:08:47 -03

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- TOC entry 215 (class 1259 OID 17708)
-- Name: cliente; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.cliente (
    id_cliente integer NOT NULL,
    nome_cliente character varying(255) NOT NULL,
    cpf_cliente character varying(12) NOT NULL,
    endereco_cliente character varying(255) NOT NULL,
    tel_cliente character varying(255) NOT NULL
);


ALTER TABLE public.cliente OWNER TO postgres;

--
-- TOC entry 214 (class 1259 OID 17707)
-- Name: cliente_id_cliente_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.cliente_id_cliente_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.cliente_id_cliente_seq OWNER TO postgres;

--
-- TOC entry 3533 (class 0 OID 0)
-- Dependencies: 214
-- Name: cliente_id_cliente_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.cliente_id_cliente_seq OWNED BY public.cliente.id_cliente;


--
-- TOC entry 227 (class 1259 OID 17786)
-- Name: componente; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.componente (
    id_componente integer NOT NULL,
    nome_componente character varying(255) NOT NULL,
    preco_componente numeric(10,2) NOT NULL,
    tipo_componente character varying(255) NOT NULL,
    id_tipo_componente integer NOT NULL,
    qtd_estoque integer DEFAULT 0 NOT NULL
);


ALTER TABLE public.componente OWNER TO postgres;

--
-- TOC entry 226 (class 1259 OID 17785)
-- Name: componente_id_componente_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.componente_id_componente_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.componente_id_componente_seq OWNER TO postgres;

--
-- TOC entry 3534 (class 0 OID 0)
-- Dependencies: 226
-- Name: componente_id_componente_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.componente_id_componente_seq OWNED BY public.componente.id_componente;


--
-- TOC entry 237 (class 1259 OID 17868)
-- Name: contrato; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.contrato (
    id_contrato integer NOT NULL,
    id_cliente integer NOT NULL,
    id_veiculo integer NOT NULL,
    data_contrato date NOT NULL,
    valor_contrato numeric(10,2) NOT NULL,
    status_contrato character varying(50) NOT NULL
);


ALTER TABLE public.contrato OWNER TO postgres;

--
-- TOC entry 236 (class 1259 OID 17867)
-- Name: contrato_id_contrato_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.contrato_id_contrato_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.contrato_id_contrato_seq OWNER TO postgres;

--
-- TOC entry 3535 (class 0 OID 0)
-- Dependencies: 236
-- Name: contrato_id_contrato_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.contrato_id_contrato_seq OWNED BY public.contrato.id_contrato;


--
-- TOC entry 223 (class 1259 OID 17755)
-- Name: departamento; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.departamento (
    id_departamento integer NOT NULL,
    nome_departamento character varying(255) NOT NULL,
    descricao_departamento text,
    id_responsavel integer
);


ALTER TABLE public.departamento OWNER TO postgres;

--
-- TOC entry 222 (class 1259 OID 17754)
-- Name: departamento_id_departamento_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.departamento_id_departamento_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.departamento_id_departamento_seq OWNER TO postgres;

--
-- TOC entry 3536 (class 0 OID 0)
-- Dependencies: 222
-- Name: departamento_id_departamento_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.departamento_id_departamento_seq OWNED BY public.departamento.id_departamento;


--
-- TOC entry 241 (class 1259 OID 17897)
-- Name: despesa; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.despesa (
    id_despesa integer NOT NULL,
    id_pedido_compra integer NOT NULL,
    valor_despesa numeric(10,2) NOT NULL,
    data_despesa date NOT NULL
);


ALTER TABLE public.despesa OWNER TO postgres;

--
-- TOC entry 240 (class 1259 OID 17896)
-- Name: despesa_id_despesa_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.despesa_id_despesa_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.despesa_id_despesa_seq OWNER TO postgres;

--
-- TOC entry 3537 (class 0 OID 0)
-- Dependencies: 240
-- Name: despesa_id_despesa_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.despesa_id_despesa_seq OWNED BY public.despesa.id_despesa;


--
-- TOC entry 219 (class 1259 OID 17726)
-- Name: fornecedor; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.fornecedor (
    id_fornecedor integer NOT NULL,
    nome_fornecedor character varying(255) NOT NULL,
    endereco_fornecedor character varying(255) NOT NULL,
    tel_fornecedor character varying(255) NOT NULL,
    principal_fornecedor boolean DEFAULT false,
    cnpj_fornecedor character varying(15) NOT NULL
);


ALTER TABLE public.fornecedor OWNER TO postgres;

--
-- TOC entry 218 (class 1259 OID 17725)
-- Name: fornecedor_id_fornecedor_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.fornecedor_id_fornecedor_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.fornecedor_id_fornecedor_seq OWNER TO postgres;

--
-- TOC entry 3538 (class 0 OID 0)
-- Dependencies: 218
-- Name: fornecedor_id_fornecedor_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.fornecedor_id_fornecedor_seq OWNED BY public.fornecedor.id_fornecedor;


--
-- TOC entry 225 (class 1259 OID 17765)
-- Name: funcionario; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.funcionario (
    id_funcionario integer NOT NULL,
    nome_funcionario character varying(255) NOT NULL,
    cpf_funcionario character varying(12) NOT NULL,
    id_departamento integer NOT NULL,
    cargo_funcionario character varying(255)
);


ALTER TABLE public.funcionario OWNER TO postgres;

--
-- TOC entry 224 (class 1259 OID 17764)
-- Name: funcionario_id_funcionario_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.funcionario_id_funcionario_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.funcionario_id_funcionario_seq OWNER TO postgres;

--
-- TOC entry 3539 (class 0 OID 0)
-- Dependencies: 224
-- Name: funcionario_id_funcionario_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.funcionario_id_funcionario_seq OWNED BY public.funcionario.id_funcionario;


--
-- TOC entry 231 (class 1259 OID 17812)
-- Name: item_pedido; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.item_pedido (
    id_item_pedido integer NOT NULL,
    id_pedido_compra integer NOT NULL,
    id_componente integer NOT NULL,
    quantidade_item_pedido integer NOT NULL,
    preco_unitario_item_pedido numeric(10,2) NOT NULL
);


ALTER TABLE public.item_pedido OWNER TO postgres;

--
-- TOC entry 230 (class 1259 OID 17811)
-- Name: item_pedido_id_item_pedido_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.item_pedido_id_item_pedido_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.item_pedido_id_item_pedido_seq OWNER TO postgres;

--
-- TOC entry 3540 (class 0 OID 0)
-- Dependencies: 230
-- Name: item_pedido_id_item_pedido_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.item_pedido_id_item_pedido_seq OWNED BY public.item_pedido.id_item_pedido;


--
-- TOC entry 243 (class 1259 OID 17917)
-- Name: lista_componentes; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.lista_componentes (
    id_lista_componentes integer NOT NULL,
    id_tipo_veiculo integer NOT NULL,
    id_componente integer NOT NULL
);


ALTER TABLE public.lista_componentes OWNER TO postgres;

--
-- TOC entry 242 (class 1259 OID 17916)
-- Name: lista_componentes_id_lista_componentes_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.lista_componentes_id_lista_componentes_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.lista_componentes_id_lista_componentes_seq OWNER TO postgres;

--
-- TOC entry 3541 (class 0 OID 0)
-- Dependencies: 242
-- Name: lista_componentes_id_lista_componentes_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.lista_componentes_id_lista_componentes_seq OWNED BY public.lista_componentes.id_lista_componentes;


--
-- TOC entry 235 (class 1259 OID 17851)
-- Name: notificacao; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.notificacao (
    id_notificacao integer NOT NULL,
    id_departamento integer NOT NULL,
    id_componente integer NOT NULL,
    quantidade_notificacao integer NOT NULL,
    data_notificacao date NOT NULL
);


ALTER TABLE public.notificacao OWNER TO postgres;

--
-- TOC entry 234 (class 1259 OID 17850)
-- Name: notificacao_id_notificacao_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.notificacao_id_notificacao_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.notificacao_id_notificacao_seq OWNER TO postgres;

--
-- TOC entry 3542 (class 0 OID 0)
-- Dependencies: 234
-- Name: notificacao_id_notificacao_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.notificacao_id_notificacao_seq OWNED BY public.notificacao.id_notificacao;


--
-- TOC entry 229 (class 1259 OID 17795)
-- Name: pedido_compra; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.pedido_compra (
    id_pedido_compra integer NOT NULL,
    data_pedido date NOT NULL,
    id_departamento integer NOT NULL,
    id_fornecedor integer NOT NULL
);


ALTER TABLE public.pedido_compra OWNER TO postgres;

--
-- TOC entry 228 (class 1259 OID 17794)
-- Name: pedido_compra_id_pedido_compra_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.pedido_compra_id_pedido_compra_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.pedido_compra_id_pedido_compra_seq OWNER TO postgres;

--
-- TOC entry 3543 (class 0 OID 0)
-- Dependencies: 228
-- Name: pedido_compra_id_pedido_compra_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.pedido_compra_id_pedido_compra_seq OWNED BY public.pedido_compra.id_pedido_compra;


--
-- TOC entry 239 (class 1259 OID 17885)
-- Name: receita; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.receita (
    id_receita integer NOT NULL,
    id_contrato integer NOT NULL,
    valor_receita numeric(10,2) NOT NULL,
    data_receita date NOT NULL
);


ALTER TABLE public.receita OWNER TO postgres;

--
-- TOC entry 238 (class 1259 OID 17884)
-- Name: receita_id_receita_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.receita_id_receita_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.receita_id_receita_seq OWNER TO postgres;

--
-- TOC entry 3544 (class 0 OID 0)
-- Dependencies: 238
-- Name: receita_id_receita_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.receita_id_receita_seq OWNED BY public.receita.id_receita;


--
-- TOC entry 233 (class 1259 OID 17829)
-- Name: tipo_componente; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.tipo_componente (
    id_tipo_componente integer NOT NULL,
    nome_tipo_componente character varying(255) NOT NULL,
    descricao_tipo_componente character varying(255) NOT NULL
);


ALTER TABLE public.tipo_componente OWNER TO postgres;

--
-- TOC entry 232 (class 1259 OID 17828)
-- Name: tipo_componente_id_tipo_componente_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.tipo_componente_id_tipo_componente_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.tipo_componente_id_tipo_componente_seq OWNER TO postgres;

--
-- TOC entry 3545 (class 0 OID 0)
-- Dependencies: 232
-- Name: tipo_componente_id_tipo_componente_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.tipo_componente_id_tipo_componente_seq OWNED BY public.tipo_componente.id_tipo_componente;


--
-- TOC entry 217 (class 1259 OID 17719)
-- Name: tipo_veiculo; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.tipo_veiculo (
    id_tipo_veiculo integer NOT NULL,
    nome_tipo character varying(255) NOT NULL
);


ALTER TABLE public.tipo_veiculo OWNER TO postgres;

--
-- TOC entry 216 (class 1259 OID 17718)
-- Name: tipo_veiculo_id_tipo_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.tipo_veiculo_id_tipo_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.tipo_veiculo_id_tipo_seq OWNER TO postgres;

--
-- TOC entry 3546 (class 0 OID 0)
-- Dependencies: 216
-- Name: tipo_veiculo_id_tipo_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.tipo_veiculo_id_tipo_seq OWNED BY public.tipo_veiculo.id_tipo_veiculo;


--
-- TOC entry 221 (class 1259 OID 17738)
-- Name: veiculo; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.veiculo (
    id_veiculo integer NOT NULL,
    modelo_veiculo character varying(255) NOT NULL,
    ano_veiculo integer NOT NULL,
    id_cliente integer NOT NULL,
    id_tipo integer NOT NULL
);


ALTER TABLE public.veiculo OWNER TO postgres;

--
-- TOC entry 220 (class 1259 OID 17737)
-- Name: veiculo_id_veiculo_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.veiculo_id_veiculo_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.veiculo_id_veiculo_seq OWNER TO postgres;

--
-- TOC entry 3547 (class 0 OID 0)
-- Dependencies: 220
-- Name: veiculo_id_veiculo_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.veiculo_id_veiculo_seq OWNED BY public.veiculo.id_veiculo;


--
-- TOC entry 3286 (class 2604 OID 17711)
-- Name: cliente id_cliente; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.cliente ALTER COLUMN id_cliente SET DEFAULT nextval('public.cliente_id_cliente_seq'::regclass);


--
-- TOC entry 3293 (class 2604 OID 17789)
-- Name: componente id_componente; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.componente ALTER COLUMN id_componente SET DEFAULT nextval('public.componente_id_componente_seq'::regclass);


--
-- TOC entry 3299 (class 2604 OID 17871)
-- Name: contrato id_contrato; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.contrato ALTER COLUMN id_contrato SET DEFAULT nextval('public.contrato_id_contrato_seq'::regclass);


--
-- TOC entry 3291 (class 2604 OID 17758)
-- Name: departamento id_departamento; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.departamento ALTER COLUMN id_departamento SET DEFAULT nextval('public.departamento_id_departamento_seq'::regclass);


--
-- TOC entry 3301 (class 2604 OID 17900)
-- Name: despesa id_despesa; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.despesa ALTER COLUMN id_despesa SET DEFAULT nextval('public.despesa_id_despesa_seq'::regclass);


--
-- TOC entry 3288 (class 2604 OID 17729)
-- Name: fornecedor id_fornecedor; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.fornecedor ALTER COLUMN id_fornecedor SET DEFAULT nextval('public.fornecedor_id_fornecedor_seq'::regclass);


--
-- TOC entry 3292 (class 2604 OID 17768)
-- Name: funcionario id_funcionario; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.funcionario ALTER COLUMN id_funcionario SET DEFAULT nextval('public.funcionario_id_funcionario_seq'::regclass);


--
-- TOC entry 3296 (class 2604 OID 17815)
-- Name: item_pedido id_item_pedido; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.item_pedido ALTER COLUMN id_item_pedido SET DEFAULT nextval('public.item_pedido_id_item_pedido_seq'::regclass);


--
-- TOC entry 3302 (class 2604 OID 17920)
-- Name: lista_componentes id_lista_componentes; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.lista_componentes ALTER COLUMN id_lista_componentes SET DEFAULT nextval('public.lista_componentes_id_lista_componentes_seq'::regclass);


--
-- TOC entry 3298 (class 2604 OID 17854)
-- Name: notificacao id_notificacao; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.notificacao ALTER COLUMN id_notificacao SET DEFAULT nextval('public.notificacao_id_notificacao_seq'::regclass);


--
-- TOC entry 3295 (class 2604 OID 17798)
-- Name: pedido_compra id_pedido_compra; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.pedido_compra ALTER COLUMN id_pedido_compra SET DEFAULT nextval('public.pedido_compra_id_pedido_compra_seq'::regclass);


--
-- TOC entry 3300 (class 2604 OID 17888)
-- Name: receita id_receita; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.receita ALTER COLUMN id_receita SET DEFAULT nextval('public.receita_id_receita_seq'::regclass);


--
-- TOC entry 3297 (class 2604 OID 17832)
-- Name: tipo_componente id_tipo_componente; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.tipo_componente ALTER COLUMN id_tipo_componente SET DEFAULT nextval('public.tipo_componente_id_tipo_componente_seq'::regclass);


--
-- TOC entry 3287 (class 2604 OID 17722)
-- Name: tipo_veiculo id_tipo_veiculo; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.tipo_veiculo ALTER COLUMN id_tipo_veiculo SET DEFAULT nextval('public.tipo_veiculo_id_tipo_seq'::regclass);


--
-- TOC entry 3290 (class 2604 OID 17741)
-- Name: veiculo id_veiculo; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.veiculo ALTER COLUMN id_veiculo SET DEFAULT nextval('public.veiculo_id_veiculo_seq'::regclass);


--
-- TOC entry 3499 (class 0 OID 17708)
-- Dependencies: 215
-- Data for Name: cliente; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.cliente (id_cliente, nome_cliente, cpf_cliente, endereco_cliente, tel_cliente) FROM stdin;
\.


--
-- TOC entry 3511 (class 0 OID 17786)
-- Dependencies: 227
-- Data for Name: componente; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.componente (id_componente, nome_componente, preco_componente, tipo_componente, id_tipo_componente, qtd_estoque) FROM stdin;
\.


--
-- TOC entry 3521 (class 0 OID 17868)
-- Dependencies: 237
-- Data for Name: contrato; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.contrato (id_contrato, id_cliente, id_veiculo, data_contrato, valor_contrato, status_contrato) FROM stdin;
\.


--
-- TOC entry 3507 (class 0 OID 17755)
-- Dependencies: 223
-- Data for Name: departamento; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.departamento (id_departamento, nome_departamento, descricao_departamento, id_responsavel) FROM stdin;
\.


--
-- TOC entry 3525 (class 0 OID 17897)
-- Dependencies: 241
-- Data for Name: despesa; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.despesa (id_despesa, id_pedido_compra, valor_despesa, data_despesa) FROM stdin;
\.


--
-- TOC entry 3503 (class 0 OID 17726)
-- Dependencies: 219
-- Data for Name: fornecedor; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.fornecedor (id_fornecedor, nome_fornecedor, endereco_fornecedor, tel_fornecedor, principal_fornecedor, cnpj_fornecedor) FROM stdin;
\.


--
-- TOC entry 3509 (class 0 OID 17765)
-- Dependencies: 225
-- Data for Name: funcionario; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.funcionario (id_funcionario, nome_funcionario, cpf_funcionario, id_departamento, cargo_funcionario) FROM stdin;
\.


--
-- TOC entry 3515 (class 0 OID 17812)
-- Dependencies: 231
-- Data for Name: item_pedido; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.item_pedido (id_item_pedido, id_pedido_compra, id_componente, quantidade_item_pedido, preco_unitario_item_pedido) FROM stdin;
\.


--
-- TOC entry 3527 (class 0 OID 17917)
-- Dependencies: 243
-- Data for Name: lista_componentes; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.lista_componentes (id_lista_componentes, id_tipo_veiculo, id_componente) FROM stdin;
\.


--
-- TOC entry 3519 (class 0 OID 17851)
-- Dependencies: 235
-- Data for Name: notificacao; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.notificacao (id_notificacao, id_departamento, id_componente, quantidade_notificacao, data_notificacao) FROM stdin;
\.


--
-- TOC entry 3513 (class 0 OID 17795)
-- Dependencies: 229
-- Data for Name: pedido_compra; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.pedido_compra (id_pedido_compra, data_pedido, id_departamento, id_fornecedor) FROM stdin;
\.


--
-- TOC entry 3523 (class 0 OID 17885)
-- Dependencies: 239
-- Data for Name: receita; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.receita (id_receita, id_contrato, valor_receita, data_receita) FROM stdin;
\.


--
-- TOC entry 3517 (class 0 OID 17829)
-- Dependencies: 233
-- Data for Name: tipo_componente; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.tipo_componente (id_tipo_componente, nome_tipo_componente, descricao_tipo_componente) FROM stdin;
\.


--
-- TOC entry 3501 (class 0 OID 17719)
-- Dependencies: 217
-- Data for Name: tipo_veiculo; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.tipo_veiculo (id_tipo_veiculo, nome_tipo) FROM stdin;
\.


--
-- TOC entry 3505 (class 0 OID 17738)
-- Dependencies: 221
-- Data for Name: veiculo; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.veiculo (id_veiculo, modelo_veiculo, ano_veiculo, id_cliente, id_tipo) FROM stdin;
\.


--
-- TOC entry 3548 (class 0 OID 0)
-- Dependencies: 214
-- Name: cliente_id_cliente_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.cliente_id_cliente_seq', 1, false);


--
-- TOC entry 3549 (class 0 OID 0)
-- Dependencies: 226
-- Name: componente_id_componente_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.componente_id_componente_seq', 1, false);


--
-- TOC entry 3550 (class 0 OID 0)
-- Dependencies: 236
-- Name: contrato_id_contrato_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.contrato_id_contrato_seq', 1, false);


--
-- TOC entry 3551 (class 0 OID 0)
-- Dependencies: 222
-- Name: departamento_id_departamento_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.departamento_id_departamento_seq', 1, false);


--
-- TOC entry 3552 (class 0 OID 0)
-- Dependencies: 240
-- Name: despesa_id_despesa_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.despesa_id_despesa_seq', 1, false);


--
-- TOC entry 3553 (class 0 OID 0)
-- Dependencies: 218
-- Name: fornecedor_id_fornecedor_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.fornecedor_id_fornecedor_seq', 1, false);


--
-- TOC entry 3554 (class 0 OID 0)
-- Dependencies: 224
-- Name: funcionario_id_funcionario_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.funcionario_id_funcionario_seq', 1, false);


--
-- TOC entry 3555 (class 0 OID 0)
-- Dependencies: 230
-- Name: item_pedido_id_item_pedido_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.item_pedido_id_item_pedido_seq', 1, false);


--
-- TOC entry 3556 (class 0 OID 0)
-- Dependencies: 242
-- Name: lista_componentes_id_lista_componentes_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.lista_componentes_id_lista_componentes_seq', 1, false);


--
-- TOC entry 3557 (class 0 OID 0)
-- Dependencies: 234
-- Name: notificacao_id_notificacao_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.notificacao_id_notificacao_seq', 1, false);


--
-- TOC entry 3558 (class 0 OID 0)
-- Dependencies: 228
-- Name: pedido_compra_id_pedido_compra_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.pedido_compra_id_pedido_compra_seq', 1, false);


--
-- TOC entry 3559 (class 0 OID 0)
-- Dependencies: 238
-- Name: receita_id_receita_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.receita_id_receita_seq', 1, false);


--
-- TOC entry 3560 (class 0 OID 0)
-- Dependencies: 232
-- Name: tipo_componente_id_tipo_componente_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.tipo_componente_id_tipo_componente_seq', 1, false);


--
-- TOC entry 3561 (class 0 OID 0)
-- Dependencies: 216
-- Name: tipo_veiculo_id_tipo_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.tipo_veiculo_id_tipo_seq', 1, false);


--
-- TOC entry 3562 (class 0 OID 0)
-- Dependencies: 220
-- Name: veiculo_id_veiculo_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.veiculo_id_veiculo_seq', 1, false);


--
-- TOC entry 3304 (class 2606 OID 17717)
-- Name: cliente cliente_cpf_cliente_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.cliente
    ADD CONSTRAINT cliente_cpf_cliente_key UNIQUE (cpf_cliente);


--
-- TOC entry 3306 (class 2606 OID 17715)
-- Name: cliente cliente_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.cliente
    ADD CONSTRAINT cliente_pkey PRIMARY KEY (id_cliente);


--
-- TOC entry 3322 (class 2606 OID 17793)
-- Name: componente componente_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.componente
    ADD CONSTRAINT componente_pkey PRIMARY KEY (id_componente);


--
-- TOC entry 3332 (class 2606 OID 17873)
-- Name: contrato contrato_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.contrato
    ADD CONSTRAINT contrato_pkey PRIMARY KEY (id_contrato);


--
-- TOC entry 3316 (class 2606 OID 17762)
-- Name: departamento departamento_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.departamento
    ADD CONSTRAINT departamento_pkey PRIMARY KEY (id_departamento);


--
-- TOC entry 3336 (class 2606 OID 17902)
-- Name: despesa despesa_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.despesa
    ADD CONSTRAINT despesa_pkey PRIMARY KEY (id_despesa);


--
-- TOC entry 3310 (class 2606 OID 17736)
-- Name: fornecedor fornecedor_cnpj_fornecedor_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.fornecedor
    ADD CONSTRAINT fornecedor_cnpj_fornecedor_key UNIQUE (cnpj_fornecedor);


--
-- TOC entry 3312 (class 2606 OID 17734)
-- Name: fornecedor fornecedor_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.fornecedor
    ADD CONSTRAINT fornecedor_pkey PRIMARY KEY (id_fornecedor);


--
-- TOC entry 3318 (class 2606 OID 17774)
-- Name: funcionario funcionario_cpf_funcionario_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.funcionario
    ADD CONSTRAINT funcionario_cpf_funcionario_key UNIQUE (cpf_funcionario);


--
-- TOC entry 3320 (class 2606 OID 17772)
-- Name: funcionario funcionario_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.funcionario
    ADD CONSTRAINT funcionario_pkey PRIMARY KEY (id_funcionario);


--
-- TOC entry 3326 (class 2606 OID 17817)
-- Name: item_pedido item_pedido_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.item_pedido
    ADD CONSTRAINT item_pedido_pkey PRIMARY KEY (id_item_pedido);


--
-- TOC entry 3338 (class 2606 OID 17922)
-- Name: lista_componentes lista_componentes_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.lista_componentes
    ADD CONSTRAINT lista_componentes_pkey PRIMARY KEY (id_lista_componentes);


--
-- TOC entry 3330 (class 2606 OID 17856)
-- Name: notificacao notificacao_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.notificacao
    ADD CONSTRAINT notificacao_pkey PRIMARY KEY (id_notificacao);


--
-- TOC entry 3324 (class 2606 OID 17800)
-- Name: pedido_compra pedido_compra_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.pedido_compra
    ADD CONSTRAINT pedido_compra_pkey PRIMARY KEY (id_pedido_compra);


--
-- TOC entry 3334 (class 2606 OID 17890)
-- Name: receita receita_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.receita
    ADD CONSTRAINT receita_pkey PRIMARY KEY (id_receita);


--
-- TOC entry 3328 (class 2606 OID 17836)
-- Name: tipo_componente tipo_componente_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.tipo_componente
    ADD CONSTRAINT tipo_componente_pkey PRIMARY KEY (id_tipo_componente);


--
-- TOC entry 3308 (class 2606 OID 17724)
-- Name: tipo_veiculo tipo_veiculo_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.tipo_veiculo
    ADD CONSTRAINT tipo_veiculo_pkey PRIMARY KEY (id_tipo_veiculo);


--
-- TOC entry 3314 (class 2606 OID 17743)
-- Name: veiculo veiculo_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.veiculo
    ADD CONSTRAINT veiculo_pkey PRIMARY KEY (id_veiculo);


--
-- TOC entry 3343 (class 2606 OID 17837)
-- Name: componente componente_id_tipo_componente_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.componente
    ADD CONSTRAINT componente_id_tipo_componente_fkey FOREIGN KEY (id_tipo_componente) REFERENCES public.tipo_componente(id_tipo_componente);


--
-- TOC entry 3350 (class 2606 OID 17874)
-- Name: contrato contrato_id_cliente_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.contrato
    ADD CONSTRAINT contrato_id_cliente_fkey FOREIGN KEY (id_cliente) REFERENCES public.cliente(id_cliente);


--
-- TOC entry 3351 (class 2606 OID 17879)
-- Name: contrato contrato_id_veiculo_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.contrato
    ADD CONSTRAINT contrato_id_veiculo_fkey FOREIGN KEY (id_veiculo) REFERENCES public.veiculo(id_veiculo);


--
-- TOC entry 3341 (class 2606 OID 17780)
-- Name: departamento departamento_id_responsavel_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.departamento
    ADD CONSTRAINT departamento_id_responsavel_fkey FOREIGN KEY (id_responsavel) REFERENCES public.funcionario(id_funcionario);


--
-- TOC entry 3353 (class 2606 OID 17903)
-- Name: despesa despesa_id_pedido_compra_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.despesa
    ADD CONSTRAINT despesa_id_pedido_compra_fkey FOREIGN KEY (id_pedido_compra) REFERENCES public.pedido_compra(id_pedido_compra);


--
-- TOC entry 3342 (class 2606 OID 17775)
-- Name: funcionario funcionario_id_departamento_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.funcionario
    ADD CONSTRAINT funcionario_id_departamento_fkey FOREIGN KEY (id_departamento) REFERENCES public.departamento(id_departamento);


--
-- TOC entry 3346 (class 2606 OID 17823)
-- Name: item_pedido item_pedido_id_componente_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.item_pedido
    ADD CONSTRAINT item_pedido_id_componente_fkey FOREIGN KEY (id_componente) REFERENCES public.componente(id_componente);


--
-- TOC entry 3347 (class 2606 OID 17818)
-- Name: item_pedido item_pedido_id_pedido_compra_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.item_pedido
    ADD CONSTRAINT item_pedido_id_pedido_compra_fkey FOREIGN KEY (id_pedido_compra) REFERENCES public.pedido_compra(id_pedido_compra);


--
-- TOC entry 3354 (class 2606 OID 17928)
-- Name: lista_componentes lista_componentes_id_componente_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.lista_componentes
    ADD CONSTRAINT lista_componentes_id_componente_fkey FOREIGN KEY (id_componente) REFERENCES public.componente(id_componente);


--
-- TOC entry 3355 (class 2606 OID 17923)
-- Name: lista_componentes lista_componentes_id_tipo_veiculo_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.lista_componentes
    ADD CONSTRAINT lista_componentes_id_tipo_veiculo_fkey FOREIGN KEY (id_tipo_veiculo) REFERENCES public.tipo_veiculo(id_tipo_veiculo);


--
-- TOC entry 3348 (class 2606 OID 17862)
-- Name: notificacao notificacao_id_componente_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.notificacao
    ADD CONSTRAINT notificacao_id_componente_fkey FOREIGN KEY (id_componente) REFERENCES public.componente(id_componente);


--
-- TOC entry 3349 (class 2606 OID 17857)
-- Name: notificacao notificacao_id_departamento_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.notificacao
    ADD CONSTRAINT notificacao_id_departamento_fkey FOREIGN KEY (id_departamento) REFERENCES public.departamento(id_departamento);


--
-- TOC entry 3344 (class 2606 OID 17801)
-- Name: pedido_compra pedido_compra_id_departamento_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.pedido_compra
    ADD CONSTRAINT pedido_compra_id_departamento_fkey FOREIGN KEY (id_departamento) REFERENCES public.departamento(id_departamento);


--
-- TOC entry 3345 (class 2606 OID 17806)
-- Name: pedido_compra pedido_compra_id_fornecedor_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.pedido_compra
    ADD CONSTRAINT pedido_compra_id_fornecedor_fkey FOREIGN KEY (id_fornecedor) REFERENCES public.fornecedor(id_fornecedor);


--
-- TOC entry 3352 (class 2606 OID 17891)
-- Name: receita receita_id_contrato_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.receita
    ADD CONSTRAINT receita_id_contrato_fkey FOREIGN KEY (id_contrato) REFERENCES public.contrato(id_contrato);


--
-- TOC entry 3339 (class 2606 OID 17744)
-- Name: veiculo veiculo_id_cliente_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.veiculo
    ADD CONSTRAINT veiculo_id_cliente_fkey FOREIGN KEY (id_cliente) REFERENCES public.cliente(id_cliente);


--
-- TOC entry 3340 (class 2606 OID 17749)
-- Name: veiculo veiculo_id_tipo_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.veiculo
    ADD CONSTRAINT veiculo_id_tipo_fkey FOREIGN KEY (id_tipo) REFERENCES public.tipo_veiculo(id_tipo_veiculo);


-- Completed on 2024-09-23 20:08:47 -03

--
-- PostgreSQL database dump complete
--

