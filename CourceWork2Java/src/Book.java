//import java.util.Objects; // Для использования Objects.hash, equals
import java.io.Serializable;

public class Book implements Serializable{
	private static final long serialVersionUID = 1L;
	
    private int bookId;
    private String title;
    private String author;
    private String isbn;
    //private int quantity;
    private String filePath; // Путь к файлу для чтения
    private boolean isAvailable;

    private static int nextBookId = 1; // Статическое поле для уникальных ID книг
    
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
        return nextBookId++; // Возвращаем текущее значение и инкрементируем для следующего вызова
    }

    // Public methods
    public void display() {
    	System.out.println("ID: " + bookId + " | Название: " + title 
                + " | Автор: " + author + " | ISBN: " + isbn
                + " | Статус: " + (isAvailable ? "Доступна" : "Выдана"));
    }

	/*
	 * public void decreaseAvailable() { if (available > 0) { available--; } else {
	 * // Инициализация исключения throw new
	 * IllegalStateException("Cannot decrease available quantity below zero for book '"
	 * + this.title + "' (ID: " + this.bookId + ")"); } }
	 * 
	 * public void increaseAvailable() { if (available < quantity) { available++; }
	 * else { System.out.println("Warning: Available quantity for '" + this.title +
	 * "' is already at maximum."); } }
	 */

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
    
// Реализация клонирования
    
    // Поверхностное клонирование
	/*
	 * @Override public Object clone() { try { // Поверхностное копирование return
	 * super.clone(); } catch (CloneNotSupportedException e) { throw new
	 * InternalError(e); } }
	 * 
	 * // Глубокое клонирование public Book deepClone() { // Создаем новый объект и
	 * копируем все поля Book newBook = new Book(this.bookId, this.title,
	 * this.author, this.quantity); newBook.available = this.available; // Копируем
	 * доступное количество return newBook; }
	 * 
	 * // Переопределение equals и hashCode для корректной работы с коллекциями
	 * (например, HashSet)
	 * 
	 * @Override public boolean equals(Object o) { if (this == o) return true; if (o
	 * == null || getClass() != o.getClass()) return false; Book book = (Book) o;
	 * return bookId == book.bookId; // Считаем книги с одинаковым ID равными }
	 * 
	 * @Override public int hashCode() { return Objects.hash(bookId); // Хеш на
	 * основе bookId }
	 */
}