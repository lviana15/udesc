package src.persistencia;

import src.dados.Artist;
import src.dados.Song;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class SongDAO {

    private static SongDAO instance = null;
    private PreparedStatement insertSong;
    private PreparedStatement insertArtistSong;
    private PreparedStatement insertSongBytea;

    public static SongDAO getInstance() {
        if (instance == null)
            instance = new SongDAO();
        return instance;
    }

    private SongDAO() {
        try {
            Connection conn = DatabaseConnection.getConnection();

            insertSong = conn.prepareStatement("INSERT INTO songs (title, release_date) VALUES (?, ?)");
            insertArtistSong = conn.prepareStatement("INSERT INTO artist_songs (artist_id, song_id) VALUES (?, ?)");
            insertSongBytea = conn.prepareStatement("INSERT INTO songs (song_bytea) VALUES (?)");
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public int insertSong(Song song, List<Integer> authors) {
        int songId = -1;

        try {
            insertSong.setString(1, song.getTitle());
            insertSong.setDate(2, java.sql.Date.valueOf(song.getRelease()));

            int rowsAffected = insertSong.executeUpdate();

            if (rowsAffected > 0) {
                ResultSet generatedKeys = insertSong.getGeneratedKeys();

                if (generatedKeys.next()) {
                    songId = generatedKeys.getInt(1);

                    for (int author : authors) {
                        insertArtistSong.setInt(1, author);
                        insertArtistSong.setInt(2, songId);
                        insertArtistSong.executeUpdate();
                    }
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return songId;
    }

    public void insertSongBytea(File file) {
        try (FileInputStream fis = new FileInputStream(file)) {
            insertSongBytea.setString(1, file.getName());
            insertSongBytea.setBinaryStream(2, fis, (int) file.length());
            insertSongBytea.executeUpdate();
        } catch (SQLException | IOException e) {
            e.printStackTrace();
        }
    }
}
