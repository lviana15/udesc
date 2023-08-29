
public class Serie {
	private String nome;
	private int temporadas;
	private int episodios;
	
	public Serie() {}
	
	public Serie(String nome, int temporadas, int episodios) {
		this.nome = nome;
		this.temporadas = temporadas;
		this.episodios = episodios;
	}
	
	public String getNome() {
		return nome;
	}
	public void setNome(String nome) {
		this.nome = nome;
	}
	public int getTemporadas() {
		return temporadas;
	}
	public void setTemporadas(int temporadas) {
		this.temporadas = temporadas;
	}
	public int getEpisodios() {
		return episodios;
	}
	public void setEpisodios(int episodios) {
		this.episodios = episodios;
	}
	
	public String toString() {
        return "Serie [Nome: " + nome + ", Temporadas: " + temporadas + ", Episodios: " + episodios + "]";
    }
}
