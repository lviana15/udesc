import { Controller, Get, Post, Body, Param, Put, Delete } from '@nestjs/common'
import { FuncionarioServiceImpl } from '../../domain/services/FuncionarioService'
import { ObjectId } from 'mongodb'
import { Funcionario } from '../../mongo/schemas/funcionario.schema'

@Controller('funcionarios')
export class FuncionarioController {
    constructor(private funcionarioService: FuncionarioServiceImpl) {}

    @Post()
    async create(@Body() data: Funcionario): Promise<boolean> {
        return this.funcionarioService.create(data)
    }

    @Get()
    async findAll(): Promise<Funcionario[]> {
        return this.funcionarioService.findAll()
    }

    @Get(':id')
    async findById(@Param('id') id: string): Promise<Funcionario | null> {
        return this.funcionarioService.findById(new ObjectId(id))
    }

    @Put(':id')
    async update(
        @Param('id') id: string,
        @Body() data: Partial<Funcionario>
    ): Promise<boolean> {
        return this.funcionarioService.update(new ObjectId(id), data)
    }

    @Delete(':id')
    async delete(@Param('id') id: string): Promise<boolean> {
        return this.funcionarioService.delete(new ObjectId(id))
    }
}
