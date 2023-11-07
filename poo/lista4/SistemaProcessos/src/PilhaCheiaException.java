public class PilhaCheiaException extends Exception {
    public PilhaCheiaException(){
        super("Pilha cheia");
    }

    public PilhaCheiaException(String mensagem){
        super (mensagem);
    }
}
