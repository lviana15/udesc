import { HttpService } from "@nestjs/axios";
import { Command, CommandRunner, Option } from "nest-commander";

@Command({ name: 'crud', description: 'CRUD operations' })
export class CommandService extends CommandRunner {
    constructor(private readonly httpService: HttpService) {
        super()
    }

    async run(passedParams: string[], options?: Record<string, any>): Promise<void> {
        const [command, entity] = passedParams
        const id = options.id
        const data = options.data ? JSON.parse(options.data) : null

        switch (command) {
            case 'create':
                await this.create(entity, data)
                break
            case 'findAll':
                await this.findAll(entity)
                break
            case 'findById':
                await this.findById(entity, id)
                break
            case 'update':
                await this.update(entity, id, data)
                break
            case 'delete':
                await this.delete(entity, id)
                break
            default:
                console.error('Invalid command')
        }

        throw new Error('Method not implemented.')
    }

    private async create(entity: string, data: Record<string, any>): Promise<void> {
        const response = await this.httpService.post(`http://localhost:3000/${entity}`, data).toPromise()
        console.log(response.data)
    }

    private async findById(entity: string, id: number): Promise<void> {
        const response = await this.httpService.post(`http://localhost:3000/${entity}`, id).toPromise()
        console.log(response.data)
    }

    private async findAll(entity: string): Promise<void> {
        const response = await this.httpService.get(`http://localhost:3000/${entity}`).toPromise()
        console.log(response.data)
    }

    private async update(entity: string, id: number, data: Record<string, any>): Promise<void> {
        const response = await this.httpService.put(`http://localhost:3000/${entity}/${id}`, data).toPromise()
        console.log(response.data)
    }

    private async delete(entity: string, id: number) {
        const response = await this.httpService.delete(`http://localhost:3000/${entity}/${id}`).toPromise()
        console.log(response)
    }

    @Option({
        flags: '-i, --id <id>',
        description: 'Entity ID'
    })
    parseId(value: string): string {
        return value
    }

    @Option({
        flags: '-d, --data <data>',
        description: 'Entity data'
    })
    parseData(value: string): string {
        return value
    }
}