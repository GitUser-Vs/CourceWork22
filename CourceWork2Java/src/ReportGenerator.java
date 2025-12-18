import java.util.List;
import java.time.format.DateTimeFormatter;

public class ReportGenerator {

    private static final DateTimeFormatter DATE_FORMATTER = DateTimeFormatter.ofPattern("yyyy-MM-dd");

    // Конструкторы
    public ReportGenerator() {
    }

    // Публичные методы
    public void generateBookReport(List<Book> books) {
        System.out.println("\n--- Book Report ---");
        if (books.isEmpty()) {
            System.out.println("No books available in the library.");
            return;
        }
        for (Book book : books) {
            System.out.println("  ID: " + book.getBookId() + ", Title: \"" + book.getTitle() + "\", Author: " + book.getAuthor() + ", Available: " + book.getAvailable() + "/" + book.getQuantity());
        }
        System.out.println("--- End of Book Report ---");
    }

    public void generateUserReport(List<User> users) {
        System.out.println("\n--- User Report ---");
        if (users.isEmpty()) {
            System.out.println("No users registered in the library.");
            return;
        }
        for (User user : users) {
            System.out.println("  ID: " + user.getUserId() + ", Name: " + user.getName() + ", Email: " + user.getEmail() + ", Borrowed: " + user.getBorrowedCount() + "/" + user.getMaxBorrowedCount());
        }
        System.out.println("--- End of User Report ---");
    }

    public void generateTransactionReport(List<Transaction> transactions) {
        System.out.println("\n--- Transaction Report ---");
        if (transactions.isEmpty()) {
            System.out.println("No transactions recorded.");
            return;
        }
        for (Transaction transaction : transactions) {
            System.out.print("  ID: " + transaction.getTransactionId() + ", BookID: " + transaction.getBookId() + ", UserID: " + transaction.getUserId());
            System.out.print(", Issued: " + transaction.getIssueDate().format(DATE_FORMATTER));
            System.out.print(", Due: " + transaction.getDueDate().format(DATE_FORMATTER));
            if (transaction.isReturned()) {
                System.out.print(", Returned: " + transaction.getReturnDate().format(DATE_FORMATTER));
                System.out.printf(", Fine: $%.2f%n", transaction.getFineAmount()); // Форматированный вывод штрафа
            } else {
                System.out.println(", Status: Outstanding");
            }
        }
        System.out.println("--- End of Transaction Report ---");
    }

    // Общий отчет (для демонстрации)
    public void generateGeneralReport(String reportType) {
        System.out.println("\n--- Generating General Report: " + reportType + " ---");
        System.out.println("Report generation process initiated...");
        System.out.println("Report generation complete.");
        System.out.println("--- End of General Report ---");
    }
}