package dados;

public class Item {
	private int id;
	private String titulo;
	private String nomeAutor;
	private int ano;
	private boolean emprestado;
	private int tempoEmprestimo;
	
	public Item(int id, String titulo, String nomeAutor, int ano) {
		this.id = id;
		this.titulo = titulo;
		this.nomeAutor = nomeAutor;
		this.ano = ano;
		this.emprestado = false;
	}
	
	public void emprestar() {
		setEmprestado(true);
	}
	
	public void devolver() {
		setEmprestado(false);
	}
	
	public boolean estaEmprestado() {
		return emprestado;
	}
	
	public int getId() {
		return id;
	}
	public void setId(int id) {
		this.id = id;
	}
	public String getTitulo() {
		return titulo;
	}
	public void setTitulo(String titulo) {
		this.titulo = titulo;
	}
	public String getNomeAutor() {
		return nomeAutor;
	}
	public void setNomeAutor(String nomeAutor) {
		this.nomeAutor = nomeAutor;
	}
	public int getAno() {
		return ano;
	}
	public void setAno(int ano) {
		this.ano = ano;
	}
	public boolean isEmprestado() {
		return emprestado;
	}
	public void setEmprestado(boolean emprestado) {
		this.emprestado = emprestado;
	}
	public int getTempoEmprestimo() {
		return tempoEmprestimo;
	}
	public void setTempoEmprestimo(int tempoEmprestimo) {
		this.tempoEmprestimo = tempoEmprestimo;
	}
}
