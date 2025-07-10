import { Prop, Schema, SchemaFactory } from '@nestjs/mongoose'
import { Document } from 'mongoose'
import { ObjectId } from 'mongodb'


@Schema()
export class TipoVeiculo extends Document {
    @Prop()
    _id: ObjectId
    
    @Prop()
    id_tipo_veiculo: number
    
    @Prop()
    tipo_veiculo: string

    @Prop()
    descricao_tipo_veiculo: string
}

export const TipoVeiculoSchema = SchemaFactory.createForClass(TipoVeiculo)