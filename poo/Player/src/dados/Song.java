package dados;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Objects;
import java.time.Duration;

public class Song {
	private String title;
	private Duration duration;
	private Date release;
	private List<Artist> authors;

	public Song(String title, Date release, Duration duration) {
		this.title = title;
		this.duration = duration;
		this.release = release;
		this.authors = new ArrayList<Artist>();
	}
	
	public void addAuthor(Artist author) {
		authors.add(author);
	}
	
	public void removeAuthor(Artist author) {
		authors.remove(author);
	}

	public String getTitle() {
		return title;
	}

	public void setTitle(String title) {
		this.title = title;
	}

	public Duration getDuration() {
		return duration;
	}

	public void setDuration(Duration duration) {
		this.duration = duration;
	}

	public List<Artist> getAuthors() {
		return authors;
	}

	public Date getRelease() {
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
		return Objects.equals(authors, other.authors) && Objects.equals(duration, other.duration)
				&& Objects.equals(release, other.release) && Objects.equals(title, other.title);
	}

	public String toString() {
		return "Title: " +title+ ", Release Date: " +release+ ", Duration: " +duration+ ", Author(s): " +authors;
	}
}
