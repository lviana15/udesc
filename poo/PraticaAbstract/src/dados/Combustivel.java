package dados;

public enum Combustivel {
	GASOLINA("gasolina"),
	ALCOOL("alcool"),
	DIESEL("diesel"),
	GAS("gas");
	
	private String combustivel;
	
	Combustivel(String combustivel) {
		this.combustivel = combustivel;
	}
	
	public String getCombustivel() {
		return combustivel;
	}
}
