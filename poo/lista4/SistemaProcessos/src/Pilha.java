import java.util.ArrayList;
import java.util.List;

public class Pilha<T> {
    private int limite;
    private List<T> elementos;

    public Pilha(int limite) {
        this.limite = limite;
        this.elementos = new ArrayList<>();
    }

    public void inserir(T objeto) throws PilhaCheiaException {
        if (this.getSize() >= limite) {
            throw new PilhaCheiaException();
        }
        elementos.add(objeto);
    }

    public T remover() throws PilhaVaziaException {
        if (elementos.isEmpty()) {
            throw new PilhaVaziaException();
        }

        int ultimo = elementos.size() - 1;
        T elemento = elementos.get(ultimo);
        elementos.remove(0);

        return elemento;
    }

    public int getSize() {
        return elementos.size();
    }
}
