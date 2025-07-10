import { Controller, Get, Post, Body, Param, Put, Delete } from '@nestjs/common'
import { ObjectId } from 'mongodb'
import { TipoVeiculoServiceImpl } from '../../domain/services/TipoVeiculoService'
import { TipoVeiculo } from '../../mongo/schemas/tipoveiculo.schema'

@Controller('tipoveiculos')
export class TipoVeiculoController {
    constructor(private tipoVeiculoService: TipoVeiculoServiceImpl) { }

    @Post()
    async create(@Body() data: TipoVeiculo): Promise<boolean> {
        return this.tipoVeiculoService.create(data)
    }

    @Get()
    async findAll(): Promise<TipoVeiculo[]> {
        return this.tipoVeiculoService.findAll()
    }

    @Get(':id')
    async findById(@Param('id') id: string): Promise<TipoVeiculo | null> {
        return this.tipoVeiculoService.findById(new ObjectId(id))
    }

    @Put(':id')
    async update(
        @Param('id') id: string,
        @Body() data: Partial<TipoVeiculo>
    ): Promise<boolean> {
        return this.tipoVeiculoService.update(new ObjectId(id), data)
    }

    @Delete(':id')
    async delete(@Param('id') id: string): Promise<boolean> {
        return this.tipoVeiculoService.delete(new ObjectId(id))
    }
}
