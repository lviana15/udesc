package src.persistencia;

import src.dados.Playlist;
import src.dados.Song;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class PlaylistDAO {

    private static PlaylistDAO instance = null;
    private PreparedStatement insertPlaylist;
    private PreparedStatement insertSongToPlaylist;
    private PreparedStatement deleteSongFromPlaylist;

    public static PlaylistDAO getInstance() {
        if (instance == null)
            instance = new PlaylistDAO();
        return instance;
    }

    private PlaylistDAO() {
        try {
            Connection conn = DatabaseConnection.getConnection();

            insertPlaylist = conn.prepareStatement("INSERT INTO playlists (user_id, name) VALUES (?, ?)");
            insertSongToPlaylist = conn.prepareStatement("INSERT INTO playlist_songs (playlist_id, song_id) VALUES (?, ?)");
            deleteSongFromPlaylist = conn.prepareStatement("DELETE FROM playlist_songs WHERE playlist_id = ? AND song_id = ?");
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public int insertPlaylist(int userId, Playlist playlist) {
        try {
            insertPlaylist.setInt(1, userId);
            insertPlaylist.setString(2, playlist.getName());

            int rowsAffected = insertPlaylist.executeUpdate();
            if (rowsAffected > 0) {
                ResultSet generatedKeys = insertPlaylist.getGeneratedKeys();
                if (generatedKeys.next()) {
                    return generatedKeys.getInt(1);
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return -1;
    }

    public boolean addSongToPlaylist(int playlistId, int songId) {
        try {
            insertSongToPlaylist.setInt(1, playlistId);
            insertSongToPlaylist.setInt(2, songId);

            int rowsAffected = insertSongToPlaylist.executeUpdate();
            return rowsAffected > 0;
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return false;
    }

    public boolean removeSongFromPlaylist(int playlistId, int songId) {
        try {
            deleteSongFromPlaylist.setInt(1, playlistId);
            deleteSongFromPlaylist.setInt(2, songId);

            int rowsAffected = deleteSongFromPlaylist.executeUpdate();
            return rowsAffected > 0;
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return false;
    }
}
