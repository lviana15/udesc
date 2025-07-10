import { Prop, Schema, SchemaFactory } from "@nestjs/mongoose"
import { ObjectId } from 'mongodb'
import { Document } from 'mongoose'

@Schema()
export class Funcionario extends Document {
    @Prop()
    _id: ObjectId
    
    @Prop()
    nome_funcionario: string

    @Prop()
    cpf_funcionario: string

    @Prop()
    cargo_funcionario: string

    @Prop()
    id_departamento: string

    @Prop()
    id_responsavel: string
}

export const FuncionarioSchema = SchemaFactory.createForClass(Funcionario)