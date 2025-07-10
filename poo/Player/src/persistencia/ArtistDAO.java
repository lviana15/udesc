package src.persistencia;

import src.dados.Artist;
import src.dados.Song;

import java.sql.*;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

public class ArtistDAO {

    private static ArtistDAO instance = null;
    private PreparedStatement insertArtist;

    public static ArtistDAO getInstance() {
        if (instance == null)
            instance = new ArtistDAO();
        return instance;
    }

    private ArtistDAO() {
        try {
            Connection conn = DatabaseConnection.getConnection();

            insertArtist = conn.prepareStatement("INSERT INTO artists (name, bio) VALUES (?, ?)");
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public int insertArtist(Artist artist) {
        try {
            insertArtist.setString(1, artist.getName());
            insertArtist.setString(2, artist.getBio());

            int rowsAffected = insertArtist.executeUpdate();
            if (rowsAffected > 0) {
                ResultSet generatedKeys = insertArtist.getGeneratedKeys();
                if (generatedKeys.next()) {
                    return generatedKeys.getInt(1);
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return -1;
    }
}
