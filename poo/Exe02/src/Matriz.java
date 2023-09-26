import java.util.List;

public class Matriz<T> {
	private int linhas;
	private int colunas;
	private List<List<Integer>> matriz;
	
	public Matriz() {
		
	}
	
	public T get(int i, int j) {
		return matriz[i][j];
	}
}
