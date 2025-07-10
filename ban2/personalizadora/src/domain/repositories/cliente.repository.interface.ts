import { ObjectId } from "mongodb"
import { Cliente } from 'src/mongo/schemas/cliente.schema'

export interface IClienteRepository {
    create(cliente: Cliente): Promise<boolean>
    findById(id: ObjectId): Promise<Cliente | null>
    findAll(): Promise<Cliente[]>
    update(id: ObjectId, cliente: Partial<Cliente>): Promise<boolean>
    delete(id: ObjectId): Promise<boolean>
}

