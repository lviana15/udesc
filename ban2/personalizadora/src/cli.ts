import { NestFactory } from "@nestjs/core";
import { CliModule } from "./cli/cli.module";
import { CommandRunner } from "nest-commander";

async function bootstrap() {
  const app = await NestFactory.createApplicationContext(CliModule)

  const commandRunner = app.get(CommandRunner)
  await commandRunner.run(process.argv.slice(2))

  await app.close()
}

bootstrap()