public class Main {
    public static void main(String[] args) {
        SistemaProcessos sistema = new SistemaProcessos();

        for(int i = 0; i < 3; i++) {
            sistema.cadastrarJuiz(new Juiz(5));
        }

        for(int i = 0; i < 18; i++) {
            sistema.cadastrarProcesso((new Processo()));
        }

        try {
            sistema.distribuiProcessos();
        } catch (ProcessoSemJuizException e){
            System.out.println(e.getMessage());
        }

    }
}
