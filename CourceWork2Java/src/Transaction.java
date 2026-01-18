import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.io.Serializable;
import java.time.temporal.ChronoUnit;

public class Transaction implements Serializable{
	private static final long serialVersionUID = 1L;
	
    private int transactionId;
    private int bookId; // Storing the Book ID
    private int userId; // Storing the User ID
    private String borrowDate;
    private String dueDate;
    private String returnDate; // It can be null if the book has not been returned yet.
    private boolean isActive;
    //private double fineAmount; // Fine if it was accrued

    // Formatter for date output
    private static final DateTimeFormatter FORMATTER = DateTimeFormatter.ofPattern("yyyy-MM-dd");

    // Constructors
    public Transaction(int id, int bId, int uId) {
    	LocalDate today = LocalDate.now();
    	
        this.transactionId = 0;
        this.bookId = bId;
        this.userId = uId;
        this.borrowDate = today.format(FORMATTER); // By default, the current date is     
        this.dueDate = today.plus(14, ChronoUnit.DAYS).format(FORMATTER);
        this.returnDate = "N/A";
        this.isActive = true;
        //this.fineAmount = 0.0;
    }

    public Transaction() {
    	this.isActive = false;
    	
//        this.transactionId = transactionId;
//        this.bookId = bookId;
//        this.userId = userId;
//        this.issueDate = issueDate;
//        this.dueDate = dueDate;
//        this.returnDate = null;
//        this.isReturned = false;
//        this.fineAmount = 0.0;
    }

    // Public methods
    public void displayInfo() {
    	System.out.println("TID: " + transactionId + " | BookID: " + bookId 
                + " | UserID: " + userId + " | Выдана: " + borrowDate
                + " | Срок: " + dueDate + " | Статус: " 
                + (isActive ? "Активна" : "Возвращена"));
    }

//    public void markAsReturned(LocalDate returnDate, double fine) {
//        this.returnDate = returnDate;
//        this.fineAmount = fine;
//        this.isReturned = true;
//    }
    
    public void completeTransaction() {
        this.isActive = false;
        this.returnDate = LocalDate.now().format(FORMATTER);
    }

    // Getters
    public int getId() { return transactionId; }
    public int getBookId() { return bookId; }
    public int getUserId() { return userId; }
    //public LocalDate getIssueDate() { return issueDate; }
    public String getDueDate() { return dueDate; }
    //public LocalDate getReturnDate() { return returnDate; }
    public boolean isActiveStatus() { return isActive; }
    //public double getFineAmount() { return fineAmount; }
}