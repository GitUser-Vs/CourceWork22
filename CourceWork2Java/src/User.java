public class User {
    private int userId;
    private String name;
    private String email;
    private int borrowedCount;
    private int maxBorrowedCount;

    // Constructors
    public User() {
        this.userId = 0;
        this.name = "Unknown User";
        this.email = "";
        this.borrowedCount = 0;
        this.maxBorrowedCount = 0;
    }

    public User(int userId, String name, String email, int maxBorrowedCount) {
        this.userId = userId;
        this.name = name;
        this.email = email;
        this.borrowedCount = 0;
        this.maxBorrowedCount = maxBorrowedCount;
    }

    // Public methods
    public void displayInfo() {
        System.out.println("User ID: " + userId +
                           ", Name: " + name +
                           ", Email: " + email +
                           ", Borrowed: " + borrowedCount + "/" + maxBorrowedCount);
    }

    public boolean borrowBook() {
        if (borrowedCount < maxBorrowedCount) {
            borrowedCount++;
            return true;
        }
        return false;
    }

    public boolean returnBook() {
        if (borrowedCount > 0) {
            borrowedCount--;
            return true;
        }
        return false;
    }

    // Getters
    public int getUserId() { return userId; }
    public String getName() { return name; }
    public String getEmail() { return email; }
    public int getBorrowedCount() { return borrowedCount; }
    public int getMaxBorrowedCount() { return maxBorrowedCount; }
}