package dados;

public class Peixe extends Animal {
	
	private float temperaturaIdeal;
	
	public float getTemperaturaIdeal() {
		return temperaturaIdeal;
	}

	public void setTemperaturaIdeal(float temperaturaIdeal) {
		this.temperaturaIdeal = temperaturaIdeal;
	}
	
	public float calculaEspacoOcupado() {
		return altura * super.calculaEspacoOcupado();
	}
	
	public String toString() {
		return super.toString() + " Temperatura: "+ temperaturaIdeal;
	}

}
