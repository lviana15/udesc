import { ObjectId } from "mongodb"
import { TipoVeiculo } from "src/mongo/schemas/tipoveiculo.schema"

export interface ITipoVeiculoRepository {
    create(tipoVeiculo: TipoVeiculo): Promise<boolean>
    findById(id: ObjectId): Promise<TipoVeiculo | null>
    findAll(): Promise<TipoVeiculo[]>
    update(id: ObjectId, tipoVeiculo: Partial<TipoVeiculo>): Promise<boolean>
    delete(id: ObjectId): Promise<boolean>
}
