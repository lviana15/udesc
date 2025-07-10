package dados;

import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;

public class CalculadoraEstatistica implements ISequencia {
	private static CalculadoraEstatistica instance = null;
	private List<Integer> sequencia = new LinkedList<Integer>();

	private CalculadoraEstatistica() {
	}
	
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


	public void adicionarValor(int valor) {
		this.sequencia.add(valor);
	}

	public List<Integer> getValores() {
		return sequencia;
	}

	public void setValores(List<Integer> valores) {
		this.sequencia = valores;
	}

	public void limparValores() {
		this.sequencia.clear();
	}

	public static CalculadoraEstatistica getInstance() {
		if (instance == null) {
			instance = new CalculadoraEstatistica();
		}
		return instance;
	}
}
