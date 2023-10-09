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
		apresenta(new Abundantes());
        apresenta(new Fatorial());
        apresenta(new Fibonacci());
        apresenta(new Naturais());
        apresenta(new Primo());
        apresenta(new Perfeitos());
        apresenta(new Quadrados());
	}
	
	public static void apresenta(Gerador g) {
		g.gerar(10);

		System.out.println("Sortea: " + g.sortear());
        System.out.println("Somatorio: " + g.somatorio());
        System.out.println("Media Aritmetica: " + g.mediaAritmetica());
        System.out.println("Media Geometrica: " + g.mediaGeometrica());
        System.out.println("Variancia: " + g.variancia());
        System.out.println("Desvio Padrão: " + g.desvioPadrao());
        System.out.println("Amplitude:" + g.amplitude());
    }
}
