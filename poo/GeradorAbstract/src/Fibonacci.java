
public class Fibonacci extends Gerador {
	public void gerar(int quantidade) {
		for(int i = 0; i < quantidade; i++) {
			sequencia.add(fibo(i));
		}	
	}
	
	private int fibo(int n) {
        if (n < 2) {
            return n;
        } else {
            return fibo(n - 1) + fibo(n - 2);
        }
    }
}
