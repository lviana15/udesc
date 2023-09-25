package dados;

public abstract class Veiculo {
	private Cor cor;
	
	public void setCor(Cor cor) {
		this.cor = cor;
	}
	
	public Cor getCor() {
		return cor;
	}
	
	public abstract String info();
}
