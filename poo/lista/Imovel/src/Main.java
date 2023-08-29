
public class Main {

	public static void main(String[] args) {
		Imovel imovel1 = new Imovel(10, 30, 80000);
		Imovel imovel2 = new Imovel(20, 40, 120000);
		Imovel imovel3 = new Imovel(20, 25, 100000);
		
		Imobiliaria imobiliaria = new Imobiliaria("Imobi");
		imobiliaria.adicionarImovel(imovel1);
		imobiliaria.adicionarImovel(imovel2);
		imobiliaria.adicionarImovel(imovel3);
				
		System.out.println(imobiliaria);
		
		Imovel[] filtrados = imobiliaria.filtrarPorArea(800);
		for(Imovel imovel: filtrados) {
			System.out.println(imovel);			
		}

	}

}
