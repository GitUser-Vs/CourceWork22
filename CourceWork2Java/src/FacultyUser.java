public class FacultyUser extends User {
    private String department;

    public FacultyUser(String name, String email, int maxBooks, String department) {
        super(0, name, email, maxBooks); // Faculty может брать больше книг
        this.department = department;
    }

    // Переопределение (Полиморфизм/Виртуальная функция)
    @Override
    public void displayInfo() {
        System.out.println("[Faculty User] ID: " + this.userId + ", Name: " + super.getName() +
                           ", Department: " + this.department +
                           ", Borrowed: " + super.getBorrowedCount() + "/" + super.getMaxBorrowedCount());
    }

}