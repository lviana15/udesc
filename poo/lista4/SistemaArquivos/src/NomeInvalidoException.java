public class NomeInvalidoException extends Exception {
    public NomeInvalidoException(){
        super("Nome invalido");
    }

    public NomeInvalidoException(String mensagem){
        super(mensagem);
    }
}
