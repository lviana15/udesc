package dados;

public class Viveiro {
	protected String nome;
	protected float comprimento;
	protected float largura;
	protected Animal[] listaAnimais;
	
	public float calculaEspaco() {
		return largura * comprimento;
	}
	
	private float espacoOcupado() {
		float espaco = 0;
		for(Animal animal: listaAnimais) {
			espaco += animal.calculaEspacoOcupado();
		}
		
		return espaco;
	}
	
	public float espacoDisponivel() {
		return calculaEspaco() - espacoOcupado();
	}
	
	public boolean adicionarAnimal() {
		return true;
	}
	
	public String getNome() {
		return nome;
	}
	public void setNome(String nome) {
		this.nome = nome;
	}
	public float getComprimento() {
		return comprimento;
	}
	public void setComprimento(float comprimento) {
		this.comprimento = comprimento;
	}
	public float getLargura() {
		return largura;
	}
	public void setLargura(float largura) {
		this.largura = largura;
	}

	public Animal[] getListaAnimais() {
		return listaAnimais;
	}

	public void setListaAnimais(Animal[] listaAnimais) {
		this.listaAnimais = listaAnimais;
	}
	
	
}
