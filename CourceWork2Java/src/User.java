//import java.util.Objects; // Для использования Objects.hash, equals
import java.io.Serializable;

public class User implements Serializable {
	private static final long serialVersionUID = 1L;
	
	private int userId;
	private String name;
    private String contact;
//    private int borrowedCount;
//    private int maxBorrowedCount;

    //private static int nextUserId = 1; // Статическое поле для уникальных ID пользователей
    
    // Constructors
    public User() {
    	//this(0, "Unknown User", "", 0);
    }

    public User(int id, String n, String c) {
        this.userId = id;
        this.name = n;
        this.contact = c;
//        this.borrowedCount = 0;
//        this.maxBorrowedCount = (maxBorrowedCount > 0) ? maxBorrowedCount : 1; // Минимум 1 книга
    }
    
    // Статический метод для получения следующего ID
//    public static int getNextUserId() {
//        return nextUserId++;
//    }

    // Public methods
    public void display() {
    	System.out.println("User ID: " + userId + " | Имя: " + name 
                + " | Контакт: " + contact);
    }

//    public boolean borrowBook() {
//        if (borrowedCount < maxBorrowedCount) {
//            borrowedCount++;
//            return true;
//        }
//        throw new IllegalStateException("User '" + this.name + "' (ID: " + this.userId + ") has reached maximum borrowed books.");
//    }
//
//    public boolean returnBook() {
//        if (borrowedCount > 0) {
//            borrowedCount--;
//            return true;
//        }
//        System.out.println("Warning: User '" + this.name + "' has no books to return.");
//        return false;
//    }
    
 // Демонстрация перегрузки. Вызывается из дочернего класса
//    public void printDetails(String prefix) {
//        System.out.println(prefix + " | Base User: " + this.name + " (ID: " + this.userId + ")");
//    }

    // Getters
    public int getId() { return userId; }
    public String getName() { return name; }
    
//    public String getEmail() { return this.email; }
//    public int getBorrowedCount() { return this.borrowedCount; }
//    public int getMaxBorrowedCount() { return this.maxBorrowedCount; }
    
 // Переопределение equals и hashCode
//    @Override
//    public boolean equals(Object o) {
//        if (this == o) return true;
//        if (o == null || getClass() != o.getClass()) return false;
//        User user = (User) o;
//        return userId == user.userId;
//    }
//
//    @Override
//    public int hashCode() {
//        return Objects.hash(userId);
//    }
}