
public class Abundantes extends Gerador {
	public void gerar(int quantidade) {
		int count = 0;
		int teste = 2;
		
		while (count < quantidade ) {
			int soma = 0;
			
			for (int i = 1; i <= teste/2; i++) {
				if (teste % i == 0) {
					soma += i;
				}
			}
			
			if(teste < soma) {
				sequencia.add(teste);
				count++;
			}
			
			teste++;
		}
	}
}
