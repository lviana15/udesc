import { ObjectId } from 'mongodb'
import { Funcionario } from 'src/mongo/schemas/funcionario.schema'

export interface IFuncionarioRepository {
    create(funcionario: Funcionario): Promise<boolean>
    findById(id: ObjectId): Promise<Funcionario | null>
    findAll(): Promise<Funcionario[]>
    update(id: ObjectId,funcionario: Partial<Funcionario>): Promise<boolean>
    delete(id: ObjectId): Promise<boolean>
}

