package dados;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class Artist {
	private String name;
	private String bio;
	private List<String> trackList;

	public Artist(String name, String bio) {
		this.name = name;
		this.bio = bio;
		this.trackList = new ArrayList<String>();
	}

	public void addSong(String song) {
		trackList.add(song);
	}

	public void removeSong(Song song) {
		trackList.remove(song.getTitle());
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getBio() {
		return bio;
	}

	public void setBio(String bio) {
		this.bio = bio;
	}

	public List<String> getTrackList() {
		return trackList;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Artist other = (Artist) obj;
		return Objects.equals(bio, other.bio) && Objects.equals(name, other.name)
				&& Objects.equals(trackList, other.trackList);
	}

	public String toString() {
		return "Name: " + name + ", Bio: " + bio + ", trackList: " + trackList;
	}
}
