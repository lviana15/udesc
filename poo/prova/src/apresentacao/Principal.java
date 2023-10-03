package apresentacao;

import java.util.Scanner;

import dados.Item;
import dados.Usuario;
import negocio.Biblioteca;

public class Principal {
	private Biblioteca biblioteca = new Biblioteca();
	
	public static void main(String[] args) {
		
	}
	
	public void menu() {
		System.out.println("Selecione opção: ");
		System.out.println("1 - Adicionar usuario");
		System.out.println("2 - Adicionar item");
		System.out.println("3 - Mostrar itens");
		System.out.println("4 - Mostrar emprestimos por itens");
		System.out.println("5 - Mostrar emprestimos por usuarios");
		System.out.println("6 - Emprestar item");
		System.out.println("7 - Devolver item");
		System.out.println("8 - Renovar item");
		System.out.println("9 - Verificar atraso");
	}
	
	public void adicionarUsuario() {
		Scanner sc = new Scanner(System.in);
		System.out.println("Digite login do usuario: ");
		String login = sc.nextLine();
		
		System.out.println("Digite senha do usuario: ");
		String senha = sc.nextLine();
		sc.close();
		
		Usuario usuario = new Usuario(login, senha);
		
		biblioteca.addUsuario(usuario);
	}
	
	public void adicionarItem() {
		Scanner sc = new Scanner(System.in);
		System.out.println("Digite titulo do item: ");
		String titulo = sc.nextLine();
		
		System.out.println("Digite autor do item: ");
		String autor = sc.nextLine();
		
		System.out.println("Digite ano do item");
		int ano = Integer.parseInt(sc.nextLine());
		sc.close();
		
		int id = biblioteca.getItens().size();
		Item item = new Item(id, titulo, autor, ano);
		
		biblioteca.addItem(item);
	}
}
