package dados;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class User {
	private String name;
	private String username;
	private String password;
	private List<Song> favorites;
	private List<Playlist> playlists;
	
	public User(String name, String username, String password) {
		this.name = name;
		this.username = username;
		this.password = password;
		this.favorites = new ArrayList<Song>();
		this.playlists = new ArrayList<Playlist>();
	}

    public void addSong(Song song) {
        favorites.add(song);
    }
    
    public void removeSong(Song song) {
    	favorites.remove(song);
    }
    
    public void addPlaylist(Playlist playlist) {
    	playlists.add(playlist);
    }
    
    public void removePlaylist(Playlist playlist) {
    	playlists.remove(playlist);
    }

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getUsername() {
		return username;
	}

	public void setUsername(String username) {
		this.username = username;
	}

	public void setPassword(String password) {
		this.password = password;
	}
	
	public String getPassword() {
		return this.password;
	}
	
	public List<Song> getFavorites() {
		return favorites;
	}

	public List<Playlist> getPlaylists() {
		return playlists;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		User other = (User) obj;
		return Objects.equals(username, other.username) && Objects.equals(favorites, other.favorites)
				&& Objects.equals(name, other.name) && Objects.equals(playlists, other.playlists);
	}

	public String toString() {
		return "Name: " +name+ ", Username: " +username+ ", Favorite songs: " +favorites+ ", Playlists: " +playlists;
	}

}
