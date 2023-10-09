package dados;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;

public abstract class Gerador implements ISequencia {
	protected List<Integer> sequencia;
	
	Gerador() {
		sequencia = new ArrayList<Integer>();
	}
	
	public abstract void gerar(int quantidade);
	
	public int sortear() {
		int index = new Random().nextInt(sequencia.size());
		return 	sequencia.get(index);
	}
	
	public long somatorio() {
		int somatorio = 0;
		for (int numero : sequencia) {
			somatorio += numero;
		}
		
		return somatorio;
	}
	
	public long produtorio() {
		int produtorio = 1;
		for (int numero : sequencia) {
			produtorio *= numero;
		}
		
		return produtorio;
	}
	
	public double mediaAritmetica() {
		return somatorio() / (double) sequencia.size();
	}
	
	public double mediaGeometrica() {
        return Math.pow(produtorio(), 1.0 / (double) (sequencia.size()));
	}
	
	public double variancia() {
		double media = mediaAritmetica();
		double soma = 0;
		
		for (int num : sequencia) {
			soma += Math.pow(num - media, 2);
		}
	
		return soma / (double) sequencia.size() - 1;
	}
	
	public double desvioPadrao() {
		
		return Math.sqrt(variancia());
	}
	
	public int amplitude() {
		return Collections.max(sequencia) - Collections.min(sequencia);
	}
	
	public List<Integer> getSequencia() {
		return sequencia;
	}
}

































