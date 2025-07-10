package persistencia;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class Conexao {
    private static Connection connection = null;
    private String senha;

    private Conexao() {
    };

    public static Connection getConexao() {
        try {
            if (connection == null) {
                Class.forName("org.postgresql.Driver");
                String url = "jdbc:postgresql://localhost:5432/pratica";
                Connection connection = DriverManager.getConnection(url, "postgres", "lucasusanike");
            }
        } catch (ClassNotFoundException | SQLException e) {
            System.err.print(e.getMessage());
        }

        return connection;
    }
}
