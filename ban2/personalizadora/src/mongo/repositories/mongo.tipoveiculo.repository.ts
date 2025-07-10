import { ObjectId } from 'mongodb';
import { Connection } from 'mongoose';
import { TipoVeiculo } from '../schemas/tipoveiculo.schema';
import { InjectConnection } from '@nestjs/mongoose';

export class MongoTipoVeiculoRepository {
    constructor(
        @InjectConnection() private connection: Connection
    ) { }

    async create(tipoVeiculo: TipoVeiculo): Promise<boolean> {
        const tipoVeiculoWithId = { ...tipoVeiculo, _id: new ObjectId() }

        const response = await this.connection.useDb('personalizadora')
            .collection('tipoveiculo')
            .insertOne(tipoVeiculoWithId)

        return response.acknowledged
    }

    async findById(id: ObjectId): Promise<TipoVeiculo | null> {
        const query = { _id: id }

        const response = await this.connection
            .collection<TipoVeiculo>('tipoveiculo')
            .findOne(query)

        return response
    }

    async update(id: string, tipoVeiculo: Partial<TipoVeiculo>): Promise<boolean> {
        const query = { _id: new ObjectId(id) }

        const response = await this.connection.collection<TipoVeiculo>('tipoveiculo').updateOne(query, { $set: tipoVeiculo })

        return response.acknowledged
    }

    async delete(id: string): Promise<boolean> {
        const response = await this.connection.collection<TipoVeiculo>('tipoveiculo').deleteOne({ _id: new ObjectId(id) })

        return response.acknowledged
    }

    async findAll(): Promise<TipoVeiculo[]> {
        const response = await this.connection
            .collection<TipoVeiculo>('tipoveiculo')
            .find()
            .toArray()

        return response
    }
}

export default MongoTipoVeiculoRepository