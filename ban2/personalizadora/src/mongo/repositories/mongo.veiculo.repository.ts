import { ObjectId } from 'mongodb'
import { Connection } from 'mongoose'
import { Veiculo } from '../schemas/veiculo.schema'
import { InjectConnection } from '@nestjs/mongoose'
import { TipoVeiculo } from '../schemas/tipoveiculo.schema'

export class MongoVeiculoRepository {
    constructor(
        @InjectConnection() private connection: Connection
    ) { }

    async create(veiculo: Veiculo): Promise<boolean> {
        const veiculoWithId = { ...veiculo, _id: new ObjectId() }

        const response = await this.connection
            .collection('veiculo')
            .insertOne(veiculoWithId)

        return response.acknowledged
    }

    async findById(id: ObjectId): Promise<Veiculo | null> {
        const query = { _id: id }

        const veiculo = await this.connection
            .collection<Veiculo>('veiculo')
            .findOne(query)

        const id_tipo = new ObjectId(veiculo.id_tipo)

        const tipo_veiculo = await this.connection
            .collection<TipoVeiculo>('tipoveiculo')
            .findOne({ _id: id_tipo })

        const response = {
            ...veiculo,
            tipo_veiculo
        }

        return response
    }

    async update(id: ObjectId, veiculo: Partial<Veiculo>): Promise<boolean> {
        const query = { _id: id }

        const response = await this.connection.collection<Veiculo>('veiculo').updateOne(query, { $set: veiculo })

        return response.acknowledged
    }

    async delete(id: ObjectId): Promise<boolean> {
        const response = await this.connection.collection<Veiculo>('veiculo').deleteOne({ _id: id })

        return response.acknowledged
    }

    async findAll(): Promise<Veiculo[]> {
        const response = await this.connection
            .collection<Veiculo>('veiculo')
            .find()
            .toArray()

        return response
    }
}

export default MongoVeiculoRepository;