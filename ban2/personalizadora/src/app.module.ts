import { Module } from '@nestjs/common'
import { MongooseModule } from '@nestjs/mongoose'

import { ClienteController } from 'src/infra/controllers/cliente.controller'
import { ContratoController } from 'src/infra/controllers/contrato.controller'
import { FuncionarioController } from 'src/infra/controllers/funcionario.controller'
import { TipoVeiculoController } from 'src/infra/controllers/tipoveiculo.controller'
import { VeiculoController } from 'src/infra/controllers/veiculo.controller'

import { ClienteServiceImpl } from 'src/domain/services/ClienteService'
import { ContratoServiceImpl } from 'src/domain/services/ContratoService'
import { FuncionarioServiceImpl } from 'src/domain/services/FuncionarioService'
import { TipoVeiculoServiceImpl } from 'src/domain/services/TipoVeiculoService'
import { VeiculoServiceImpl } from 'src/domain/services/VeiculoService'

import { CliModule } from './cli/cli.module'
import { MongoModule } from './mongo/mongo.module'

import { MongoClienteRepository } from './mongo/repositories/mongo.cliente.repository'
import { MongoContratoRepository } from './mongo/repositories/mongo.contrato.repository'
import { MongoFuncionarioRepository } from './mongo/repositories/mongo.funcionario.repository'
import { MongoTipoVeiculoRepository } from './mongo/repositories/mongo.tipoveiculo.repository'
import { MongoVeiculoRepository } from './mongo/repositories/mongo.veiculo.repository'

@Module({
    imports: [
        MongooseModule.forRoot('mongodb://localhost:27017/', {
            dbName: 'personalizadora'
          }),
        MongoModule,
        CliModule
    ],
    controllers: [
        ClienteController,
        ContratoController,
        FuncionarioController,
        TipoVeiculoController,
        VeiculoController,
    ],
    providers: [
        ClienteServiceImpl,
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
            provide: 'ITipoVeiculoRepository',
            useClass: MongoTipoVeiculoRepository,
        },
        {
            provide: 'IVeiculoRepository',
            useClass: MongoVeiculoRepository,
        },
        ContratoServiceImpl,
        FuncionarioServiceImpl,
        TipoVeiculoServiceImpl,
        VeiculoServiceImpl,
    ],
})
export class AppModule { }
