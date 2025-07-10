package apresentacao;

import java.awt.EventQueue;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextField;

public class Calculadora extends JFrame {
	private JPanel painel = new JPanel();
	private JPanel painelEntrada = new JPanel();
	private JLabel infoCaixaTexto = new JLabel("Digite um valor:");
	private JTextField caixaTexto = new JTextField();
	private JButton botaoAdicionar = new JButton("adicionar");
	private JButton botaoLimpar = new JButton("limpar");
	private JScrollPane painelScrollTabelaResultados = new JScrollPane();
	private JTable tabelaResultados;
	private TabelaResultados resultados = new TabelaResultados();
	private JScrollPane painelScrollTabelaValores = new JScrollPane();
	private JTable tabelaValores;
	private TabelaValores valores = new TabelaValores();

	public Calculadora() {
		setTitle("Calculadora Estatistica");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 900, 300);

		setContentPane(painel);
		painel.setLayout(null);

		painelEntrada.setBounds(15, 80, 280, 173);
		painelEntrada.setLayout(null);
		painel.add(painelEntrada);

		infoCaixaTexto.setBounds(30, 30, 200, 15);
		painelEntrada.add(infoCaixaTexto);

		caixaTexto.setBounds(30, 50, 200, 20);
		painelEntrada.add(caixaTexto);

		botaoAdicionar.setBounds(77, 94, 117, 25);
		painelEntrada.add(botaoAdicionar);

		botaoLimpar.setBounds(77, 136, 117, 25);
		painelEntrada.add(botaoLimpar);

		painelScrollTabelaResultados.setBounds(10, 10, 880, 50);
		painel.add(painelScrollTabelaResultados);

		tabelaResultados = new JTable(resultados);
		painelScrollTabelaResultados.setViewportView(tabelaResultados);

		painelScrollTabelaValores.setBounds(307, 80, 173, 173);
		painel.add(painelScrollTabelaValores);

		tabelaValores = new JTable(valores);
		painelScrollTabelaValores.setViewportView(tabelaValores);

		botaoAdicionar.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				valores.adicionaValor(Integer.parseInt(caixaTexto.getText()));
				resultados.atualizar();
				caixaTexto.setText("");
			}
		});

		botaoLimpar.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				valores.limpar();
				resultados.atualizar();
			}
		});
	}

	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					Calculadora frame = new Calculadora();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}
}
