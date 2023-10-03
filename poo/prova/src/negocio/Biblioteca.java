package negocio;

import java.util.ArrayList;
import java.util.List;

import dados.Item;
import dados.Emprestimo;
import dados.Usuario;

public class Biblioteca {
	private List<Item> itens;
	private List<Emprestimo> emprestimos;
	private List<Usuario> usuarios;
	
	public Biblioteca() {
		itens = new ArrayList<Item>();
		emprestimos = new ArrayList<Emprestimo>();
		usuarios = new ArrayList<Usuario>();
	}
	
	public void cadastrarUsuario(Usuario u) {
		usuarios.add(u);
	}
	
	public void cadastraItem(Item i) {
		itens.add(i);
	}
	
	public List<Emprestimo> getEmprestimosItem(Item i){
		List<Emprestimo> emprestimosItem = new ArrayList<Emprestimo>();
		for(Emprestimo e: emprestimos) {
			if (e.getItem() == i) emprestimosItem.add(e);
		}
		
		return emprestimosItem;
	}
	
	public List<Emprestimo> getEmprestimosUsuario(Usuario u) {
		List<Emprestimo> emprestimosUsuarios = new ArrayList<Emprestimo>();
		for(Emprestimo e: emprestimos) {
			if (e.getUsuario() == u) emprestimosUsuarios.add(e);
		}
		
		return emprestimosUsuarios;	
	}

	public boolean emprestar(Usuario u, Item i) {
		if ((i.getTempoEmprestimo() == 15) && u.podeEmprLivro()) {
			Emprestimo emprestimo = new Emprestimo(u, i);
			u.setLimiteEmpLivro(u.getLimiteEmpLivro()-1);
			emprestimos.add(emprestimo);
			
			return true;
		} else if ((i.getTempoEmprestimo() == 30) && u.podeEmprMono()){
			Emprestimo emprestimo = new Emprestimo(u, i);
			u.setLimiteEmpMono(u.getLimiteEmpMono()-1);
			emprestimos.add(emprestimo);
			
			return true;
		} else {
			return false;
		}
	}

	public void devolver(Emprestimo e) {
		e.devolver();
	}
	
	public void renovar(Emprestimo e) {
		e.setDataDevolucao(e.getDataDevolucao().plusDays(e.getItem().getTempoEmprestimo()));
	}
	
	public List<Emprestimo> getEmprestimos() {
		return emprestimos;
	}

	public void addEmprestimo(Emprestimo emprestimo) {
		emprestimos.add(emprestimo);
	}

	public List<Usuario> getUsuarios() {
		return usuarios;
	}

	public void addUsuario(Usuario usuario) {
		usuarios.add(usuario);
	}

	public List<Item> getItens(){
		return itens;
	}
	
	public void addItem(Item item) {
		itens.add(item);
	}
}
