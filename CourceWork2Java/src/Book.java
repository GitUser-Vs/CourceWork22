public class Book {
    private int bookId;
    private String title;
    private String author;
    private int quantity;
    private int available;

    // Constructors
    public Book() {
        this.bookId = 0;
        this.title = "Unknown Title";
        this.author = "Unknown Author";
        this.quantity = 0;
        this.available = 0;
    }

    public Book(int bookId, String title, String author, int quantity) {
        this.bookId = bookId;
        this.title = title;
        this.author = author;
        this.quantity = quantity;
        this.available = quantity;
    }

    // Public methods
    public void displayInfo() {
        System.out.println("Book ID: " + bookId +
                           ", Title: " + title +
                           ", Author: " + author +
                           ", Quantity: " + quantity +
                           ", Available: " + available);
    }

    public void decreaseAvailable() {
        if (available > 0) {
            available--;
        }
    }

    public void increaseAvailable() {
        if (available < quantity) {
            available++;
        }
    }

    // Getters
    public int getBookId() { return bookId; }
    public String getTitle() { return title; }
    public String getAuthor() { return author; }
    public int getQuantity() { return quantity; }
    public int getAvailable() { return available; }
}