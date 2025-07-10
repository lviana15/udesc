import { Controller, Get, Post, Put, Delete, Param, Body } from '@nestjs/common'
import { ObjectId } from 'mongodb'
import { ClienteServiceImpl } from 'src/domain/services/ClienteService'
import { Cliente } from 'src/mongo/schemas/cliente.schema'

@Controller('clientes')
export class ClienteController {
    constructor(private readonly clienteService: ClienteServiceImpl) { }

    @Post()
    async create(@Body() data: Cliente) {
        return this.clienteService.create(data)
    }

    @Get()
    async findAll() {
        return this.clienteService.findAll()
    }

    @Get(':id')
    async findById(@Param('id') id: string) {
        return this.clienteService.findById(new ObjectId(id))
    }

    @Put(':id')
    async update(@Param('id') id: string, @Body() data: Partial<Cliente>) {
        return this.clienteService.update(new ObjectId(id), data)
    }

    @Delete(':id')
    async delete(@Param('id') id: string) {
        return this.clienteService.delete(new ObjectId(id))
    }
}
