import { Test, TestingModule } from '@nestjs/testing'
import { ClienteController } from '../../infra/controllers/cliente.controller'
import { ClienteServiceImpl } from '../../domain/services/ClienteService'
import { NotFoundException } from '@nestjs/common'
import { Cliente } from '../../mongo/schemas/cliente.schema'
import { ObjectId } from 'mongodb'

describe('ClienteController', () => {
    let controller: ClienteController
    let service: jest.Mocked<ClienteServiceImpl>

    beforeEach(async () => {
        const module: TestingModule = await Test.createTestingModule({
            controllers: [ClienteController],
            providers: [
                {
                    provide: ClienteServiceImpl,
                    useValue: {
                        findAll: jest.fn(),
                        findById: jest.fn(),
                        create: jest.fn(),
                        update: jest.fn(),
                        delete: jest.fn(),
                    },
                },
            ],
        }).compile()

        controller = module.get<ClienteController>(ClienteController)
        service = module.get(ClienteServiceImpl)
    });

    describe('findAll', () => {
        it('should return all clients', async () => {
            const mockClientes: Cliente[] = [
                new Cliente({
                    _id: new ObjectId('61a74f09b63f9e39b964f1f5'),
                    id_cliente: 1,
                    nome_cliente: 'John Doe',
                    cpf_cliente: '12345678901',
                    endereco_cliente: '123 Main St',
                    tel_cliente: '1234567890',
                }),
            ];

            service.findAll.mockResolvedValue(mockClientes)

            const result = await controller.findAll()
            expect(result).toEqual(mockClientes)
            expect(service.findAll).toHaveBeenCalled()
        })
    })

    describe('findById', () => {
        it('should return a single client by ID', async () => {
            const mockCliente = new Cliente({
                _id: new ObjectId('61a74f09b63f9e39b964f1f5'),
                id_cliente: 1,
                nome_cliente: 'John Doe',
                cpf_cliente: '12345678901',
                endereco_cliente: '123 Main St',
                tel_cliente: '1234567890',
            })

            service.findById.mockResolvedValue(mockCliente)

            const result = await controller.findById('61a74f09b63f9e39b964f1f5')
            expect(result).toEqual(mockCliente)
            expect(service.findById).toHaveBeenCalledWith('61a74f09b63f9e39b964f1f5')
        })

        it('should throw NotFoundException if client not found', async () => {
            service.findById.mockResolvedValue(null)

            await expect(controller.findById('invalid-id')).rejects.toThrow(NotFoundException)
            expect(service.findById).toHaveBeenCalledWith('invalid-id')
        })
    })

    describe('create', () => {
        it('should create and return a new client', async () => {
            const createDto = {
                id_cliente: 1,
                nome_cliente: 'John Doe',
                cpf_cliente: '12345678901',
                endereco_cliente: '123 Main St',
                tel_cliente: '1234567890',
            };

            const mockCliente = {
                ...createDto,
                _id: '61a74f09b63f9e39b964f1f5',
            };

            service.create.mockResolvedValue(true)

            const result = await controller.create(new Cliente(createDto))
            expect(result).toEqual(mockCliente)
            expect(service.create).toHaveBeenCalledWith(createDto)
        })
    })

    describe('update', () => {
        it('should update and return the updated client', async () => {
            const updateDto = {
                nome_cliente: 'Jane Doe',
            }

            const mockCliente = {
                _id: '61a74f09b63f9e39b964f1f5',
                id_cliente: 1,
                nome_cliente: 'Jane Doe',
                cpf_cliente: '12345678901',
                endereco_cliente: '123 Main St',
                tel_cliente: '1234567890',
            };

            service.update.mockResolvedValue(true)

            const result = await controller.update('61a74f09b63f9e39b964f1f5', updateDto)
            expect(result).toEqual(mockCliente)
            expect(service.update).toHaveBeenCalledWith('61a74f09b63f9e39b964f1f5', updateDto)
        })

        it('should throw NotFoundException if client to update is not found', async () => {
            service.update.mockResolvedValue(null)

            await expect(controller.update('invalid-id', {})).rejects.toThrow(NotFoundException)
            expect(service.update).toHaveBeenCalledWith('invalid-id', {})
        })
    })

    describe('delete', () => {
        it('should delete a client and return true', async () => {
            service.delete.mockResolvedValue(true)

            const result = await controller.delete('61a74f09b63f9e39b964f1f5')
            expect(result).toBe(true)
            expect(service.delete).toHaveBeenCalledWith('61a74f09b63f9e39b964f1f5')
        })

        it('should throw NotFoundException if client to delete is not found', async () => {
            service.delete.mockResolvedValue(false)

            await expect(controller.delete('invalid-id')).rejects.toThrow(NotFoundException)
            expect(service.delete).toHaveBeenCalledWith('invalid-id')
        })
    })
})
