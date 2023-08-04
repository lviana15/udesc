import java.util.Scanner;

public class Pratica1 {
	public static void main(String[] args) {
        int[] arr = new int[5];
        int sum = 0;

        Scanner in = new Scanner(System.in);
        System.out.println("Digite 5 valores:");
        for(int i = 0;i < 5;i++){
            arr[i] = Integer.parseInt(in.nextLine());
        }
        in.close();

        for(int i = 0;i < 5;i++){
            sum += arr[i];
        }

        System.out.println("Media dos valores: " +sum/5);
	}
}
