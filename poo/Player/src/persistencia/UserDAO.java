package src.persistencia;

import src.dados.User;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UserDAO {
    private static UserDAO instance = null;
    private PreparedStatement selectUserByUsername;
    private PreparedStatement insertUser;

    public static UserDAO getInstance() {
        if (instance == null)
            instance = new UserDAO();
        return instance;
    }

    private UserDAO() {
        try {
            Connection conn = DatabaseConnection.getConnection();
            selectUserByUsername = conn.prepareStatement("SELECT * FROM users WHERE username = ?");
            insertUser = conn.prepareStatement("INSERT INTO users (name, username, password) VALUES (?, ?, ?)");
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public User getUserByUsername(String username) {
        try {
            selectUserByUsername.setString(1, username);
            ResultSet resultSet = selectUserByUsername.executeQuery();

            if (resultSet.next()) {
                return new User(
                        resultSet.getString("name"),
                        resultSet.getString("username"),
                        resultSet.getString("password")
                );
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return null;
    }

    public int insertUser(User user) {
        try {
            insertUser.setString(1, user.getName());
            insertUser.setString(2, user.getUsername());
            insertUser.setString(3, user.getPassword());

            // Execute the insert statement and retrieve the generated keys
            int rowsAffected = insertUser.executeUpdate();
            if (rowsAffected > 0) {
                ResultSet generatedKeys = insertUser.getGeneratedKeys();
                if (generatedKeys.next()) {
                    return generatedKeys.getInt(1); // Retrieve the generated user_id
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
            // Handle the exception according to your application's needs
        }

        return -1; // Return -1 if an error occurs
    }
}
