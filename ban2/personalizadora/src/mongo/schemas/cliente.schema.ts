import { Prop, Schema, SchemaFactory } from '@nestjs/mongoose'
import { Document } from 'mongoose'
import { ObjectId } from 'mongodb'

@Schema()
export class Cliente extends Document {
    @Prop()
    _id: ObjectId
    
    @Prop()
    id_cliente: number
    
    @Prop()
    nome_cliente: string

    @Prop()
    cpf_cliente: string

    @Prop()
    endereco_cliente: string

    @Prop()
    tel_cliente: string
}

export const ClienteSchema = SchemaFactory.createForClass(Cliente)