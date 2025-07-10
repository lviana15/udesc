package exceptions;

public class DeleteException extends Exception {
    public DeleteException() {
        super("Delete Exception");
    }

    public DeleteException(String message) {
        super(message);
    }
}
