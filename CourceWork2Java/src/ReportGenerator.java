import java.util.List;
//import java.time.format.DateTimeFormatter;
import java.util.Optional;

public class ReportGenerator {

    //private static final DateTimeFormatter DATE_FORMATTER = DateTimeFormatter.ofPattern("yyyy-MM-dd");

    // Конструкторы
    public ReportGenerator() {
    }

    // Публичные методы
    public void generateActiveLoansReport(List<Transaction> transactions, 
            List<User> users, List<Book> books) {
        System.out.println("\n--- ОТЧЕТ ОБ АКТИВНЫХ ВЫДАЧАХ ---");
        boolean found = false;
        for (Transaction t : transactions) {
        	if (t.isActiveStatus()) {
        		found = true;
        		System.out.println("Транзакция ID: " + t.getId());
        		
        		Optional<User> userOpt = users.stream().filter(u -> u.getId() == t.getUserId()).findFirst();

				userOpt.ifPresent(user -> System.out.println("  Пользователь: " + user.getName() + " (ID: " + t.getUserId() + ")"));
				
				Optional<Book> bookOpt = books.stream().filter(b -> b.getId() == t.getBookId()).findFirst();
				
				bookOpt.ifPresent(book -> {
				    System.out.println("  Книга: " + book.getTitle() + " (ID: " + t.getBookId() + ")");
				    System.out.println("  Срок возврата: " + t.getDueDate());
				});
				System.out.println("-----------------------------------");
        	}
        }
        if (!found) {
            System.out.println("Активных выданных книг нет.");
        }
        //System.out.println("--- End of Book Report ---");
    }

//    public void generateUserReport(List<User> users) {
//        System.out.println("\n--- User Report ---");
//        if (users.isEmpty()) {
//            System.out.println("No users registered in the library.");
//            return;
//        }
//        for (User user : users) {
//            System.out.println("  ID: " + user.getUserId() + ", Name: " + user.getName() + ", Email: " + user.getEmail() + ", Borrowed: " + user.getBorrowedCount() + "/" + user.getMaxBorrowedCount());
//        }
//        System.out.println("--- End of User Report ---");
//    }
//
//    public void generateTransactionReport(List<Transaction> transactions) {
//        System.out.println("\n--- Transaction Report ---");
//        if (transactions.isEmpty()) {
//            System.out.println("No transactions recorded.");
//            return;
//        }
//        for (Transaction transaction : transactions) {
//            System.out.print("  ID: " + transaction.getTransactionId() + ", BookID: " + transaction.getBookId() + ", UserID: " + transaction.getUserId());
//            System.out.print(", Issued: " + transaction.getIssueDate().format(DATE_FORMATTER));
//            System.out.print(", Due: " + transaction.getDueDate().format(DATE_FORMATTER));
//            if (transaction.isReturned()) {
//                System.out.print(", Returned: " + transaction.getReturnDate().format(DATE_FORMATTER));
//                System.out.printf(", Fine: $%.2f%n", transaction.getFineAmount()); // Форматированный вывод штрафа
//            } else {
//                System.out.println(", Status: Outstanding");
//            }
//        }
//        System.out.println("--- End of Transaction Report ---");
//    }
//
//    // Общий отчет (для демонстрации)
//    public void generateGeneralReport(String reportType) {
//        System.out.println("\n--- Generating General Report: " + reportType + " ---");
//        System.out.println("Report generation process initiated...");
//        System.out.println("Report generation complete.");
//        System.out.println("--- End of General Report ---");
//    }
}