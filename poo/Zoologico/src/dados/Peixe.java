package dados;

public class Peixe extends Animal {
	private float temperaturaIdeal;

	public float calculaEspacoOcupado() {
		return super.calculaEspacoOcupado() * altura;
	}
	
	public float getTemperaturaIdeal() {
		return temperaturaIdeal;
	}

	public void setTemperaturaIdeal(float temperaturaIdeal) {
		this.temperaturaIdeal = temperaturaIdeal;
	}
	
	
}
