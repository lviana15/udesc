package apresentacao;

import java.util.Scanner;

import negocio.SistemaPetShop;

public class Main {

	public static void main(String args[]) {
		SistemaPetShop sistema = new SistemaPetShop(10);
		Scanner scan = new Scanner(System.in);
		int opc = -1;

		while (opc != 0) {
			System.out.println("Escolha opção:");
			System.out.println("1 - Cadastro Veterinário");
			System.out.println("2 - Cadastro Animal");
			System.out.println("3 - Mostrar Veterinários");
			System.out.println("4 - Mostrar animais de um veterinário");
			System.out.println("0 - Sair");
			opc = Integer.parseInt(scan.nextLine());

			switch (opc) {
			case 1:
				sistema.cadastrarVeterinario();
				break;
			case 2:
				sistema.cadastrarAnimal();
				break;
			case 3:
				sistema.mostrarVeterinarios();
				break;
			case 4:
				sistema.mostrarAnimais();
				break;
			case 5:
				sistema.cadastrarDono();
				break;
			default:
				System.out.println("Opção Inválida");
			}
		}

		scan.close();
	}
}
