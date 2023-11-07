public class Multiplicacao extends Soma {

    public int executar(int valor1, int valor2) {
        int multi = 0;
        while (valor2 >= 1) {
            multi += super.executar(valor1, valor2);
            valor2--;
        }

        return multi;
    }
}
