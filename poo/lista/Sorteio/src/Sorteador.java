import java.util.Random;

public class Sorteador {
	private Pessoa pessoas[];
    private int tamanho;
    private Random random = new Random();

    public Sorteador(int capacidade) {
        pessoas = new Pessoa[capacidade];
        tamanho = 0;
    }

    public void adicionarPessoa(Pessoa pessoa) {
            pessoas[tamanho] = pessoa;
            tamanho++;
    }

    public Pessoa sortearProximo() {
        int idxSorteado = random.nextInt(tamanho);
        Pessoa pessoaSorteada = pessoas[idxSorteado];

        pessoas[idxSorteado] = pessoas[tamanho - 1];
        tamanho--;

        return pessoaSorteada;
    }
}
