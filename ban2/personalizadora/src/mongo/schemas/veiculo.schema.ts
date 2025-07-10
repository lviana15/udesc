import { Prop, Schema, SchemaFactory } from "@nestjs/mongoose"
import { ObjectId } from 'mongodb'
import { Document } from 'mongoose'

@Schema()
export class Veiculo extends Document {
    @Prop()
    _id: ObjectId
    
    @Prop()
    id_veiculo: ObjectId

    @Prop()
    modelo_veiculo: string

    @Prop()
    ano_veiculo: number

    @Prop()
    id_cliente: number

    @Prop()
    id_tipo: ObjectId
}

export const VeiculoSchema = SchemaFactory.createForClass(Veiculo)