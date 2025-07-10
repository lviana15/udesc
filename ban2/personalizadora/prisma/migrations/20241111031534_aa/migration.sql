/*
  Warnings:

  - You are about to drop the column `nome_tipo` on the `tipo_veiculo` table. All the data in the column will be lost.
  - Added the required column `descricao_tipo_veiculo` to the `tipo_veiculo` table without a default value. This is not possible if the table is not empty.
  - Added the required column `nome_tipo_veiculo` to the `tipo_veiculo` table without a default value. This is not possible if the table is not empty.

*/
-- AlterTable
ALTER TABLE "tipo_veiculo" DROP COLUMN "nome_tipo",
ADD COLUMN     "descricao_tipo_veiculo" VARCHAR(255) NOT NULL,
ADD COLUMN     "nome_tipo_veiculo" VARCHAR(255) NOT NULL;
