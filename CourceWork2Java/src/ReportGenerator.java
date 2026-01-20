import java.util.List;
import java.util.Optional;

public class ReportGenerator {

    // Constructors
    public ReportGenerator() {
    }

    // Public methods
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
    }
}