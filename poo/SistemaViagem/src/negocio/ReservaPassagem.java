package negocio;

import dados.Cidade;
import dados.Cliente;
import dados.Reserva;

public class ReservaPassagem {
	private Cidade listaDeCidades[];
	private Cliente listaDeClientes[];
	
	public void cadastrarCidade(Cidade cidade) {
		listaDeCidades[listaDeCidades.length] = cidade;
	}
	
	public void cadastrarCliente(Cliente cliente) {
		listaDeClientes[listaDeClientes.length] = cliente;
	}
	
	public void reservarIda(Cliente cliente, Reserva reserva) {
		cliente.reservarIda(reserva);
	}
	
	public void reservarVolta(Cliente cliente, Reserva reserva, Reserva volta) {
		cliente.reservarVolta(reserva, volta);
	}
	
	public Reserva[] mostrarReservas(int cpfCliente) {
		for (int i = 0; i < listaDeClientes.length; i++) {
			if (listaDeClientes[i].getCpf() == cpfCliente) {
				return listaDeClientes[i].getReservas();
			}
		}
		return null;
	}
	
	public 	Cliente[] mostrarClientes() {
		return listaDeClientes;
	}
	
	public 	Cidade[] mostrarCidades() {
		return listaDeCidades;
	}
}
