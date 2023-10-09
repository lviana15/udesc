package dados;

public class Primo extends Gerador {
	public void gerar(int quantidade) {
		int count = 0;
		int i = 0;
		while (count < quantidade) {
			if (primo(i)) {
				sequencia.add(i);
				count++;
			}
			
			i++;
		}
	}
	
	boolean primo(int n) {
		if (n <= 1) return false;
		
		for (int i = 2; i <= n/2; i++) {
			if (n % i == 0) {
				return false;
			}
		}
		
		return true;
	}
}
