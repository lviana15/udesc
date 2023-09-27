package dados;

public class Quadrados extends Gerador {
	public void gerar(int quantidade) {
		int count = 0;
		int i = 2;
		
		while(count < quantidade) {
			sequencia.add(i * i);
			i++;
			count++;
		}
	}
}
