import { Module } from '@nestjs/common';
import { MongooseModule } from '@nestjs/mongoose';

import { Contrato, ContratoSchema } from './schemas/contrato.schema';
import { Cliente, ClienteSchema } from './schemas/cliente.schema';
import { Funcionario, FuncionarioSchema } from './schemas/funcionario.schema';
import { Veiculo, VeiculoSchema } from './schemas/veiculo.schema';
import { TipoVeiculo, TipoVeiculoSchema } from './schemas/tipoveiculo.schema';

import { MongoClienteRepository } from './repositories/mongo.cliente.repository';
import MongoContratoRepository from './repositories/mongo.contrato.repository';
import MongoFuncionarioRepository from './repositories/mongo.funcionario.repository';
import MongoVeiculoRepository from './repositories/mongo.veiculo.repository';
import MongoTipoVeiculoRepository from './repositories/mongo.tipoveiculo.repository';

import { ClienteServiceImpl } from 'src/domain/services/ClienteService';
import { ContratoServiceImpl } from 'src/domain/services/ContratoService';
import { FuncionarioServiceImpl } from 'src/domain/services/FuncionarioService';
import { VeiculoServiceImpl } from 'src/domain/services/VeiculoService';
import { TipoVeiculoServiceImpl } from 'src/domain/services/TipoVeiculoService';

@Module({
  imports: [
    MongooseModule.forFeature([
      { name: 'cliente', schema: ClienteSchema },
      { name: 'funcionario', schema: FuncionarioSchema },
      { name: 'veiculo', schema: VeiculoSchema },
      { name: 'tipoveiculo', schema: TipoVeiculoSchema },
      { name: 'contrato', schema: ContratoSchema },
    ]),
  ],
  providers: [
    {
      provide: 'IClienteRepository',
      useClass: MongoClienteRepository,
    },
    {
      provide: 'IContratoRepository',
      useClass: MongoContratoRepository,
    },
    {
      provide: 'IFuncionarioRepository',
      useClass: MongoFuncionarioRepository,
    },
    {
      provide: 'IVeiculoRepository',
      useClass: MongoVeiculoRepository,
    },
    {
      provide: 'ITipoVeiculoRepository',
      useClass: MongoTipoVeiculoRepository,
    },

    {
      provide: 'IClienteService',
      useClass: ClienteServiceImpl,
    },
    {
      provide: 'IContratoService',
      useClass: ContratoServiceImpl,
    },
    {
      provide: 'IFuncionarioService',
      useClass: FuncionarioServiceImpl,
    },
    {
      provide: 'IVeiculoService',
      useClass: VeiculoServiceImpl,
    },
    {
      provide: 'ITipoVeiculoService',
      useClass: TipoVeiculoServiceImpl,
    },
  ],
  exports: [
    'IClienteRepository',
    'IContratoRepository',
    'IFuncionarioRepository',
    'IVeiculoRepository',
    'ITipoVeiculoRepository',

    'IClienteService',
    'IContratoService',
    'IFuncionarioService',
    'IVeiculoService',
    'ITipoVeiculoService',
  ],
})
export class MongoModule { }
