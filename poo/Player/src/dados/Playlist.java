package dados;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class Playlist {
	private String name;
	private List<Song> songs;
	
	public Playlist(String name) {
		this.name = name;
		this.songs = new ArrayList<Song>();
	}

    public void addSong(Song song) {
        songs.add(song);
    }

    public void removeSong(Song song) {
        songs.remove(song);
    }

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public List<Song> getSongs() {
		return songs;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Playlist other = (Playlist) obj;
		return Objects.equals(name, other.name) && Objects.equals(songs, other.songs);
	}

	public String toString() {
		return "Name: " +name+ ", Songs: " +songs;
	}
}
