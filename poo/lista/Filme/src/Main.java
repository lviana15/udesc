
public class Main {
	public static void main(String[] args) {
		Ator ator = new Ator();
		ator.setNome("Tom");
		ator.setIdade(24);
		ator.setNascimento("27/10/98");
		
		Ator atriz = new Ator("Olivia", 23, "18/05/00");
		
		Filme filmeA = new Filme();
		filmeA.setNome("Spider Man");
		filmeA.setAno(2023);
		filmeA.setEstrela(ator);
		
		Filme filmeB = new Filme("Silent Night", 2022, atriz);
		
		Filme[] listaFilmes = new Filme[2];
		listaFilmes[0] = filmeA;
		listaFilmes[1] = filmeB;
		
		Serie serieA = new Serie();
		serieA.setNome("Breaking Bad");
		serieA.setTemporadas(5);
		serieA.setEpisodios(62);
		
		Serie serieB = new Serie("Ragnarok", 3, 18);
		
		Serie[] listaSeries = new Serie[2];
		listaSeries[0] = serieA;
		listaSeries[1] = serieB;
		
		Usuario usuarioA = new Usuario();
		
		usuarioA.setNome("Lucas");
		usuarioA.setEmail("lucas@gmail.com");
		usuarioA.setFavoritos(listaFilmes);
		
		Usuario usuarioB = new Usuario("André", "andre@gmail.com", listaFilmes);
		
		Categoria categoriaA = new Categoria();
		
		categoriaA.setNome("Ação");
		categoriaA.setFilmes(listaFilmes);
		categoriaA.setSeries(listaSeries);
		
		Categoria categoriaB = new Categoria("Drama", listaFilmes, listaSeries);
		
		System.out.println(ator);
		System.out.println(atriz);
		
		System.out.println(filmeA);
		System.out.println(filmeB);
		
		System.out.println(serieA);
		System.out.println(serieB);
		
		System.out.println(categoriaA);
		System.out.println(categoriaB);
		
		System.out.println(usuarioA);
		System.out.println(usuarioB);
	}
}
