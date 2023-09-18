import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		List<Pessoa> pessoas = new ArrayList<>();

		try (Scanner sc = new Scanner(new File("lista.txt"))) {
			while (sc.hasNextLine()) {
				String line = sc.nextLine();
				String[] parse = line.split(",");
				String nome = parse[0];
				int idade = Integer.parseInt(parse[1]);
				String cpf = parse[2];
				String cidade = parse[3];
				Pessoa pessoa = new Pessoa(nome, idade, cpf, cidade);
				
				pessoas.add(pessoa);
			}
		} catch (FileNotFoundException e){
			Scanner sc = new Scanner(System.in);
		}
		
		Collections.sort(pessoas, Comparator.comparing(Pessoa::getNome));
		
		
		String criancas = "Crianças: \n";
		String adolescentes = "Adolescentes: \n";
		String jovens = "Jovens: \n";
		String adultos = "Adultos: \n";
		String idosos = "Idosos: \n";
		
		for (Pessoa pessoa : pessoas) {
			if ((1 <= pessoa.getIdade()) && (pessoa.getIdade() <= 12)) {
				criancas += "- " +pessoa+ "\n";
			}

			if ((12 <= pessoa.getIdade()) && (pessoa.getIdade() <= 18)) {
				adolescentes += "- " +pessoa+ "\n";
			}
			
			if ((19 <= pessoa.getIdade()) && (pessoa.getIdade() <= 25)) {
				jovens += "- " +pessoa+ "\n";
			}
			
			if ((26 <= pessoa.getIdade()) && (pessoa.getIdade() <= 59)) {
				adultos += "- " +pessoa+ "\n";
			}
			
			if (60 <= pessoa.getIdade()) {
				idosos += "- " +pessoa+ "\n";
			}
			
		}
		
		System.out.println(criancas);
		System.out.println(adolescentes);
		System.out.println(jovens);
		System.out.println(adultos);
		System.out.println(idosos);

	}

}
