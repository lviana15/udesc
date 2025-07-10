CREATE TABLE tipo_animal(
	id SERIAL PRIMARY KEY,
	tipo VARCHAR(20)
);

CREATE TABLE animais(
	id SERIAL PRIMARY KEY,
	nome VARCHAR(50),
	idade INT,
	descricao VARCHAR(50),
	tipo_animal INT REFERENCES tipo_animal(id),
	id_dono INT REFERENCES pessoas(id)
);

CREATE TABLE endereco (
	id SERIAL PRIMARY KEY,
	rua VARCHAR(100),
	numero INT,
	cep CHAR(8),
	cidade VARCHAR(50),
	estado VARCHAR(50),
	pais VARCHAR(50)
);

CREATE TABLE pessoas(
	id SERIAL PRIMARY KEY,
	nome VARCHAR(50),
	cpf CHAR(11) UNIQUE,
	id_endereco INT references endereco(id)
);
