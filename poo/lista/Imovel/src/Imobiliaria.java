
public class Imobiliaria {
    private String nome;
    private Imovel imoveis[];
    private int qtdImoveis = 0;
    
    public Imobiliaria(String nome) {
    	this.nome = nome;
    }
    
    public void adicionarImovel(Imovel imovel) {
        if (imoveis == null) {
            imoveis = new Imovel[1];
        } else {
            Imovel[] novoArray = new Imovel[imoveis.length + 1];
            System.arraycopy(imoveis, 0, novoArray, 0, imoveis.length);
            imoveis = novoArray;
        }

        imoveis[imoveis.length - 1] = imovel;
    }
    
    public void cadastrarImovel(Imovel imovel) {
    	imoveis[qtdImoveis] = imovel;
    	qtdImoveis++;
    }
    
    public Imovel[] filtrarPorArea(double areaMinima) {
        int count = 0;
        for (Imovel imovel : imoveis) {
            if (imovel.calcularArea() >= areaMinima) {
                count++;
            }
        }

        Imovel[] imoveisFiltrados = new Imovel[count];

        int index = 0;
        for (Imovel imovel : imoveis) {
            if (imovel.calcularArea() >= areaMinima) {
                imoveisFiltrados[index] = imovel;
                index++;
            }
        }

        for (int i = 0; i < imoveisFiltrados.length - 1; i++) {
            for (int j = 0; j < imoveisFiltrados.length - i - 1; j++) {
                if (imoveisFiltrados[j].getPreco() > imoveisFiltrados[j + 1].getPreco()) {
                    Imovel temp = imoveisFiltrados[j];
                    imoveisFiltrados[j] = imoveisFiltrados[j + 1];
                    imoveisFiltrados[j + 1] = temp;
                }
            }
        }

        return imoveisFiltrados;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public Imovel[] getImoveis() {
        return imoveis;
    }

    public void setImoveis(Imovel[] imoveis) {
        this.imoveis = imoveis;
    }

    public String toString(){
        String string = ""; 
        string += "Imobiliaria [ Nome: " +nome+ "]\n";
        string += "Imoveis:\n";
        for(Imovel imovel: imoveis) {
        	if(imovel == null) { break; }
        	string += "- " +imovel+ "]\n";
        }
        
        return string;
    }

}
