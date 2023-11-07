public class Arquivo {
    private String nome;
    private String extensao;


    public Arquivo(String nome) throws NomeInvalidoException {
        char[] caracteres = {'(', ')', '[', ']', '"', '\'', '\n'};
        CharSequence caracteresEspeciais = new String(caracteres);
        boolean tamanhoValido = nome.length() >= 10 && nome.length() <= 256;

        if (nome.contains(caracteresEspeciais) || !tamanhoValido) {
            throw new NomeInvalidoException();
        } else {
            this.nome = nome;
        }
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getNome() {
        return nome;
    }

    public void setExtensao(String extensao) {
        this.extensao = extensao;
    }

    public String getExtensao() {
        return extensao;
    }
}