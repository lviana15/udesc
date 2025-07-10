import { Test, TestingModule } from '@nestjs/testing'
import { FuncionarioController } from '../../infra/controllers/funcionario.controller'
import { FuncionarioServiceImpl } from '../../domain/services/FuncionarioService'
import { NotFoundException } from '@nestjs/common'
import { Funcionario } from '../../mongo/schemas/funcionario.schema'
import { ObjectId } from 'mongodb'

describe('FuncionarioController', () => {
  let controller: FuncionarioController
  let service: jest.Mocked<FuncionarioServiceImpl>

  beforeEach(async () => {
    const module: TestingModule = await Test.createTestingModule({
      controllers: [FuncionarioController],
      providers: [
        {
          provide: FuncionarioServiceImpl,
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

    controller = module.get<FuncionarioController>(FuncionarioController)
    service = module.get(FuncionarioServiceImpl)
  })

  describe('findAll', () => {
    it('should return all employees', async () => {
      const mockFuncionarios: Funcionario[] = [
        new Funcionario({
          _id: new ObjectId('61a74f09b63f9e39b964f1f6'),
          nome_funcionario: 'John Doe',
          cpf_funcionario: '12345678900',
          cargo_funcionario: 'Manager',
          id_departamento: 'dept1',
          id_responsavel: 'resp1',
        }),
      ]

      service.findAll.mockResolvedValue(mockFuncionarios)

      const result = await controller.findAll()
      expect(result).toEqual(mockFuncionarios)
      expect(service.findAll).toHaveBeenCalled()
    })
  })

  describe('findById', () => {
    it('should return a single employee by ID', async () => {
      const mockFuncionario = new Funcionario({
        _id: new ObjectId('61a74f09b63f9e39b964f1f6'),
        nome_funcionario: 'John Doe',
        cpf_funcionario: '12345678900',
        cargo_funcionario: 'Manager',
        id_departamento: 'dept1',
        id_responsavel: 'resp1',
      })

      service.findById.mockResolvedValue(mockFuncionario)

      const result = await controller.findById('61a74f09b63f9e39b964f1f6')
      expect(result).toEqual(mockFuncionario)
      expect(service.findById).toHaveBeenCalledWith('61a74f09b63f9e39b964f1f6')
    })

    it('should throw NotFoundException if employee not found', async () => {
      service.findById.mockResolvedValue(null)

      await expect(controller.findById('invalid-id')).rejects.toThrow(NotFoundException)
      expect(service.findById).toHaveBeenCalledWith('invalid-id')
    })
  })

  describe('create', () => {
    it('should create and return a new employee', async () => {
      const createDto = {
        nome_funcionario: 'John Doe',
        cpf_funcionario: '12345678900',
        cargo_funcionario: 'Manager',
        id_departamento: 'dept1',
        id_responsavel: 'resp1',
      }

      const mockFuncionario = {
        ...createDto,
        _id: new ObjectId('61a74f09b63f9e39b964f1f6'),
      }

      service.create.mockResolvedValue(true)

      const result = await controller.create(new Funcionario(createDto))
      expect(result).toEqual(mockFuncionario)
      expect(service.create).toHaveBeenCalledWith(createDto)
    })
  })

  describe('update', () => {
    it('should update and return the updated employee', async () => {
      const updateDto = {
        cargo_funcionario: 'Senior Manager',
      }

      const mockFuncionario = {
        _id: new ObjectId('61a74f09b63f9e39b964f1f6'),
        nome_funcionario: 'John Doe',
        cpf_funcionario: '12345678900',
        cargo_funcionario: 'Senior Manager',
        id_departamento: 'dept1',
        id_responsavel: 'resp1',
      }

      service.update.mockResolvedValue(true)

      const result = await controller.update('61a74f09b63f9e39b964f1f6', updateDto)
      expect(result).toEqual(mockFuncionario)
      expect(service.update).toHaveBeenCalledWith('61a74f09b63f9e39b964f1f6', updateDto)
    })

    it('should throw NotFoundException if employee to update is not found', async () => {
      service.update.mockResolvedValue(null)

      await expect(controller.update('invalid-id', {})).rejects.toThrow(NotFoundException)
      expect(service.update).toHaveBeenCalledWith('invalid-id', {})
    })
  })

  describe('delete', () => {
    it('should delete an employee and return true', async () => {
      service.delete.mockResolvedValue(true)

      const result = await controller.delete('61a74f09b63f9e39b964f1f6')
      expect(result).toBe(true)
      expect(service.delete).toHaveBeenCalledWith('61a74f09b63f9e39b964f1f6')
    })

    it('should throw NotFoundException if employee to delete is not found', async () => {
      service.delete.mockResolvedValue(false)

      await expect(controller.delete('invalid-id')).rejects.toThrow(NotFoundException)
      expect(service.delete).toHaveBeenCalledWith('invalid-id')
    })
  })
})
