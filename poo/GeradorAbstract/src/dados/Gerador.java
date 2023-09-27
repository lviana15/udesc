package dados;
import java.util.ArrayList;
import java.util.List;

public abstract class Gerador {
	protected List<Integer> sequencia;
	
	Gerador() {
		sequencia = new ArrayList<Integer>();
	}
	
	public abstract void gerar(int quantidade);
	
	public List<Integer> getSequencia() {
		return sequencia;
	}
}
