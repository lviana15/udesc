
public class Main {

	public static void main(String[] args) {
		Sorteador sorteador = new Sorteador(3);

        Pessoa pessoa1 = new Pessoa("Lucas");
        Pessoa pessoa2 = new Pessoa("Douglas");
        Pessoa pessoa3 = new Pessoa("Anna");

        sorteador.adicionarPessoa(pessoa1);
        sorteador.adicionarPessoa(pessoa2);
        sorteador.adicionarPessoa(pessoa3);

        for (int i = 0; i < 3; i++) {
            Pessoa sorteada = sorteador.sortearProximo();
            if (sorteada != null) {
                System.out.println("Pessoa sorteada: " + sorteada.getNome());
            }
        }
	}

}
