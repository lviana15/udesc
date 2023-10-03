package dados;

public class Usuario {
	private String login;
	private String senha;
	private int limiteEmpLivro = 3;
	private int limiteEmpMono = 3;
	private int tempoPenalidade;
	
	public Usuario(String login, String senha) {
		this.login = login;
		this.senha = senha;
	}
	
	public boolean podeEmprLivro() {
		return limiteEmpLivro > 0;
	}
	
	public boolean podeEmprMono() {
		return limiteEmpMono > 0;
	}
	
	public String getLogin() {
		return login;
	}
	public void setLogin(String login) {
		this.login = login;
	}
	public String getSenha() {
		return senha;
	}
	public void setSenha(String senha) {
		this.senha = senha;
	}
	public int getLimiteEmpLivro() {
		return limiteEmpLivro;
	}
	public void setLimiteEmpLivro(int limiteEmpLivro) {
		this.limiteEmpLivro = limiteEmpLivro;
	}
	public int getLimiteEmpMono() {
		return limiteEmpMono;
	}
	public void setLimiteEmpMono(int limiteEmpMono) {
		this.limiteEmpMono = limiteEmpMono;
	}
	public int getTempoPenalidade() {
		return tempoPenalidade;
	}
	public void setTempoPenalidade(int tempoPenalidade) {
		this.tempoPenalidade = tempoPenalidade;
	}
}
