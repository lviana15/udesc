public class PilhaVaziaException extends Exception {
        public PilhaVaziaException(){
            super("Pilha vazia");
        }

        public PilhaVaziaException(String mensagem){
            super (mensagem);
        }
}
