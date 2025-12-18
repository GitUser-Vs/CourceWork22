import java.util.Objects; // Для использования Objects.hash, equals

public class User {
	protected int userId;
	protected String name;
    private String email;
    private int borrowedCount;
    private int maxBorrowedCount;

    private static int nextUserId = 1; // Статическое поле для уникальных ID пользователей
    
    // Constructors
    public User() {
    	this(0, "Unknown User", "", 0);
    }

    public User(int userId, String name, String email, int maxBorrowedCount) {
        this.userId = userId = userId == 0 ? nextUserId++ : userId; // Используем статический счетчик, если ID 0;
        this.name = name;
        this.email = email;
        this.borrowedCount = 0;
        this.maxBorrowedCount = (maxBorrowedCount > 0) ? maxBorrowedCount : 1; // Минимум 1 книга
    }
    
    // Статический метод для получения следующего ID
    public static int getNextUserId() {
        return nextUserId++;
    }

    // Public methods
    public void displayInfo() {
    	System.out.println("[Base User] ID: " + this.userId + ", Name: " + this.name +
                ", Borrowed: " + this.borrowedCount + "/" + this.maxBorrowedCount);
    }

    public boolean borrowBook() {
        if (borrowedCount < maxBorrowedCount) {
            borrowedCount++;
            return true;
        }
        throw new IllegalStateException("User '" + this.name + "' (ID: " + this.userId + ") has reached maximum borrowed books.");
    }

    public boolean returnBook() {
        if (borrowedCount > 0) {
            borrowedCount--;
            return true;
        }
        System.out.println("Warning: User '" + this.name + "' has no books to return.");
        return false;
    }
    
 // Демонстрация перегрузки. Вызывается из дочернего класса
    public void printDetails(String prefix) {
        System.out.println(prefix + " | Base User: " + this.name + " (ID: " + this.userId + ")");
    }

    // Getters
    public int getUserId() { return this.userId; }
    public String getName() { return this.name; }
    public String getEmail() { return this.email; }
    public int getBorrowedCount() { return this.borrowedCount; }
    public int getMaxBorrowedCount() { return this.maxBorrowedCount; }
    
 // Переопределение equals и hashCode
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        User user = (User) o;
        return userId == user.userId;
    }

    @Override
    public int hashCode() {
        return Objects.hash(userId);
    }
}