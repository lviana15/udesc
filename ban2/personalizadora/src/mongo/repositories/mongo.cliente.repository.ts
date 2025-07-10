import { IClienteRepository } from "src/domain/repositories/cliente.repository.interface"
import { Cliente } from "../schemas/cliente.schema"
import { Connection } from "mongoose"
import { ObjectId } from "mongodb"
import { InjectConnection } from "@nestjs/mongoose"

export class MongoClienteRepository implements IClienteRepository {
    constructor(
        @InjectConnection() private connection: Connection
    ) { }
    async create(cliente: Cliente): Promise<boolean> {

        const clienteWithId = { ...cliente, _id: new ObjectId() }
        const response = await this.connection.collection('cliente').insertOne(clienteWithId)

        return response.acknowledged
    }

    async findById(id: ObjectId): Promise<Cliente | null> {
        if (!id) return null

        const query = { _id: id }

        const response = await this.connection.collection<Cliente>('cliente').findOne(query)

        return response
    }

    async findAll(): Promise<Cliente[]> {
        const response = await this.connection.collection<Cliente>('cliente').find().toArray()

        return response

    }

    async update(id: ObjectId, cliente: Partial<Cliente>): Promise<boolean> {
        const query = { _id: id }

        const response = await this.connection
            .collection<Cliente>('cliente')
            .updateOne(query, { $set: cliente })

        return response.acknowledged
    }

    async delete(id: ObjectId): Promise<boolean> {
        const query = { _id: id }

        const response = await this.connection
            .collection<Cliente>('cliente')
            .deleteOne(query)

        return response.acknowledged
    }

}
