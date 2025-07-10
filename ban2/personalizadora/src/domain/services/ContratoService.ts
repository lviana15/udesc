import { IContratoRepository } from 'src/domain/repositories/contrato.repository.interface'
import { Inject, Injectable } from '@nestjs/common'
import { ObjectId } from 'mongodb'
import { Contrato } from 'src/mongo/schemas/contrato.schema'

interface ContratoService {
    create(data: Contrato): Promise<boolean>
    findAll(): Promise<Contrato[]>
    findById(id: ObjectId): Promise<Contrato | null>
    update(id: ObjectId, data: Partial<Contrato>): Promise<boolean>
    delete(id: ObjectId): Promise<boolean>
}

@Injectable()
export class ContratoServiceImpl implements ContratoService {
    constructor(
        @Inject('IContratoRepository')
        private contratoRepository: IContratoRepository
    ) { }

    async create(data: Contrato): Promise<boolean> {
        return this.contratoRepository.create(data)
    }

    async findAll(): Promise<Contrato[]> {
        return this.contratoRepository.findAll()
    }

    async findById(id: ObjectId): Promise<Contrato | null> {
        return this.contratoRepository.findById(id)
    }

    async update(id: ObjectId, data: Partial<Contrato>): Promise<boolean> {
        return await this.contratoRepository.update(id, data)
    }

    async delete(id: ObjectId): Promise<boolean> {
        return this.contratoRepository.delete(id)
    }
}
