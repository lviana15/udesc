import { ITipoVeiculoRepository } from '../../domain/repositories/tipoveiculo.repository.interface'
import { Inject, Injectable } from '@nestjs/common'
import { ObjectId } from 'mongodb'
import { TipoVeiculo } from '../../mongo/schemas/tipoveiculo.schema'

interface TipoVeiculoService {
    create(data: TipoVeiculo): Promise<boolean>
    findAll(): Promise<TipoVeiculo[]>
    findById(id: ObjectId): Promise<TipoVeiculo | null>
    update(id: ObjectId, data: Partial<TipoVeiculo>): Promise<boolean>
    delete(id: ObjectId): Promise<boolean>
}

@Injectable()
export class TipoVeiculoServiceImpl implements TipoVeiculoService {
    constructor(
        @Inject('ITipoVeiculoRepository')
        private tipoVeiculoRepository: ITipoVeiculoRepository
    ) { }

    async create(data: TipoVeiculo): Promise<boolean> {
        return this.tipoVeiculoRepository.create(data)
    }

    async findAll(): Promise<TipoVeiculo[]> {
        return this.tipoVeiculoRepository.findAll()
    }

    async findById(id: ObjectId): Promise<TipoVeiculo | null> {
        return this.tipoVeiculoRepository.findById(id)
    }

    async update(id: ObjectId, data: Partial<TipoVeiculo>): Promise<boolean> {
        return this.tipoVeiculoRepository.update(id, data)
    }

    async delete(id: ObjectId): Promise<boolean> {
        return this.tipoVeiculoRepository.delete(id)
    }
}
