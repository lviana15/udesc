
public class Main {
	public static void main(String[] args) {
		Grupo g = new Grupo();
		
		Pessoa p1 = new Pessoa();
		p1.setNome("Joao");
		p1.setAltura(1.72f);
		p1.setIdade(18);
		p1.setMassa(68.0f);
		
		Pessoa p2 = new Pessoa();
		p2.setNome("Maria");
		p2.setAltura(1.56f);
		p2.setIdade(19);
		p2.setMassa(53.6f);
		
		Pessoa p3 = new Pessoa();
		p3.setNome("Gabriel");
		p3.setAltura(1.85f);
		p3.setIdade(21);
		p3.setMassa(81.0f);
		
		g.setPessoa(p1);
		g.setPessoa(p2);
		g.setPessoa(p3);
		
		g.ordena();
		
		for(int i = 0; i < 3; i++) {
			System.out.println("Nome: " +g.getPessoas()[i].getNome());
			System.out.println("Altura: " +g.getPessoas()[i].getAltura());
			System.out.println("Idade: " +g.getPessoas()[i].getIdade());
			System.out.println("Massa: " +g.getPessoas()[i].getMassa());
			System.out.println("IMC: " +g.getPessoas()[i].calculaImc() + "\n");
		}
	}
}
