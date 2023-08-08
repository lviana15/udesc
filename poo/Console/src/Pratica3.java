import java.util.Scanner;

public class Pratica3 {
	public static void main(String[] args) {
		int n = 3;
		String[] nameArr = new String[n];
		int[] ageArr = new int[n];

		Scanner in = new Scanner(System.in);

		for(int i = 0; i < n;i++) {
			System.out.print("Digite nome:");
			nameArr[i] = in.nextLine();

			System.out.print("Digite idade:");
			ageArr[i] = Integer.parseInt(in.nextLine());
		}
		
		for(int i = 0;i < n;i++) {
			System.out.println(nameArr[i] + " - " +ageArr[i]);
		}
	}
}
