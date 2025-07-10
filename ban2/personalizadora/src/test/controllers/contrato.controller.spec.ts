import { Test, TestingModule } from '@nestjs/testing'
import { ContratoController } from '../../infra/controllers/contrato.controller'
import { ContratoServiceImpl } from '../../domain/services/ContratoService'
import { NotFoundException } from '@nestjs/common'
import { Contrato } from '../../mongo/schemas/contrato.schema'
import { ObjectId } from 'mongodb'

describe('ContratoController', () => {
    let controller: ContratoController
    let service: jest.Mocked<ContratoServiceImpl>

    beforeEach(async () => {
        const module: TestingModule = await Test.createTestingModule({
            controllers: [ContratoController],
            providers: [
                {
                    provide: ContratoServiceImpl,
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

        controller = module.get<ContratoController>(ContratoController)
        service = module.get(ContratoServiceImpl)
    })

    describe('findAll', () => {
        it('should return all contracts', async () => {
            const mockContratos: Contrato[] = [
                new Contrato({
                    _id: new ObjectId('61a74f09b63f9e39b964f1f6'),
                    id_cliente: new ObjectId('61a74f09b63f9e39b964f1f7'),
                    id_veiculo: new ObjectId('61a74f09b63f9e39b964f1f8'),
                    data_contrato: new Date('2024-01-01'),
                    valor_contrato: 15000,
                    status_contrato: 'Ativo',
                }),
            ]

            service.findAll.mockResolvedValue(mockContratos)

            const result = await controller.findAll()
            expect(result).toEqual(mockContratos)
            expect(service.findAll).toHaveBeenCalled()
        })
    })

    describe('findById', () => {
        it('should return a single contract by ID', async () => {
            const mockContrato = new Contrato({
                _id: new ObjectId('61a74f09b63f9e39b964f1f6'),
                id_cliente: new ObjectId('61a74f09b63f9e39b964f1f7'),
                id_veiculo: new ObjectId('61a74f09b63f9e39b964f1f8'),
                data_contrato: new Date('2024-01-01'),
                valor_contrato: 15000,
                status_contrato: 'Ativo',
            })

            service.findById.mockResolvedValue(mockContrato)

            const result = await controller.findById('61a74f09b63f9e39b964f1f6')
            expect(result).toEqual(mockContrato)
            expect(service.findById).toHaveBeenCalledWith('61a74f09b63f9e39b964f1f6')
        })

        it('should throw NotFoundException if contract not found', async () => {
            service.findById.mockResolvedValue(null)

            await expect(controller.findById('invalid-id')).rejects.toThrow(NotFoundException)
            expect(service.findById).toHaveBeenCalledWith('invalid-id')
        })
    })

    describe('create', () => {
        it('should create and return a new contract', async () => {
            const createDto = {
                id_cliente: new ObjectId('61a74f09b63f9e39b964f1f7'),
                id_veiculo: new ObjectId('61a74f09b63f9e39b964f1f8'),
                data_contrato: new Date('2024-01-01'),
                valor_contrato: 15000,
                status_contrato: 'Ativo',
            }

            const mockContrato = {
                ...createDto,
                _id: '61a74f09b63f9e39b964f1f6',
            }

            service.create.mockResolvedValue(true)

            const result = await controller.create(new Contrato(createDto))
            expect(result).toEqual(mockContrato)
            expect(service.create).toHaveBeenCalledWith(createDto)
        })
    })

    describe('update', () => {
        it('should update and return the updated contract', async () => {
            const updateDto = {
                status_contrato: 'Inativo',
            }

            const mockContrato = {
                _id: '61a74f09b63f9e39b964f1f6',
                id_cliente: new ObjectId('61a74f09b63f9e39b964f1f7'),
                id_veiculo: new ObjectId('61a74f09b63f9e39b964f1f8'),
                data_contrato: new Date('2024-01-01'),
                valor_contrato: 15000,
                status_contrato: 'Inativo',
            }

            service.update.mockResolvedValue(true)

            const result = await controller.update('61a74f09b63f9e39b964f1f6', updateDto)
            expect(result).toEqual(mockContrato)
            expect(service.update).toHaveBeenCalledWith('61a74f09b63f9e39b964f1f6', updateDto)
        })

        it('should throw NotFoundException if contract to update is not found', async () => {
            service.update.mockResolvedValue(null)

            await expect(controller.update('invalid-id', {})).rejects.toThrow(NotFoundException)
            expect(service.update).toHaveBeenCalledWith('invalid-id', {})
        })
    })

    describe('delete', () => {
        it('should delete a contract and return true', async () => {
            service.delete.mockResolvedValue(true)

            const result = await controller.delete('61a74f09b63f9e39b964f1f6')
            expect(result).toBe(true)
            expect(service.delete).toHaveBeenCalledWith('61a74f09b63f9e39b964f1f6')
        })

        it('should throw NotFoundException if contract to delete is not found', async () => {
            service.delete.mockResolvedValue(false)

            await expect(controller.delete('invalid-id')).rejects.toThrow(NotFoundException)
            expect(service.delete).toHaveBeenCalledWith('invalid-id')
        })
    })
})
