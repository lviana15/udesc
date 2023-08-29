
public class Usuario {
	private String nome;
	private String email;
	private Filme []filmesFavoritos;
	
	public Usuario() {}
	
	public Usuario(String nome, String email, Filme[] filmesFavoritos) {
		this.nome = nome;
		this.email = email;
		this.filmesFavoritos = filmesFavoritos;
	}
	
	public String getNome() {
		return nome;
	}
	
	public void setNome(String nome) {
		this.nome = nome;
	}
	
	public String getEmail() {
		return email;
	}
	
	public void setEmail(String email) {
		this.email = email;
	}
	
	public Filme [] getFavoritos() {
		return filmesFavoritos;
	}
	
	public void setFavoritos(Filme [] favoritos) {
		this.filmesFavoritos = favoritos;
	}
	
	public String toString() {
		String string = "";
		string += "Usuario [Nome: " +nome+ ", Email: " +email+ "]\n";
		string += "Filmes favoritos:\n";
		for(Filme filme: filmesFavoritos) {
            string += "- " +filme+ "\n";
		}
		
		return string;
	}
}
