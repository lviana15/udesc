
public class Naturais extends Gerador {
	public void gerar(int quantidade) {
		int i = 0;
		
		while(i < quantidade) {
			sequencia.add(i);
			i++;
		}		
	}
}
