import java.util.Scanner;

public class Pratica2 {	
	public static void main(String[] args) {
		int n = 5;
		String[] nameArr = new String[n];
		int[] ageArr = new int[n];

		Scanner in = new Scanner(System.in);

		for(int i = 0; i < n;i++) {
			System.out.print("Digite nome:");
			nameArr[i] = in.nextLine();

			System.out.print("Digite idade:");
			ageArr[i] = Integer.parseInt(in.nextLine());
		}
		
		in.close();
		
		for(int i = 0;i < n;i++) {
			
			int maxIdx = i;
			for(int j = i+1;j < n;j++)
				if (ageArr[j] > ageArr[maxIdx])
					maxIdx = j;
			
			int temp = ageArr[i];
			ageArr[i] = ageArr[maxIdx];
			ageArr[maxIdx] = temp;
			
			String tempS = nameArr[i];
			nameArr[i] = nameArr[maxIdx];
			nameArr[maxIdx] = tempS;
		}	
		
		for(int i = 0;i < n;i++) {
			System.out.println(nameArr[i] + " - " +ageArr[i]);
		}
	}
}
