import { Controller, Get, Post, Body, Param, Put, Delete } from '@nestjs/common'
import { VeiculoServiceImpl } from '../../domain/services/VeiculoService'
import { ObjectId } from 'mongodb'
import { Veiculo } from '../../mongo/schemas/veiculo.schema'

@Controller('veiculos')
export class VeiculoController {
    constructor(private veiculoService: VeiculoServiceImpl) { }

    @Post()
    async create(@Body() data: Veiculo): Promise<boolean> {
        return this.veiculoService.create(data)
    }

    @Get()
    async findAll(): Promise<Veiculo[]> {
        return this.veiculoService.findAll()
    }

    @Get(':id')
    async findById(@Param('id') id: string): Promise<Veiculo | null> {
        return this.veiculoService.findById(new ObjectId(id))
    }

    @Put(':id')
    async update(
        @Param('id') id: string,
        @Body() data: Partial<Veiculo>
    ): Promise<boolean> {
        return this.veiculoService.update(new ObjectId(id), data)
    }

    @Delete(':id')
    async delete(@Param('id') id: string): Promise<boolean> {
        return this.veiculoService.delete(new ObjectId(id))
    }
}
