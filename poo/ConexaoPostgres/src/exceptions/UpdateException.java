package exceptions;

public class UpdateException extends Exception {
    public UpdateException() {
        super("Update Exception");
    }

    public UpdateException(String message) {
        super(message);
    }
}
