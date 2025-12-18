import java.time.LocalDate;
import java.time.format.DateTimeFormatter;

public class Transaction {
    private int transactionId;
    private int bookId; // Storing the Book ID
    private int userId; // Storing the User ID
    private LocalDate issueDate;
    private LocalDate dueDate;
    private LocalDate returnDate; // It can be null if the book has not been returned yet.
    private boolean isReturned;
    private double fineAmount; // Fine if it was accrued

    // Formatter for date output
    private static final DateTimeFormatter DATE_FORMATTER = DateTimeFormatter.ofPattern("yyyy-MM-dd");

    // Constructors
    public Transaction() {
        this.transactionId = 0;
        this.bookId = 0;
        this.userId = 0;
        this.issueDate = LocalDate.now(); // By default, the current date is
        this.dueDate = this.issueDate.plusDays(14); // By default, +14 days
        this.returnDate = null;
        this.isReturned = false;
        this.fineAmount = 0.0;
    }

    public Transaction(int transactionId, int bookId, int userId, LocalDate issueDate, LocalDate dueDate) {
        this.transactionId = transactionId;
        this.bookId = bookId;
        this.userId = userId;
        this.issueDate = issueDate;
        this.dueDate = dueDate;
        this.returnDate = null;
        this.isReturned = false;
        this.fineAmount = 0.0;
    }

    // Public methods
    public void displayInfo() {
    	String status = isReturned ? "Returned" : "Active";
        System.out.printf("  TID: %d | BookID: %d | UserID: %d | Due: %s | Status: %s | Fine: $%.2f%n",
                          transactionId, bookId, userId, dueDate, status, fineAmount);
    }

    public void markAsReturned(LocalDate returnDate, double fine) {
        this.returnDate = returnDate;
        this.fineAmount = fine;
        this.isReturned = true;
    }

    // Getters
    public int getTransactionId() { return transactionId; }
    public int getBookId() { return bookId; }
    public int getUserId() { return userId; }
    public LocalDate getIssueDate() { return issueDate; }
    public LocalDate getDueDate() { return dueDate; }
    public LocalDate getReturnDate() { return returnDate; }
    public boolean isReturned() { return isReturned; }
    public double getFineAmount() { return fineAmount; }
}