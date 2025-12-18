import java.util.Objects; // Для использования Objects.hash, equals

public class Book implements Cloneable{
    private int bookId;
    private String title;
    private String author;
    private int quantity;
    private int available;

    private static int nextBookId = 1; // Статическое поле для уникальных ID книг
    
    // Constructors
    public Book() {
    	this(0, "Unknown Title", "Unknown Author", 0); // Вызов другого конструктора класса
    }

    public Book(int bookId, String title, String author, int quantity) {
        this.bookId = bookId = bookId == 0 ? nextBookId++ : bookId;
        this.title = title;
        this.author = author;
        this.quantity = quantity;
        this.available = quantity;
    }
    
    public static int getNextBookId() {
        return nextBookId++; // Возвращаем текущее значение и инкрементируем для следующего вызова
    }

    // Public methods
    public void displayInfo() {
    	System.out.println("Book ID: " + this.bookId + ", Title: " + this.title +
                ", Author: " + this.author + ", Available: " + this.available + "/" + this.quantity);
    }

    public void decreaseAvailable() {
        if (available > 0) {
            available--;
        } else {
            // Инициализация исключения
            throw new IllegalStateException("Cannot decrease available quantity below zero for book '" + this.title + "' (ID: " + this.bookId + ")");
        }
    }

    public void increaseAvailable() {
    	if (available < quantity) {
            available++;
        } else {
            // Можно бросить исключение, если попытка увеличить больше, чем есть
            // throw new IllegalStateException("Cannot increase available quantity beyond total quantity for book '" + this.title + "' (ID: " + this.bookId + ")");
            System.out.println("Warning: Available quantity for '" + this.title + "' is already at maximum.");
        }
    }

    // Getters
    public int getBookId() { return this.bookId; }
    public String getTitle() { return this.title; }
    public String getAuthor() { return this.author; }
    public int getQuantity() { return this.quantity; }
    public int getAvailable() { return this.available; }
    
// Реализация клонирования
    
    // Поверхностное клонирование
    @Override
    public Object clone() {
        try {
            // Поверхностное копирование
            return super.clone(); 
        } catch (CloneNotSupportedException e) {
            throw new InternalError(e);
        }
    }
    
    // Глубокое клонирование
    public Book deepClone() {
        // Создаем новый объект и копируем все поля
        Book newBook = new Book(this.bookId, this.title, this.author, this.quantity);
        newBook.available = this.available; // Копируем доступное количество
        return newBook;
    }
    
 // Переопределение equals и hashCode для корректной работы с коллекциями (например, HashSet)
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Book book = (Book) o;
        return bookId == book.bookId; // Считаем книги с одинаковым ID равными
    }

    @Override
    public int hashCode() {
        return Objects.hash(bookId); // Хеш на основе bookId
    }
}