package dados;

public class Livro extends Item {
	public Livro(int id, String titulo, String nomeAutor, int ano) {
		super(id, titulo, nomeAutor, ano);
		setTempoEmprestimo(15);
	}
}
