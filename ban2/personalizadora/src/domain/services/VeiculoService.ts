import { IVeiculoRepository } from '../../domain/repositories/veiculo.repository.interface'
import { Inject, Injectable } from '@nestjs/common'
import { Veiculo } from '../../mongo/schemas/veiculo.schema'
import { ObjectId } from 'mongodb'

interface VeiculoService {
    create(data: Veiculo): Promise<boolean>
    findAll(): Promise<Veiculo[]>
    findById(id: ObjectId): Promise<Veiculo | null>
    update(id: ObjectId, data: Partial<Veiculo>): Promise<boolean>
    delete(id: ObjectId): Promise<boolean>
}

@Injectable()
export class VeiculoServiceImpl implements VeiculoService {
    constructor(
        @Inject('IVeiculoRepository')
        private veiculoRepository: IVeiculoRepository
    ) { }

    async create(data: Veiculo): Promise<boolean> {
        return this.veiculoRepository.create(data)
    }

    async findAll(): Promise<Veiculo[]> {
        return this.veiculoRepository.findAll()
    }

    async findById(id: ObjectId): Promise<Veiculo | null> {
        return this.veiculoRepository.findById(id)
    }

    async update(id: ObjectId, data: Partial<Veiculo>): Promise<boolean> {
        return this.veiculoRepository.update(id, data)
    }

    async delete(id: ObjectId): Promise<boolean> {
        return this.veiculoRepository.delete(id)
    }
}
