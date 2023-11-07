import java.util.Random;
import java.util.List;
import java.util.ArrayList;

public class Main {
        public static void main(String[] args) {
            List<IOperacaoInteira> operacoes = new ArrayList<>();
            operacoes.add(new Soma());
            operacoes.add(new Multiplicacao());
            operacoes.add(new MDC());
            operacoes.add(new Mod());

            Random random = new Random();
            int valor1 = random.nextInt(100);
            int valor2 = random.nextInt(100);

            System.out.println("Valor 1: " +valor1+ " Valor 2: " +valor2);
            for (IOperacaoInteira operacao : operacoes) {
                int resultado = operacao.executar(valor1, valor2);
                System.out.println(operacao.getClass().getSimpleName() + ": " + resultado);
            }
        }
}
