import { IFuncionarioRepository } from '../../domain/repositories/funcionario.repository.interface'
import { Inject, Injectable } from '@nestjs/common'
import { Funcionario } from '../../mongo/schemas/funcionario.schema'
import { ObjectId } from 'mongodb'

interface FuncionarioService {
    create(data: Funcionario): Promise<boolean>
    findAll(): Promise<Funcionario[]>
    findById(id: ObjectId): Promise<Funcionario | null>
    update(id: ObjectId, data: Partial<Funcionario>): Promise<boolean>
    delete(id: ObjectId): Promise<boolean>
}

@Injectable()
export class FuncionarioServiceImpl implements FuncionarioService {
    constructor(
        @Inject('IFuncionarioRepository')
        private funcionarioRepository: IFuncionarioRepository
    ) { }

    async create(data: Funcionario): Promise<boolean> {
        return this.funcionarioRepository.create(data)
    }

    async findAll(): Promise<Funcionario[]> {
        return this.funcionarioRepository.findAll()
    }

    async findById(id: ObjectId): Promise<Funcionario | null> {
        return this.funcionarioRepository.findById(id)
    }

    async update(id: ObjectId, data: Partial<Funcionario>): Promise<boolean> {
        const existingFuncionario = await this.funcionarioRepository.findById(id);
        if (!existingFuncionario) {
            return null;
        }
        const updatedFuncionario = { ...existingFuncionario, ...data };
        return this.funcionarioRepository.update(id, updatedFuncionario);
    }

    async delete(id: ObjectId): Promise<boolean> {
        return this.funcionarioRepository.delete(id)
    }
}
