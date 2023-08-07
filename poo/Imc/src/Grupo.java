
public class Grupo {
	private Pessoa[] pessoas = new Pessoa[3];
	private int numeroPessoas = 0;

	public void setPessoa(Pessoa p) {
		if (this.numeroPessoas < 3) {
			pessoas[this.numeroPessoas] = p;
			this.numeroPessoas++;
		}
	}
	
	public Pessoa[] getPessoas() {
		return this.pessoas;
	}

	public void ordena() {
		for (int i = 0; i < 3; i++) {
			for (int j = i + 1; j < 3; j++) {
				if (this.pessoas[j].calculaImc() > this.pessoas[i].calculaImc()) {
					Pessoa aux = this.pessoas[j];
					this.pessoas[j] = this.pessoas[i];
					this.pessoas[i] = aux;
				}
			}
		}
	}
}
