package src.persistencia;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class GenericDAO {
    private static GenericDAO instance = null;

    public static GenericDAO getInstance() {
        if (instance == null)
            instance = new GenericDAO();
        return instance;
    }

    public void printAllRows(String tableName) {
        try {
            Connection conn = DatabaseConnection.getConnection();
            PreparedStatement preparedStatement = conn.prepareStatement("SELECT * FROM " + tableName);
            ResultSet resultSet = preparedStatement.executeQuery();

            System.out.print("\033[H\033[2J");
            System.out.flush();
            System.out.println("=== " + tableName + " ===");

            while (resultSet.next()) {
                int columnCount = resultSet.getMetaData().getColumnCount();
                for (int i = 1; i <= columnCount; i++) {
                    String columnName = resultSet.getMetaData().getColumnName(i);
                    String columnValue = resultSet.getString(i);
                    System.out.print(columnName + ": " + columnValue + "\t");
                }
                System.out.println();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
