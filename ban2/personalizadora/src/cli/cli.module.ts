import { Module } from '@nestjs/common'
import { CommandRunnerModule } from 'nest-commander';
import { CommandService } from './commands.service';
import { HttpModule } from '@nestjs/axios';

@Module({
    imports: [
        CommandRunnerModule,
        HttpModule
    ],
    providers: [CommandService],
})

export class CliModule { }