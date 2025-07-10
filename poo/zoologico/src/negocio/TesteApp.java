package negocio;

import dados.Viveiro;

public class TesteApp {
	
	public static void main(String[] args) {
		
		Zoologico zoo = new Zoologico(10);
		
		Viveiro v = new Viveiro(5);
		
		v.setComprimento(100);
		v.setLargura(100);
		v.setNome("Viveiro Teste");
		
		zoo.cadastrarViveiro(v);
		
		Viveiro viveiros[] = zoo.getSoViveiros();
		int quantViveiros = zoo.getQuantViveiros();
		
		for (int i = 0; i < quantViveiros; i++) {
			System.out.println(viveiros[i]);
		}
	
	}
	
		
		

}
