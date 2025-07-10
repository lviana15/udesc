package apresentacao;

import javax.swing.table.AbstractTableModel;

import dados.CalculadoraEstatistica;

public class TabelaValores extends AbstractTableModel {
	private String[] colunas = { "Valores" };
	private CalculadoraEstatistica calculadora = CalculadoraEstatistica.getInstance();
	
	public void adicionaValor(int valor) {
		calculadora.adicionarValor(valor);
		fireTableStructureChanged();
	}
	
	public void limpar() {
		calculadora.limparValores();
		fireTableStructureChanged();
	}

	public String getColumnName(int column) {
		return colunas[column];
	}

	@Override
	public int getRowCount() {
		return calculadora.getValores().size();
	}

	@Override
	public int getColumnCount() {
		return 1;
	}

	@Override
	public Object getValueAt(int linha, int coluna) {
		return calculadora.getValores().get(linha);
	}
}
