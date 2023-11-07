public class ProcessoSemJuizException extends Exception {
    public ProcessoSemJuizException() {
        super("Processo sem juiz");
    }

    public ProcessoSemJuizException(String mensagem) {
        super(mensagem);
    }
}
