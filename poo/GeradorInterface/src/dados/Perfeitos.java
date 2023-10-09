package dados;

public class Perfeitos extends Gerador{
	public void gerar(int quantidade) {
		int count = 0;
		int i = 0;
		while (count < quantidade) {
			if (perfeito(i)) {
				sequencia.add(i);
				count++;
			}
			
			i++;
		}
	}
	
	boolean perfeito(int n) {
		int divisores = 0;
		
		for(int i = 1; i <= n/2; i++) {
			if (n % i == 0) {
				divisores += i;
			}
		}
		
		if (n == divisores) return true;
		
		return false;
	}
}
