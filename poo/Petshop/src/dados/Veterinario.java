package dados;

public class Veterinario {
    private String nome;
    private float salario;
    private Endereco endereco = new Endereco();
    private Animal animais[];
    private int quantidadeAnimais = 0;
    
    public Veterinario (int tamAnimais) {
    	animais = new Animal[tamAnimais];
    }

    public String getNome(){
        return this.nome;
    }

    public float getSalario(){
        return this.salario;
    }

    public Endereco getEndereco(){
        return this.endereco;
    }

    public Animal[] getAnimais(){
        return this.animais;
    }

    public int getQuantidadeAnimais(){
        return this.quantidadeAnimais;
    }

    public void setNome(String nome){
       this.nome = nome;
    }

    public void setSalario(float salario){
       this.salario = salario;
    }

    public void setEndereco(Endereco endereco){
       this.endereco = endereco;
    }
    
    public String toString() {
    	return "Nome: " +nome+ ", Salario: " +salario;
    }

}
