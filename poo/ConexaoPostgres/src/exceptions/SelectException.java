package exceptions;

public class SelectException extends Exception {
    public SelectException() {
        super("Select Exception");
    }

    public SelectException(String message) {
        super(message);
    }
}
