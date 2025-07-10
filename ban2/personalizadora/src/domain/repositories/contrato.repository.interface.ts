import { ObjectId } from 'mongodb'
import { Contrato } from 'src/mongo/schemas/contrato.schema'

export interface IContratoRepository {
    create(contrato: Contrato): Promise<boolean>
    findById(id: ObjectId): Promise<Contrato| null>
    findAll(): Promise<Contrato[]>
    update(id: ObjectId, contrato: Partial<Contrato>): Promise<boolean>
    delete(id: ObjectId): Promise<boolean>
}

