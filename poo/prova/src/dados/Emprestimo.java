package dados;

import java.time.LocalDate;

public class Emprestimo {
	private int qntRenovado;
	private LocalDate dataEmprestimo;
	private LocalDate dataDevolucao;
	private Item item;
	private Usuario usuario;
	private boolean devolvido;
	
	public Emprestimo(Usuario usuario, Item item) {
		this.qntRenovado = 0;
		this.dataEmprestimo = LocalDate.now();
		this.dataDevolucao = LocalDate.now().plusDays(item.getTempoEmprestimo());
		this.setItem(item);
		this.setUsuario(usuario);
		
		item.emprestar();
	}
	
	public void devolver() {
		setDevolvido(true);
		this.item.devolver();
	}

	public int getQntRenovado() {
		return qntRenovado;
	}

	public void setQntRenovado(int qntRenovado) {
		this.qntRenovado = qntRenovado;
	}

	public LocalDate getDataEmprestimo() {
		return dataEmprestimo;
	}

	public void setDataEmprestimo(LocalDate dataEmprestimo) {
		this.dataEmprestimo = dataEmprestimo;
	}

	public LocalDate getDataDevolucao() {
		return dataDevolucao;
	}

	public void setDataDevolucao(LocalDate dataDevolucao) {
		this.dataDevolucao = dataDevolucao;
	}

	public Item getItem() {
		return item;
	}

	public void setItem(Item item) {
		this.item = item;
	}

	public Usuario getUsuario() {
		return usuario;
	}

	public void setUsuario(Usuario usuario) {
		this.usuario = usuario;
	}

	public boolean isDevolvido() {
		return devolvido;
	}

	public void setDevolvido(boolean devolvido) {
		this.devolvido = devolvido;
	}
	
	
}
