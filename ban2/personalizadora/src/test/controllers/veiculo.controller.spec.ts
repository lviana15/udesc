import { Test, TestingModule } from '@nestjs/testing'
import { VeiculoController } from '../../infra/controllers/veiculo.controller'
import { VeiculoServiceImpl } from '../../domain/services/VeiculoService'
import { NotFoundException } from '@nestjs/common'
import { Veiculo } from '../../mongo/schemas/veiculo.schema'
import { ObjectId } from 'mongodb'

describe('VeiculoController', () => {
    let controller: VeiculoController
    let service: jest.Mocked<VeiculoServiceImpl>

    beforeEach(async () => {
        const module: TestingModule = await Test.createTestingModule({
            controllers: [VeiculoController],
            providers: [
                {
                    provide: VeiculoServiceImpl,
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

        controller = module.get<VeiculoController>(VeiculoController)
        service = module.get(VeiculoServiceImpl)
    })

    describe('findAll', () => {
        it('should return all vehicles', async () => {
            const mockVeiculos: Veiculo[] = [
                new Veiculo({
                    _id: new ObjectId('61a74f09b63f9e39b964f1f7'),
                    id_veiculo: new ObjectId('61a74f09b63f9e39b964f1f8'),
                    modelo_veiculo: 'Sedan',
                    ano_veiculo: 2022,
                    id_cliente: 1,
                    id_tipo: new ObjectId('61a74f09b63f9e39b964f1f9'),
                }),
            ]

            service.findAll.mockResolvedValue(mockVeiculos)

            const result = await controller.findAll()
            expect(result).toEqual(mockVeiculos)
            expect(service.findAll).toHaveBeenCalled()
        })
    })

    describe('findById', () => {
        it('should return a single vehicle by ID', async () => {
            const mockVeiculo = new Veiculo({
                _id: new ObjectId('61a74f09b63f9e39b964f1f7'),
                id_veiculo: new ObjectId('61a74f09b63f9e39b964f1f8'),
                modelo_veiculo: 'Sedan',
                ano_veiculo: 2022,
                id_cliente: 1,
                id_tipo: new ObjectId('61a74f09b63f9e39b964f1f9'),
            })

            service.findById.mockResolvedValue(mockVeiculo)

            const result = await controller.findById('61a74f09b63f9e39b964f1f7')
            expect(result).toEqual(mockVeiculo)
            expect(service.findById).toHaveBeenCalledWith('61a74f09b63f9e39b964f1f7')
        })

        it('should throw NotFoundException if vehicle not found', async () => {
            service.findById.mockResolvedValue(null)

            await expect(controller.findById('invalid-id')).rejects.toThrow(NotFoundException)
            expect(service.findById).toHaveBeenCalledWith('invalid-id')
        })
    })

    describe('create', () => {
        it('should create and return a new vehicle', async () => {
            const createDto = {
                id_veiculo: new ObjectId('61a74f09b63f9e39b964f1f8'),
                modelo_veiculo: 'SUV',
                ano_veiculo: 2023,
                id_cliente: 2,
                id_tipo: new ObjectId('61a74f09b63f9e39b964f1fa'),
            }

            const mockVeiculo = {
                ...createDto,
                _id: new ObjectId('61a74f09b63f9e39b964f1f7'),
            }

            service.create.mockResolvedValue(true)

            const result = await controller.create(new Veiculo(createDto))
            expect(result).toEqual(mockVeiculo)
            expect(service.create).toHaveBeenCalledWith(createDto)
        })
    })

    describe('update', () => {
        it('should update and return the updated vehicle', async () => {
            const updateDto = {
                modelo_veiculo: 'Updated Model',
            }

            const mockVeiculo = {
                _id: new ObjectId('61a74f09b63f9e39b964f1f7'),
                id_veiculo: new ObjectId('61a74f09b63f9e39b964f1f8'),
                modelo_veiculo: 'Updated Model',
                ano_veiculo: 2022,
                id_cliente: 1,
                id_tipo: new ObjectId('61a74f09b63f9e39b964f1f9'),
            }

            service.update.mockResolvedValue(true)

            const result = await controller.update('61a74f09b63f9e39b964f1f7', updateDto)
            expect(result).toEqual(mockVeiculo)
            expect(service.update).toHaveBeenCalledWith('61a74f09b63f9e39b964f1f7', updateDto)
        })

        it('should throw NotFoundException if vehicle to update is not found', async () => {
            service.update.mockResolvedValue(null)

            await expect(controller.update('invalid-id', {})).rejects.toThrow(NotFoundException)
            expect(service.update).toHaveBeenCalledWith('invalid-id', {})
        })
    })

    describe('delete', () => {
        it('should delete a vehicle and return true', async () => {
            service.delete.mockResolvedValue(true)

            const result = await controller.delete('61a74f09b63f9e39b964f1f7')
            expect(result).toBe(true)
            expect(service.delete).toHaveBeenCalledWith('61a74f09b63f9e39b964f1f7')
        })

        it('should throw NotFoundException if vehicle to delete is not found', async () => {
            service.delete.mockResolvedValue(false)

            await expect(controller.delete('invalid-id')).rejects.toThrow(NotFoundException)
            expect(service.delete).toHaveBeenCalledWith('invalid-id')
        })
    })
})
