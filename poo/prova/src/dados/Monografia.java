package dados;

public class Monografia extends Item {
	public Monografia (int id, String titulo, String nomeAutor, int ano) {
		super(id, titulo, nomeAutor, ano);
		setTempoEmprestimo(30);
	}
}
