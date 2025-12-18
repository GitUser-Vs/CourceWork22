public class StudentUser extends User {
    private String studentId; // Дополнительное поле

    public StudentUser(String name, String email, int maxBooks, String studentId) {
        // Вызываем конструктор родителя. Protected поле userId будет инициализировано.
        super(0, name, email, maxBooks);
        this.studentId = studentId;
    }
    
    // 2) Доступ к protected полю родителя
    public void checkProtectedId() {
        System.out.println("Student " + this.name + " checking protected ID: " + this.userId);
    }

    // 4) Переопределение (Полиморфизм/Виртуальная функция)
    @Override
    public void displayInfo() {
        System.out.println("[Student User] ID: " + this.userId + ", Name: " + super.getName() +
                           ", Max Books: " + super.getMaxBorrowedCount() +
                           ", Student ID: " + this.studentId +
                           ", Borrowed: " + super.getBorrowedCount());
    }
    
    // 3) Перегрузка (Overloading) базового метода printDetails
    public void printDetails(String prefix, String suffix) {
        super.printDetails(prefix); // Вызов метода базового класса
        System.out.println(prefix + " | Student Suffix: " + suffix + " (StudentID: " + this.studentId + ")");
    }
}