-- CreateTable
CREATE TABLE "cliente" (
    "id_cliente" SERIAL NOT NULL,
    "nome_cliente" VARCHAR(255) NOT NULL,
    "cpf_cliente" VARCHAR(12) NOT NULL,
    "endereco_cliente" VARCHAR(255) NOT NULL,
    "tel_cliente" VARCHAR(255) NOT NULL,

    CONSTRAINT "cliente_pkey" PRIMARY KEY ("id_cliente")
);

-- CreateTable
CREATE TABLE "componente" (
    "id_componente" SERIAL NOT NULL,
    "nome_componente" VARCHAR(255) NOT NULL,
    "preco_componente" DECIMAL(10,2) NOT NULL,
    "id_tipo_componente" INTEGER NOT NULL,
    "qtd_estoque" INTEGER NOT NULL DEFAULT 0,
    "qtd_minima" INTEGER DEFAULT 0,

    CONSTRAINT "componente_pkey" PRIMARY KEY ("id_componente")
);

-- CreateTable
CREATE TABLE "contrato" (
    "id_contrato" SERIAL NOT NULL,
    "id_cliente" INTEGER NOT NULL,
    "id_veiculo" INTEGER NOT NULL,
    "data_contrato" DATE NOT NULL,
    "valor_contrato" DECIMAL(10,2) NOT NULL,
    "status_contrato" VARCHAR(50) NOT NULL,

    CONSTRAINT "contrato_pkey" PRIMARY KEY ("id_contrato")
);

-- CreateTable
CREATE TABLE "departamento" (
    "id_departamento" SERIAL NOT NULL,
    "nome_departamento" VARCHAR(255) NOT NULL,
    "descricao_departamento" TEXT,
    "id_responsavel" INTEGER,

    CONSTRAINT "departamento_pkey" PRIMARY KEY ("id_departamento")
);

-- CreateTable
CREATE TABLE "despesa" (
    "id_despesa" SERIAL NOT NULL,
    "id_pedido_compra" INTEGER NOT NULL,
    "valor_despesa" DECIMAL(10,2) NOT NULL,
    "data_despesa" DATE NOT NULL,

    CONSTRAINT "despesa_pkey" PRIMARY KEY ("id_despesa")
);

-- CreateTable
CREATE TABLE "fornecedor" (
    "id_fornecedor" SERIAL NOT NULL,
    "nome_fornecedor" VARCHAR(255) NOT NULL,
    "endereco_fornecedor" VARCHAR(255) NOT NULL,
    "tel_fornecedor" VARCHAR(255) NOT NULL,
    "principal_fornecedor" BOOLEAN DEFAULT false,
    "cnpj_fornecedor" VARCHAR(15) NOT NULL,

    CONSTRAINT "fornecedor_pkey" PRIMARY KEY ("id_fornecedor")
);

-- CreateTable
CREATE TABLE "funcionario" (
    "id_funcionario" SERIAL NOT NULL,
    "nome_funcionario" VARCHAR(255) NOT NULL,
    "cpf_funcionario" VARCHAR(12) NOT NULL,
    "id_departamento" INTEGER NOT NULL,
    "cargo_funcionario" VARCHAR(255),
    "id_responsavel" INTEGER,

    CONSTRAINT "funcionario_pkey" PRIMARY KEY ("id_funcionario")
);

-- CreateTable
CREATE TABLE "item_pedido" (
    "id_item_pedido" SERIAL NOT NULL,
    "id_pedido_compra" INTEGER NOT NULL,
    "id_componente" INTEGER NOT NULL,
    "quantidade_item_pedido" INTEGER NOT NULL,
    "preco_unitario_item_pedido" DECIMAL(10,2) NOT NULL,

    CONSTRAINT "item_pedido_pkey" PRIMARY KEY ("id_item_pedido")
);

-- CreateTable
CREATE TABLE "lista_componentes" (
    "id_lista_componentes" SERIAL NOT NULL,
    "id_tipo_veiculo" INTEGER NOT NULL,
    "id_componente" INTEGER NOT NULL,

    CONSTRAINT "lista_componentes_pkey" PRIMARY KEY ("id_lista_componentes")
);

-- CreateTable
CREATE TABLE "notificacao" (
    "id_notificacao" SERIAL NOT NULL,
    "id_departamento" INTEGER NOT NULL,
    "id_componente" INTEGER NOT NULL,
    "quantidade_notificacao" INTEGER NOT NULL,
    "data_notificacao" DATE NOT NULL,

    CONSTRAINT "notificacao_pkey" PRIMARY KEY ("id_notificacao")
);

-- CreateTable
CREATE TABLE "pedido_compra" (
    "id_pedido_compra" SERIAL NOT NULL,
    "data_pedido" DATE NOT NULL,
    "id_departamento" INTEGER NOT NULL,
    "id_fornecedor" INTEGER NOT NULL,

    CONSTRAINT "pedido_compra_pkey" PRIMARY KEY ("id_pedido_compra")
);

-- CreateTable
CREATE TABLE "receita" (
    "id_receita" SERIAL NOT NULL,
    "id_contrato" INTEGER NOT NULL,
    "valor_receita" DECIMAL(10,2) NOT NULL,
    "data_receita" DATE NOT NULL,

    CONSTRAINT "receita_pkey" PRIMARY KEY ("id_receita")
);

-- CreateTable
CREATE TABLE "tipo_componente" (
    "id_tipo_componente" SERIAL NOT NULL,
    "nome_tipo_componente" VARCHAR(255) NOT NULL,
    "descricao_tipo_componente" VARCHAR(255) NOT NULL,

    CONSTRAINT "tipo_componente_pkey" PRIMARY KEY ("id_tipo_componente")
);

-- CreateTable
CREATE TABLE "tipo_veiculo" (
    "id_tipo_veiculo" SERIAL NOT NULL,
    "nome_tipo" VARCHAR(255) NOT NULL,

    CONSTRAINT "tipo_veiculo_pkey" PRIMARY KEY ("id_tipo_veiculo")
);

-- CreateTable
CREATE TABLE "veiculo" (
    "id_veiculo" SERIAL NOT NULL,
    "modelo_veiculo" VARCHAR(255) NOT NULL,
    "ano_veiculo" INTEGER NOT NULL,
    "id_cliente" INTEGER NOT NULL,
    "id_tipo" INTEGER NOT NULL,

    CONSTRAINT "veiculo_pkey" PRIMARY KEY ("id_veiculo")
);

-- CreateIndex
CREATE UNIQUE INDEX "cliente_cpf_cliente_key" ON "cliente"("cpf_cliente");

-- CreateIndex
CREATE UNIQUE INDEX "fornecedor_cnpj_fornecedor_key" ON "fornecedor"("cnpj_fornecedor");

-- CreateIndex
CREATE UNIQUE INDEX "funcionario_cpf_funcionario_key" ON "funcionario"("cpf_funcionario");

-- AddForeignKey
ALTER TABLE "componente" ADD CONSTRAINT "componente_id_tipo_componente_fkey" FOREIGN KEY ("id_tipo_componente") REFERENCES "tipo_componente"("id_tipo_componente") ON DELETE NO ACTION ON UPDATE NO ACTION;

-- AddForeignKey
ALTER TABLE "contrato" ADD CONSTRAINT "contrato_id_cliente_fkey" FOREIGN KEY ("id_cliente") REFERENCES "cliente"("id_cliente") ON DELETE NO ACTION ON UPDATE NO ACTION;

-- AddForeignKey
ALTER TABLE "contrato" ADD CONSTRAINT "contrato_id_veiculo_fkey" FOREIGN KEY ("id_veiculo") REFERENCES "veiculo"("id_veiculo") ON DELETE NO ACTION ON UPDATE NO ACTION;

-- AddForeignKey
ALTER TABLE "departamento" ADD CONSTRAINT "departamento_id_responsavel_fkey" FOREIGN KEY ("id_responsavel") REFERENCES "funcionario"("id_funcionario") ON DELETE NO ACTION ON UPDATE NO ACTION;

-- AddForeignKey
ALTER TABLE "despesa" ADD CONSTRAINT "despesa_id_pedido_compra_fkey" FOREIGN KEY ("id_pedido_compra") REFERENCES "pedido_compra"("id_pedido_compra") ON DELETE NO ACTION ON UPDATE NO ACTION;

-- AddForeignKey
ALTER TABLE "funcionario" ADD CONSTRAINT "funcionario_id_departamento_fkey_unique" FOREIGN KEY ("id_departamento") REFERENCES "departamento"("id_departamento") ON DELETE NO ACTION ON UPDATE NO ACTION;

-- AddForeignKey
ALTER TABLE "funcionario" ADD CONSTRAINT "funcionario_id_responsavel_fkey" FOREIGN KEY ("id_responsavel") REFERENCES "departamento"("id_departamento") ON DELETE SET NULL ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "funcionario" ADD CONSTRAINT "funcionario_id_departamento_fkey" FOREIGN KEY ("id_departamento") REFERENCES "departamento"("id_departamento") ON DELETE RESTRICT ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "item_pedido" ADD CONSTRAINT "item_pedido_id_componente_fkey" FOREIGN KEY ("id_componente") REFERENCES "componente"("id_componente") ON DELETE NO ACTION ON UPDATE NO ACTION;

-- AddForeignKey
ALTER TABLE "item_pedido" ADD CONSTRAINT "item_pedido_id_pedido_compra_fkey" FOREIGN KEY ("id_pedido_compra") REFERENCES "pedido_compra"("id_pedido_compra") ON DELETE NO ACTION ON UPDATE NO ACTION;

-- AddForeignKey
ALTER TABLE "lista_componentes" ADD CONSTRAINT "lista_componentes_id_componente_fkey" FOREIGN KEY ("id_componente") REFERENCES "componente"("id_componente") ON DELETE NO ACTION ON UPDATE NO ACTION;

-- AddForeignKey
ALTER TABLE "lista_componentes" ADD CONSTRAINT "lista_componentes_id_tipo_veiculo_fkey" FOREIGN KEY ("id_tipo_veiculo") REFERENCES "tipo_veiculo"("id_tipo_veiculo") ON DELETE NO ACTION ON UPDATE NO ACTION;

-- AddForeignKey
ALTER TABLE "notificacao" ADD CONSTRAINT "notificacao_id_componente_fkey" FOREIGN KEY ("id_componente") REFERENCES "componente"("id_componente") ON DELETE NO ACTION ON UPDATE NO ACTION;

-- AddForeignKey
ALTER TABLE "notificacao" ADD CONSTRAINT "notificacao_id_departamento_fkey" FOREIGN KEY ("id_departamento") REFERENCES "departamento"("id_departamento") ON DELETE NO ACTION ON UPDATE NO ACTION;

-- AddForeignKey
ALTER TABLE "pedido_compra" ADD CONSTRAINT "pedido_compra_id_departamento_fkey" FOREIGN KEY ("id_departamento") REFERENCES "departamento"("id_departamento") ON DELETE NO ACTION ON UPDATE NO ACTION;

-- AddForeignKey
ALTER TABLE "pedido_compra" ADD CONSTRAINT "pedido_compra_id_fornecedor_fkey" FOREIGN KEY ("id_fornecedor") REFERENCES "fornecedor"("id_fornecedor") ON DELETE NO ACTION ON UPDATE NO ACTION;

-- AddForeignKey
ALTER TABLE "receita" ADD CONSTRAINT "receita_id_contrato_fkey" FOREIGN KEY ("id_contrato") REFERENCES "contrato"("id_contrato") ON DELETE NO ACTION ON UPDATE NO ACTION;

-- AddForeignKey
ALTER TABLE "veiculo" ADD CONSTRAINT "veiculo_id_cliente_fkey" FOREIGN KEY ("id_cliente") REFERENCES "cliente"("id_cliente") ON DELETE NO ACTION ON UPDATE NO ACTION;

-- AddForeignKey
ALTER TABLE "veiculo" ADD CONSTRAINT "veiculo_id_tipo_fkey" FOREIGN KEY ("id_tipo") REFERENCES "tipo_veiculo"("id_tipo_veiculo") ON DELETE NO ACTION ON UPDATE NO ACTION;
