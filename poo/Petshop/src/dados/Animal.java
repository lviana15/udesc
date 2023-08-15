package dados;

public class Animal {
    private String nome;
    private Dono dono;
    private String especie;
    private String descricao;

    public String getNome(){
        return this.nome;
    }

    public Dono getDono(){
        return this.dono;
    }

    public String getEspecie(){
        return this.especie;
    }

    public String getDescricao(){
        return this.descricao;
    }

    public void setNome(String nome){
        this.nome = nome;
    }

    public void setDono(Dono dono){
        this.dono = dono;
    }

    public void setEspecie(String especie){
        this.especie = especie;
    }

    public void setDescricao(String descricao){
        this.descricao = descricao;
    }
    
    public String toString() {
    	return "Nome: " +nome+ ", Especie: " +especie+ ", Descricao: " +descricao;
    }
}
