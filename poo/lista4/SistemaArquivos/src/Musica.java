public class Musica extends Arquivo {
    private int duracao;

    public Musica(String nome) throws NomeInvalidoException{
        super(nome);
        this.setExtensao(".mp3");
    }

    public String toString(){
        return getNome() + getExtensao();
    }
}
