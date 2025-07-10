import { Prop, Schema, SchemaFactory } from '@nestjs/mongoose'
import { ObjectId } from 'mongodb'
import { Document } from 'mongoose'

@Schema()
export class Contrato extends Document {
    @Prop()
    _id: ObjectId
    
    @Prop()
    id_cliente: ObjectId

    @Prop()
    id_veiculo: ObjectId
    
    @Prop()
    data_contrato: Date

    @Prop()
    valor_contrato: number

    @Prop()
    status_contrato: string
}

export const ContratoSchema = SchemaFactory.createForClass(Contrato)