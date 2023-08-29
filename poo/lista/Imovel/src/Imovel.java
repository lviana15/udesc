public class Imovel {
    private double largura;
    private double comprimento;
    private double preco;
    
    public Imovel(double largura, double comprimento, double preco) {
    	this.largura = largura;
    	this.comprimento = comprimento;
    	this.preco = preco;
    }

    public double calcularArea() {
        double area = largura * comprimento;
        return area;
    }

    public double getLargura() {
        return largura;
    }

    public void setLargura(double largura) {
        this.largura = largura;
    }

    public double getComprimento() {
        return comprimento;
    }

    public void setComprimento(double comprimento) {
        this.comprimento = comprimento;
    }

    public double getPreco() {
        return preco;
    }

    public void setPreco(double preco) {
        this.preco = preco;
    }

    public String toString() {
        return "Imovel [Largura: " + largura + ", Comprimento: " + comprimento + ", Preco: " + preco;
    }
}
