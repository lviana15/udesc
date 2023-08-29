
public class Categoria {
	private String nome;
	private Filme []filmes;
	private Serie []series;
	
	public Categoria() {}
	
	public Categoria(String nome, Filme[] filmes, Serie[] series) {
		this.nome = nome;
		this.filmes = filmes;
		this.series = series;
	}
	
	public String getNome() {
		return nome;
	}
	
	public void setNome(String nome) {
		this.nome = nome;
	}
	
	public Filme [] getFilmes() {
		return filmes;
	}
	
	public void setFilmes(Filme [] filmes) {
		this.filmes = filmes;
	}
	
	public Serie [] getSeries() {
		return series;
	}
	
	public void setSeries(Serie [] series) {
		this.series = series;
	}
	
	public String toString() {
		String string = "";
        string += "Categoria [Nome: " +nome+ "]\nFilmes: \n";
        for (Filme filme : filmes) {
            string += "- " +filme+ "\n";
        }
        string  += "Series: \n";
        for (Serie serie : series) {
        	string += "- " +serie+ "\n";
        }
        
        return string;
       }
}
