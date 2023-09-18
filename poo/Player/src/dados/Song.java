package dados;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Objects;
import java.time.Duration;
import java.time.LocalDate;

public class Song {
	private String title;
	// private Stream songStream;
	private LocalDate release;
	private List<String> authors;

	public Song(String title, LocalDate date) {
		this.title = title;
		this.release = date;
		this.authors = new ArrayList<String>();
	}

	// TODO: Play song method

	public void addAuthor(Artist author) {
		author.addSong(this.title);
		authors.add(author.getName());
	}

	public void removeAuthor(String author) {
		authors.remove(author);
	}

	public String getTitle() {
		return title;
	}

	public void setTitle(String title) {
		this.title = title;
	}

	public List<String> getAuthors() {
		return authors;
	}

	public LocalDate getRelease() {
		return release;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Song other = (Song) obj;
		return Objects.equals(authors, other.authors) && Objects.equals(release, other.release)
				&& Objects.equals(title, other.title);
	}

	public String toString() {
		return "Title: " + title + ", Release Date: " + release + ", Author(s): " + authors;
	}
}
