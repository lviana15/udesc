import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Main {
	private static Map<Integer, List<Integer>> todasAsTabuadas = new HashMap<Integer, List<Integer>>();
	
	public static void main(String[] args) {
		for(int i = 1; i <= 10; i++) {
			todasAsTabuadas.put(i, tabuada(i));
		}
		
		todasAsTabuadas.forEach(
				(chave, tabuada) -> {
					System.out.print("Tabuada de " +chave+ ": ");
					for (int x: tabuada) {
						System.out.print("\t" +x+ " ");
					}
					System.out.println();
				}
		);
	}
	
	public static List<Integer> tabuada (int n) {
		List<Integer> tabuada = new ArrayList<Integer>();
		
		for (int i = 1; i <= 10; i++) {
			tabuada.add(i * n);
		}
		
		return tabuada;
	}
}
