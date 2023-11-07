public class Juiz {
    private String nome;
    private Pilha<Processo> processos;

    public Juiz(int limite) {
        this.processos = new Pilha<Processo>(limite);
    }

    public void cadastrarProcesso(Processo processo) throws PilhaCheiaException {
        try{
            processos.inserir(processo);
        } catch (PilhaCheiaException e) {
            System.out.println(e.getMessage());
        }
    }
}
