import { IClienteRepository } from 'src/domain/repositories/cliente.repository.interface'
import { Inject, Injectable } from '@nestjs/common'
import { Cliente } from 'src/mongo/schemas/cliente.schema'
import { ObjectId } from 'mongodb'

interface ClienteService {
    create(data: Cliente): Promise<boolean>
    findAll(): Promise<Cliente[]>
    findById(id: ObjectId): Promise<Cliente | null>
    update(id: ObjectId, data: Partial<Cliente>): Promise<boolean>
    delete(id: ObjectId): Promise<boolean>
}

@Injectable()
export class ClienteServiceImpl implements ClienteService {
    constructor(
        @Inject('IClienteRepository')
        private readonly clienteRepository: IClienteRepository
    ) { }

    async create(data: Cliente): Promise<boolean> {
        return this.clienteRepository.create(data)
    }

    async findAll(): Promise<Cliente[]> {
        return this.clienteRepository.findAll()
    }

    async findById(id: ObjectId): Promise<Cliente | null> {
        return this.clienteRepository.findById(id)
    }

    async update(id: ObjectId, data: Partial<Cliente>): Promise<boolean> {
        return this.clienteRepository.update(id, data)
    }

    async delete(id: ObjectId): Promise<boolean> {
        return this.clienteRepository.delete(id)
    }
}
