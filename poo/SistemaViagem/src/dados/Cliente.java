package dados;

public class Cliente {
	private int cpf;
	private String nome;
	private String endereco;
	private int telefone;
	private Reserva reservas[];
	
	public void reservarIda(Reserva reserva) {
		reservas[reservas.length] = reserva;
	}
	
	public void reservarVolta(Reserva ida, Reserva volta) {
		reservas[reservas.length] = ida;
		reservas[reservas.length] = volta;
	}
	
	public int getCpf() {
		return cpf;
	}
	
	public String getEndereco() {
		return endereco;
	}
	
	public String getNome() {
		return nome;
	}
	
	public int getTelefone() {
		return telefone;
	}
	
	public Reserva[] getReservas() {
		return reservas;
	}
	
	public void setCpf(int cpf) {
		this.cpf = cpf;
	}
	
	public void setEndereco(String endereco) {
		this.endereco = endereco;
	}
	
	public void setNome(String nome) {
		this.nome = nome;
	}
	
	public void setTelefone(int telefone) {
		this.telefone = telefone;
	}
	
	public String toString() {
		return "Nome: " +nome+ ", Endereço: " +endereco+ ", CPF: " +cpf+ ", Telefone: " +telefone+ ", Reservas: " +reservas;
	}
}
