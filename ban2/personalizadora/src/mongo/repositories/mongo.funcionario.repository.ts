import { ObjectId } from 'mongodb';
import { Connection } from 'mongoose';
import { Funcionario } from '../schemas/funcionario.schema';
import { InjectConnection } from '@nestjs/mongoose';

export class MongoFuncionarioRepository {
    constructor(
        @InjectConnection() private connection: Connection
    ) { }

    async create(funcionario: Funcionario): Promise<boolean> {
        const funcionarioWithId = { ...funcionario, _id: new ObjectId() }

        const response = await this.connection
            .collection('funcionario')
            .insertOne(funcionarioWithId)

        return response.acknowledged
    }

    async findById(id: ObjectId): Promise<Funcionario | null> {
        const query = { _id: id }

        const response = await this.connection
            .collection<Funcionario>('funcionario')
            .findOne(query)

        return response
    }

    async findAll(): Promise<Funcionario[]> {
        const response = await this.connection
            .collection<Funcionario>('funcionario')
            .find()
            .toArray()

        return response
    }
    
    async update(id: ObjectId, funcionario: Partial<Funcionario>): Promise<boolean> {
        const query = { _id: id }

        const response = await this.connection.collection<Funcionario>('funcionario').updateOne(query, { $set: funcionario })

        return response.acknowledged
    }

    async delete(id: ObjectId): Promise<boolean> {
        const response = await this.connection.collection<Funcionario>('funcionario').deleteOne({ _id: id })

        return response.acknowledged
    }

}

export default MongoFuncionarioRepository