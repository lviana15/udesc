import { Controller, Get, Post, Body, Param, Put, Delete } from '@nestjs/common'
import { ObjectId } from 'mongodb'
import { ContratoServiceImpl } from 'src/domain/services/ContratoService'
import { Contrato } from 'src/mongo/schemas/contrato.schema'

@Controller('contratos')
export class ContratoController {
    constructor(private contratoService: ContratoServiceImpl) { }

    @Post()
    async create(@Body() data: Contrato): Promise<boolean> {
        return this.contratoService.create(data)
    }

    @Get()
    async findAll(): Promise<Contrato[]> {
        return this.contratoService.findAll()
    }

    @Get(':id')
    async findById(@Param('id') id: string): Promise<Contrato> {
        return this.contratoService.findById(new ObjectId(id))
    }

    @Put(':id')
    async update(
        @Param('id') id: string,
        @Body() data: Partial<Contrato>
    ): Promise<boolean> {
        return this.contratoService.update(new ObjectId(id), data)
    }

    @Delete(':id')
    async delete(@Param('id') id: string): Promise<boolean> {
        return this.contratoService.delete(new ObjectId(id))
    }
}
