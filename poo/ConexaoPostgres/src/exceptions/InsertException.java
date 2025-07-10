package exceptions;

public class InsertException extends Exception {
    public InsertException() {
        super("Insert exception");
    }

    public InsertException(String message) {
        super(message);
    }

}
