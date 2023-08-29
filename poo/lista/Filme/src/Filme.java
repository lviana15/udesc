
public class Filme {
	private String nome;
	private int ano;
	private Ator estrela;
	
	public Filme() {
	}
	
	public Filme(String nome, int ano, Ator estrela) {
		this.nome = nome;
		this.ano = ano;
		this.estrela = estrela;
	}
	
	public String getNome() {
		return nome;
	}
	public void setNome(String nome) {
		this.nome = nome;
	}
	public int getAno() {
		return ano;
	}
	public void setAno(int ano) {
		this.ano = ano;
	}
	public Ator getEstrela() {
		return estrela;
	}
	public void setEstrela(Ator estrela) {
		this.estrela = estrela;
	}
	
	public String toString() {
		return "Filme [Nome: " +nome+ ", Ano: " +ano+ ", Estrela: " +estrela+" ]";
	}
}
