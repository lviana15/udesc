import dados.Abundantes;
import dados.Fatorial;
import dados.Fibonacci;
import dados.Gerador;
import dados.Naturais;
import dados.Perfeitos;
import dados.Primo;
import dados.Quadrados;

public class Principal {
	public static void main(String[] args) {
		Gerador naturais = new Naturais();
		naturais.gerar(5);
		System.out.println("Naturais: " +naturais.getSequencia());
		
		Gerador abundantes = new Abundantes();
		abundantes.gerar(5);
		System.out.println("Abundantes: " + abundantes.getSequencia());

		Gerador fibonacci = new Fibonacci();
		fibonacci.gerar(5);
		System.out.println("Fibonacci: " +fibonacci.getSequencia());
		
		Gerador fatorial = new Fatorial();
		fatorial.gerar(5);
		System.out.println("Fatorial: " +fatorial.getSequencia());
		
		Gerador primo = new Primo();
		primo.gerar(5);
		System.out.println("Primo: " +primo.getSequencia());
		
		Gerador quadrados = new Quadrados();
		quadrados.gerar(5);
		System.out.println("Quadrados: " +quadrados.getSequencia());
		
		Gerador perfeitos = new Perfeitos();
		perfeitos.gerar(5);
		System.out.println("Perfeitos: " +perfeitos.getSequencia());
	}
}
