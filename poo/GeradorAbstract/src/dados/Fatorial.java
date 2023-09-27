package dados;

public class Fatorial extends Gerador {
	public void gerar(int quantidade) {
		for (int i = 1; i <= quantidade; i++) {
			int count = i;
			int fat = 1;
			while(count > 0) {
				fat *= count;
				
				count--;
			}
			
			sequencia.add(fat);
		}
	}
}
