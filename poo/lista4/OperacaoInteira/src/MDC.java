public class MDC implements IOperacaoInteira {

    public int executar(int valor1, int valor2) {
        while (valor2 != 0) {
            int temp = valor2;
            valor2 = valor1 - (valor1 / valor2) * valor2;
            valor1 = temp;
        }

        return valor1;
    }
}
