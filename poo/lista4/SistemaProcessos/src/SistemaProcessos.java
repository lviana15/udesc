import java.util.List;
import java.util.ArrayList;
import java.util.Random;

public class SistemaProcessos {
    private List<Processo> processos = new ArrayList<Processo>();
    private List<Juiz> juizes = new ArrayList<Juiz>();

    public void cadastrarProcesso(Processo processo) {
            processos.add(processo);
    }

    public void cadastrarJuiz(Juiz juiz) {
        juizes.add(juiz);
    }

    public List<Processo> getProcessos() {
        return processos;
    }

    public List<Juiz> getJuizes() {
        return juizes;
    }

    public void distribuiProcessos() throws ProcessoSemJuizException {
        Random random = new Random();

        for (Processo processo: processos) {
            boolean adicionado = false;
            try{
                Juiz juiz = juizes.get(random.nextInt(juizes.size()));
                juiz.cadastrarProcesso(processo);
                adicionado = true;
            } catch (PilhaCheiaException e) {
                System.out.println(e.getMessage());
            }

            if (!adicionado) {
                throw new ProcessoSemJuizException();
            }
        }
    }
}
