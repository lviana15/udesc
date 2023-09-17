package negocio;

import java.util.ArrayList;

import dados.User;

public class PlayerSystem {
	private static ArrayList<User> users = new ArrayList<User>();
	
	public static void main(String[] args) {
		System.out.println("Register a user");
		
		User firstUser = new User("Lucas", "lucas", "12345678");
		System.out.println(firstUser);
		addUser(firstUser);
	}
	
	public static void addUser(User user) {
		for (User existingUser: users) {
			if (existingUser.getUsername().equals(user.getUsername())){
				System.out.println("User already exists.");
				return;
			} 
		}
		
		
		users.add(user);
	}
}
