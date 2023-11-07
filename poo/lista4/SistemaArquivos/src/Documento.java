public class Documento extends Arquivo {
    private String texto;
    public Documento(String nome) throws NomeInvalidoException {
        super(nome);
        this.setExtensao(".txt");
    }

    public String toString() {
        return getNome() + getExtensao();
    }
}
