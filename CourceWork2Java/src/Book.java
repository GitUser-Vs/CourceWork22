import java.io.Serializable;

public class Book implements Serializable{
	private static final long serialVersionUID = 1L;
	
    private int bookId;
    private String title;
    private String author;
    private String isbn;
    private String filePath; // The path to the file to read
    private boolean isAvailable;

    private static int nextBookId = 1; // Static field for unique book IDs
    
    // Constructors
    public Book() {
    	this.isAvailable = true;
        this.filePath = "N/A";
    }

    public Book(int id, String t, String a, String i, String path) {
        this.bookId = id;
        this.title = t;
        this.author = a;
        this.isbn = i;
        this.filePath  = path;
        this.isAvailable = true;
    }
    
    public static int getNextBookId() {
        return nextBookId++; // return the current value and increment it for the next call.
    }

    // Public methods
    public void display() {
    	System.out.println("ID: " + bookId + " | Название: " + title 
                + " | Автор: " + author + " | ISBN: " + isbn
                + " | Статус: " + (isAvailable ? "Доступна" : "Выдана"));
    }

    // Getters
    public int getId() { return bookId; }
    public String getTitle() { return title; }
    public String getAuthor() { return author; }
    public String getFilePath() { return filePath; }
    public boolean getAvailable() { return isAvailable; }
    public String getIsbn() { return isbn; }
    
    // Setters
    public void setTitle(String title) { this.title = title; }
    public void setAuthor(String author) { this.author = author; }
    public void setIsbn(String isbn) { this.isbn = isbn; }
    public void setAvailability(boolean status) { isAvailable = status; }
}