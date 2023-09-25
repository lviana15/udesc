package dados;

public class Carro extends Veiculo {
	private int numeroPortas;
	private Combustivel combustivel;

	public void setNumeroPortas(int numeroPortas) {
		this.numeroPortas = numeroPortas;
	}
	
	public int getNumeroPortas() {
		return numeroPortas;
	}
	
	public void setCombustivel(Combustivel combustivel) {
		this.combustivel = combustivel;
	}
	
	public Combustivel getCombustivel() {
		return combustivel;
	}
	
	public String info() {
		return "\nCarro:\n"  +"Cor: " +getCor()+ " Portas: " +numeroPortas;
	}

}
