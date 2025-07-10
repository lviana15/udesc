Arquivos:
- personalizacao.sql: script dump para criação do banco 
- personalizacao-tabelas.sql: arquivo sql apenas com tabelas, para melhor visualização
- prisma/schema.prisma: Arquivo com schema do banco (Melhor visualização para relacionamentos)
- triggers-personalizadora.sql: Funções e triggers sql
- Diagrama ER: Diagrama ER do banco

- src/test: pasta com todos testes unitários criados para projeto

Para executar projeto, deve ter instalado:
- Node
- npm (packet manager)

1. Instalar dependencias
```
npm i
```

2. Criar/Alterar arquivo .env para exemplo
DATABASE_URL="postgresql://usuario_banco:senha_usuario@localhost:5432/personalizadora"

3. Criar cliente ORM e executar migrações
```
npx prisma generate
npx prisma migrate dev
```

4. Rodar testes
```
npx jest
```

5. Rodar projeto
```
npm run start:dev
```
