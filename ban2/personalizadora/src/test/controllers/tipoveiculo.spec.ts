import { Test, TestingModule } from '@nestjs/testing'
import { TipoVeiculoController } from '../../infra/controllers/tipoveiculo.controller'
import { TipoVeiculoServiceImpl } from '../../domain/services/TipoVeiculoService'
import { NotFoundException } from '@nestjs/common'
import { TipoVeiculo } from '../../mongo/schemas/tipoveiculo.schema'
import { ObjectId } from 'mongodb'

describe('TipoVeiculoController', () => {
    let controller: TipoVeiculoController
    let service: jest.Mocked<TipoVeiculoServiceImpl>

    beforeEach(async () => {
        const module: TestingModule = await Test.createTestingModule({
            controllers: [TipoVeiculoController],
            providers: [
                {
                    provide: TipoVeiculoServiceImpl,
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

        controller = module.get<TipoVeiculoController>(TipoVeiculoController)
        service = module.get(TipoVeiculoServiceImpl)
    })

    describe('findAll', () => {
        it('should return all vehicle types', async () => {
            const mockTipos: TipoVeiculo[] = [
                new TipoVeiculo({
                    _id: new ObjectId('61a74f09b63f9e39b964f1f6'),
                    id_tipo_veiculo: 1,
                    tipo_veiculo: 'Car',
                    descricao_tipo_veiculo: 'Passenger car',
                }),
            ]

            service.findAll.mockResolvedValue(mockTipos)

            const result = await controller.findAll()
            expect(result).toEqual(mockTipos)
            expect(service.findAll).toHaveBeenCalled()
        })
    })

    describe('findById', () => {
        it('should return a single vehicle type by ID', async () => {
            const mockTipo = new TipoVeiculo({
                _id: new ObjectId('61a74f09b63f9e39b964f1f6'),
                id_tipo_veiculo: 1,
                tipo_veiculo: 'Car',
                descricao_tipo_veiculo: 'Passenger car',
            })

            service.findById.mockResolvedValue(mockTipo)

            const result = await controller.findById('61a74f09b63f9e39b964f1f6')
            expect(result).toEqual(mockTipo)
            expect(service.findById).toHaveBeenCalledWith('61a74f09b63f9e39b964f1f6')
        })

        it('should throw NotFoundException if vehicle type not found', async () => {
            service.findById.mockResolvedValue(null)

            await expect(controller.findById('invalid-id')).rejects.toThrow(NotFoundException)
            expect(service.findById).toHaveBeenCalledWith('invalid-id')
        })
    })

    describe('create', () => {
        it('should create and return a new vehicle type', async () => {
            const createDto = {
                id_tipo_veiculo: 2,
                tipo_veiculo: 'Truck',
                descricao_tipo_veiculo: 'Cargo vehicle',
            }

            const mockTipo = {
                ...createDto,
                _id: '61a74f09b63f9e39b964f1f6',
            }

            service.create.mockResolvedValue(true)

            const result = await controller.create(new TipoVeiculo(createDto))
            expect(result).toEqual(mockTipo)
            expect(service.create).toHaveBeenCalledWith(createDto)
        })
    })

    describe('update', () => {
        it('should update and return the updated vehicle type', async () => {
            const updateDto = {
                descricao_tipo_veiculo: 'Updated description',
            }

            const mockTipo = {
                _id: '61a74f09b63f9e39b964f1f6',
                id_tipo_veiculo: 1,
                tipo_veiculo: 'Car',
                descricao_tipo_veiculo: 'Updated description',
            }

            service.update.mockResolvedValue(true)

            const result = await controller.update('61a74f09b63f9e39b964f1f6', updateDto)
            expect(result).toEqual(mockTipo)
            expect(service.update).toHaveBeenCalledWith('61a74f09b63f9e39b964f1f6', updateDto)
        })

        it('should throw NotFoundException if vehicle type to update is not found', async () => {
            service.update.mockResolvedValue(null)

            await expect(controller.update('invalid-id', {})).rejects.toThrow(NotFoundException)
            expect(service.update).toHaveBeenCalledWith('invalid-id', {})
        })
    })

    describe('delete', () => {
        it('should delete a vehicle type and return true', async () => {
            service.delete.mockResolvedValue(true)

            const result = await controller.delete('61a74f09b63f9e39b964f1f6')
            expect(result).toBe(true)
            expect(service.delete).toHaveBeenCalledWith('61a74f09b63f9e39b964f1f6')
        })

        it('should throw NotFoundException if vehicle type to delete is not found', async () => {
            service.delete.mockResolvedValue(false)

            await expect(controller.delete('invalid-id')).rejects.toThrow(NotFoundException)
            expect(service.delete).toHaveBeenCalledWith('invalid-id')
        })
    })
})
