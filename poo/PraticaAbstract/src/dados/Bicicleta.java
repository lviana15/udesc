package dados;

public class Bicicleta extends Veiculo {
	private int numeroMarchas;
	
	public void setNumeroMarchas(int numeroMarchas) {
		this.numeroMarchas = numeroMarchas;
	}
	
	public int getNumeroMarchas() {
		return numeroMarchas;
	}

	public String info() {
		return "\nBicicleta\n" +"Cor: " +getCor()+ " Numero Marchas: " +numeroMarchas;
	}
}
