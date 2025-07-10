import { ObjectId } from "mongodb"
import { Veiculo } from "src/mongo/schemas/veiculo.schema"

export interface IVeiculoRepository {
    create(veiculo: Veiculo): Promise<boolean>
    findById(id: ObjectId): Promise<Veiculo | null>
    findAll(): Promise<Veiculo[]>
    update(id: ObjectId, veiculo: Partial<Veiculo>): Promise<boolean>
    delete(id: ObjectId): Promise<boolean>
}
