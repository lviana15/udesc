package dados;

public class Endereco {
	private String rua;
	private int numero;
	private String bairro;
	private String cidade;
	private String estado;
	private String cep;

    public String getRua(){
        return this.rua;
    }

    public int getNumero(){
        return this.numero;
    }

    public String getBairro(){
        return this.bairro;
    }

    public String getCidade(){
        return this.cidade;
    }

    public String getEstado(){
        return this.estado;
    }

    public String getCep(){
        return this.cep;
    }

    public void setRua(String rua){
        this.rua = rua;
    }

    public void setNumero(int numero){
        this.numero = numero;
    }

    public void setBairro(String bairro){
        this.bairro = bairro;
    }

    public void setCidade(String cidade){
        this.cidade = cidade;
    }

    public void setEstado(String estado){
        this.estado = estado;
    }

    public void setCep(String cep){
        this.cep = cep;
    }
    
    public String toString() {
    	return "Rua: " +rua+ ", Número: " +numero+ ", Bairro: " +bairro+ ", Cidade: " +cidade+ ", Estado: " +estado+ ", CEP: " +cep;
    }
}
