import { ObjectId } from 'mongodb';
import { Connection } from 'mongoose';
import { Contrato } from '../schemas/contrato.schema';
import { InjectConnection } from '@nestjs/mongoose';
import { Cliente } from '../schemas/cliente.schema';
import { Veiculo } from '../schemas/veiculo.schema';


export class MongoContratoRepository {
    constructor(
        @InjectConnection() private connection: Connection
    ) { }

    async create(contrato: Contrato): Promise<boolean> {
        const contratoWithId = { ...contrato, _id: new ObjectId() }

        const response = await this.connection
            .collection('contrato')
            .insertOne(contratoWithId)

        return response.acknowledged
    }

    async findById(id: ObjectId): Promise<Contrato | null> {
        const query = { _id: id }

        const contrato = await this.connection.collection<Contrato>('contrato').findOne(query)

        const id_cliente = new ObjectId(contrato.id_cliente)
        const id_veiculo = new ObjectId(contrato.id_veiculo)
        
        const cliente = await this.connection.collection<Cliente>('cliente').findOne({ _id: id_cliente })
        const veiculo = await this.connection.collection<Veiculo>('veiculo').findOne({ _id: id_veiculo })

        const response = {
            ...contrato,
            cliente,
            veiculo
        }

        return response
    }

    async update(id: ObjectId, contrato: Partial<Contrato>): Promise<boolean> {
        const query = { _id: id }

        const response = await this.connection.collection<Contrato>('contrato').updateOne(query, { $set: contrato })

        return response.acknowledged
    }

    async delete(id: string): Promise<boolean> {

        const response = await this.connection.collection<Contrato>('contrato').deleteOne({ id })

        return response.acknowledged
    }

    async findAll(): Promise<Contrato[]> {
        const response = await this.connection
            .collection<Contrato>('contrato')
            .find()
            .toArray()

        return response
    }
}

export default MongoContratoRepository