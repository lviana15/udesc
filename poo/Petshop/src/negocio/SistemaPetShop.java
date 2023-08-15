package negocio;

import java.util.Scanner;

import dados.Animal;
import dados.Dono;
import dados.Endereco;
import dados.Veterinario;

public class SistemaPetShop {
	private Veterinario veterinarios[];
	private int quantidadeVeterinarios;

	public SistemaPetShop(int tamVeterinario) {
		veterinarios = new Veterinario[tamVeterinario];
	}
	
	public void cadastrarVeterinario() {
		Scanner scan = new Scanner(System.in);
		Veterinario veterinario = new Veterinario(5);
		
		System.out.println("Digite nome do veterinario: ");
		veterinario.setNome(scan.nextLine());
		System.out.println("Salario:");
		veterinario.setSalario(Float.parseFloat(scan.nextLine()));
		
		veterinarios[quantidadeVeterinarios] = veterinario;
		quantidadeVeterinarios++;
	}

	public void mostrarVeterinarios() {
		for (int i = 0; i < quantidadeVeterinarios; i++) {
			System.out.println("Id: " + i + "- Nome: " + veterinarios[i].getNome());
		}
	}

	public void cadastrarEnderecoVeterinario() {
		Scanner scan = new Scanner(System.in);

		mostrarVeterinarios();

		System.out.println("Id do Veterinario com Endereço a ser cadastrado:");
		int idCadastro = Integer.parseInt(scan.nextLine());

		Endereco endereco = new Endereco();
		System.out.println("Rua:");
		endereco.setRua(scan.nextLine());

		System.out.println("Número:");
		endereco.setNumero(Integer.parseInt(scan.nextLine()));

		System.out.println("Bairro:");
		endereco.setBairro(scan.nextLine());

		System.out.println("Cidade:");
		endereco.setCidade(scan.nextLine());

		System.out.println("Estado:");
		endereco.setEstado(scan.nextLine());

		System.out.println("CEP:");
		endereco.setCep(scan.nextLine());

		scan.close();
		veterinarios[idCadastro].setEndereco(endereco);
	}

	public void cadastrarAnimal() {
		Scanner scan = new Scanner(System.in);
		mostrarVeterinarios();

		System.out.println("ID do Veterinario com Animal a ser cadastrado:");
		int idCadastro = Integer.parseInt(scan.nextLine());

		Animal animal = new Animal();

		System.out.println("Nome:");
		animal.setNome(scan.nextLine());

		System.out.println("Especie:");
		animal.setEspecie(scan.nextLine());

		System.out.println("Descrição");
		animal.setDescricao(scan.nextLine());

		scan.close();
		int indexAnimal = veterinarios[idCadastro].getQuantidadeAnimais();
		Animal[] animais = veterinarios[idCadastro].getAnimais();
		animais[indexAnimal] = animal;
	}

	public Animal[] mostrarAnimais() {
		Scanner scan = new Scanner(System.in);
		mostrarVeterinarios();

		System.out.println("ID do Veterinario a mostrar Animais:");
		scan.close();
		int idVet = Integer.parseInt(scan.nextLine());
		Animal[] animais = veterinarios[idVet].getAnimais();

		for (int i = 0; i < animais.length; i++) {
			System.out.println("Id: " + i + "- Nome: " + animais[i].getNome());
		}

		return animais;
	}

	public void cadastrarDono() {
		Animal[] animais = mostrarAnimais();
		Scanner scan = new Scanner(System.in);

		System.out.println("ID do Animal com Dono a ser cadastrado:");
		int idAni = Integer.parseInt(scan.nextLine());
		Dono dono = new Dono();

		System.out.println("Nome dono:");
		dono.setNome(scan.nextLine());

		System.out.println("CPF dono:");
		dono.setCpf(scan.nextLine());

		animais[idAni].setDono(dono);

		scan.close();
	}

	public void cadastrarEnderecoDono() {
		Animal[] animais = mostrarAnimais();
		Scanner scan = new Scanner(System.in);

		System.out.println("ID do Animal com Endereço do Dono a ser cadastrado:");
		int idAni = Integer.parseInt(scan.nextLine());

		Dono dono = animais[idAni].getDono();
		System.out.println(dono.getNome() + " - " + dono.getCpf());

		Endereco endereco = new Endereco();
		System.out.println("Rua:");
		endereco.setRua(scan.nextLine());

		System.out.println("Número:");
		endereco.setNumero(Integer.parseInt(scan.nextLine()));

		System.out.println("Bairro:");
		endereco.setBairro(scan.nextLine());

		System.out.println("Cidade:");
		endereco.setCidade(scan.nextLine());

		System.out.println("Estado:");
		endereco.setEstado(scan.nextLine());

		System.out.println("CEP:");
		endereco.setCep(scan.nextLine());

		dono.setEndereco(endereco);
	}
}
