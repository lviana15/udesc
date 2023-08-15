package dados;

public class Dono {
    private String nome;
    private Endereco endereco;
    private String cpf;

    public String getNome(){
        return this.nome;
    }

    public Endereco getEndereco(){
        return this.endereco;
    }

    public String getCpf(){
        return this.cpf;
    }

    public void setNome(String nome){
        this.nome = nome;
    }

    public void setEndereco(Endereco endereco){
        this.endereco = endereco;
    }

    public void setCpf(String cpf){
        this.cpf = cpf;
    }
    
    public String toString() {
    	return "Nome: " +nome+ "CPF: " +cpf;
    }
}
