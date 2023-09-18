package negocio;

import java.util.ArrayList;
import java.time.LocalDate;
import java.util.List;

import dados.Artist;
import dados.Song;
import dados.User;

public class PlayerSystem {
	private static List<User> users = new ArrayList<User>();
	private static List<Artist> artists = new ArrayList<Artist>();
	private static List<Song> songs = new ArrayList<Song>();

	public static void main(String[] args) {
		User firstUser = new User("Lucas", "lucas", "12345678");
		addUser(firstUser);

		Artist firstArtist = new Artist("Caio", "Cantor");
		addArtist(firstArtist);

		System.out.println();
		Song firstMusic = new Song("November", LocalDate.of(2023, 9, 15));
		Song secondMusic = new Song("ASAP", LocalDate.of(2023, 7, 21));
		firstMusic.addAuthor(firstArtist);
		secondMusic.addAuthor(firstArtist);

		uploadSong(firstMusic);
		uploadSong(secondMusic);

		listSongs();
		listArtists();

		firstUser.addPlaylist("As melhores");
		firstUser.addSongPlaylist("As melhores", firstMusic);
		firstUser.listPlaylists();
		firstUser.removeSongPlaylist("As melhores", firstMusic);
		firstUser.listPlaylists();
	}

	public static void addUser(User user) {
		for (User existingUser : users) {
			if (existingUser.getUsername().equals(user.getUsername())) {
				System.out.println("User already exists.");
				return;
			}
		}

		System.out.println("Registering user");
		users.add(user);
	}

	public static void uploadSong(Song song) {
		for (Song existingSong : songs) {
			if ((existingSong.getTitle().equals(song.getTitle()))
					&& (existingSong.getRelease().equals(song.getRelease()))) {
				System.out.println("Song already exists.");
				return;
			}
		}

		System.out.println("Registering song");
		songs.add(song);
	}

	public static void addArtist(Artist artist) {
		System.out.println("Adding artist");
		artists.add(artist);
	}

	public static void listSongs() {
		for (Song song : songs) {
			System.out.println("Title: " + song.getTitle() + ", Author(s): " + song.getAuthors());
		}
		System.out.println();
	}

	public static void listArtists() {
		for (Artist artist : artists) {
			System.out.println("Name: " + artist.getName() + ", Songs: " + artist.getTrackList());
		}
		System.out.println();
	}
}
