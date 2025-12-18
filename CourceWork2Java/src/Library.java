import java.time.LocalDate;
import java.time.temporal.ChronoUnit;
import java.util.ArrayList;
import java.util.List; // Для использования List

public class Library {
    private String name;
    private String address;

    private ArrayList<Book> books;
    private ArrayList<User> users;
    private ArrayList<Transaction> transactions; // New list for transactions

    private static int nextTransactionId = 1; // Статическое поле для уникальных ID транзакций
    
    // Aggregated objects
    private FineCalculator fineCalculator;
    private SearchEngine searchEngine;
    private ReportGenerator reportGenerator;

    // Constructors
    public Library() {
    	this("Unknown Library", "Unknown Address");
    }

    public Library(String name, String address) {
        this.name = name;
        this.address = address;
        this.books = new ArrayList<>();
        this.users = new ArrayList<>();
        this.transactions = new ArrayList<>();

        this.fineCalculator = new FineCalculator(0.75); // Example with the parameter
        this.searchEngine = new SearchEngine();
        this.reportGenerator = new ReportGenerator();
    }

    // Public methods
    public void displayLibraryInfo() {
        System.out.println("Library Name: " + name +
                           ", Address: " + address);
        System.out.println("Current books: " + books.size());
        System.out.println("Current users: " + users.size());
        System.out.println("Current transactions: " + transactions.size());
    }

    // Methods for working with books
    public void addBook(Book book) {
    	try {
            if (book == null) {
                throw new IllegalArgumentException("Cannot add a null book to the library.");
            }
            // Проверка на дубликат по ID (требует equals/hashCode в Book)
            for (Book existingBook : books) {
                if (existingBook.equals(book)) {
                    throw new IllegalArgumentException("Book with ID " + book.getBookId() + " already exists.");
                }
            }
            books.add(book);
            System.out.println("Added book to library: '" + book.getTitle() + "'");
        } catch (IllegalArgumentException e) {
            System.err.println("Error adding book: " + e.getMessage());
        }
    }

    public void displayBooks() {
        System.out.println("\n--- Books in Library ---");
        if (books.isEmpty()) {
            System.out.println("No books in the library yet.");
            return;
        }
        for (Book book : books) { // Using enhanced for loop
            book.displayInfo();
        }
        System.out.println("------------------------");
    }

    public Book findBookById(int bookId) {
        for (Book book : books) {
            if (book.getBookId() == bookId) {
                return book; // Returning the link to the object
            }
        }
        return null; // The book was not found
    }

    // Methods for working with users
    public void addUser(User user) {
    	try {
            if (user == null) {
                throw new IllegalArgumentException("Cannot add a null user to the library.");
            }
             for (User existingUser : users) {
                if (existingUser.equals(user)) {
                    throw new IllegalArgumentException("User with ID " + user.getUserId() + " already exists.");
                }
            }
            users.add(user);
            System.out.println("Added user to library: '" + user.getName() + "'");
        } catch (IllegalArgumentException e) {
            System.err.println("Error adding user: " + e.getMessage());
        }
    }

    public void displayUsers() {
        System.out.println("\n--- Users in Library ---");
        if (users.isEmpty()) {
            System.out.println("No users in the library yet.");
            return;
        }
        for (User user : users) {
            user.displayInfo();
        }
        System.out.println("------------------------");
    }

    public User findUserById(int userId) {
        for (User user : users) {
            if (user.getUserId() == userId) {
                return user; // Returning the link to the object
            }
        }
        return null; // The user is not found
    }

    // Methods for working with transactions
    //private int nextTransactionId = 1; // A simple ID generator for transactions

    public void addTransaction(Transaction transaction) {
        transactions.add(transaction); // Adding a link to the object
        System.out.println("Added transaction to library system.");
    }

    public void displayTransactions() {
        System.out.println("\n--- Transactions in Library ---");
        if (transactions.isEmpty()) {
            System.out.println("No transactions recorded yet.");
            return;
        }
        for (Transaction transaction : transactions) {
            transaction.displayInfo();
        }
        System.out.println("-------------------------------");
    }

    // Search for the last active transaction for a given workbook and user
    public Transaction findActiveTransactionByBookUser(int bookId, int userId) {
        Transaction lastActiveTransaction = null;
        for (Transaction transaction : transactions) {
            if (transaction.getBookId() == bookId &&
                transaction.getUserId() == userId &&
                !transaction.isReturned()) {
                // If we find an unreturned transaction, we save the link
                lastActiveTransaction = transaction;
            }
        }
        return lastActiveTransaction; // Returns null if nothing is found.
    }

    public void processLending(int bookId, int userId) {
        System.out.println("\nProcessing lending for Book ID " + bookId + " to User ID " + userId + "...");
        Book book = findBookById(bookId);
        User user = findUserById(userId);
        
        if (book == null) {
            System.out.println("Lending failed. Book with ID " + bookId + " not found.");
            return;
        }

        if (user == null) {
            System.out.println("Lending failed. User with ID " + userId + " not found.");
            return;
        }

        if (user.borrowBook()) {
            book.decreaseAvailable();
            System.out.println("Lending successful. Book '" + book.getTitle() + "' lent to '" + user.getName() + "'.");

            // Creating a new transaction for this issue
            LocalDate issueDate = LocalDate.now();
            LocalDate dueDate = issueDate.plusDays(14);

            Transaction newTransaction = new Transaction(nextTransactionId++, bookId, userId, issueDate, dueDate);
            addTransaction(newTransaction);
        } else {
            System.out.println("Lending failed. User '" + user.getName() + "' has reached maximum borrowed books.");
        }
    }

    public void processReturn(int bookId, int userId) {
        System.out.println("\nProcessing return for Book ID " + bookId + " by User ID " + userId + "...");
        Book book = findBookById(bookId);
        User user = findUserById(userId);

        if (book == null) {
            System.out.println("Return failed. Book with ID " + bookId + " not found.");
            return;
        }

        if (user == null) {
            System.out.println("Return failed. User with ID " + userId + " not found.");
            return;
        }

        Transaction activeTransaction = findActiveTransactionByBookUser(bookId, userId);

        if (activeTransaction == null) {
            System.out.println("Return failed. No active lending transaction found for Book ID " + bookId + " and User ID " + userId + ".");
            return;
        }

        LocalDate returnDate = LocalDate.now();
        // Используем FineCalculator для расчета штрафа
        double fine = fineCalculator.calculateFine(activeTransaction.getDueDate(), returnDate);

        activeTransaction.markAsReturned(returnDate, fine);
        book.increaseAvailable();
        System.out.println("Return successful. Book '" + book.getTitle() + "' returned by '" + user.getName() + "'.");
        if (fine > 0) {
            System.out.println("  Fine incurred: $" + String.format("%.2f", fine));
        }
        user.returnBook(); // Может бросить исключение, если нечего возвращать
    }

 // Используем SearchEngine более эффективно
    public List<Book> searchBooks(String query) {
        System.out.println("\nPerforming book search in Library...");
        return searchEngine.searchBooksByTitle(this.books, query); // Передаем весь список книг
    }

    public List<User> searchUsers(String query) {
        System.out.println("\nPerforming user search in Library...");
        return searchEngine.searchUsersByName(this.users, query); // Передаем весь список пользователей
    }

    // Используем ReportGenerator для генерации конкретных отчетов
    public void generateBookReport() {
        reportGenerator.generateBookReport(this.books);
    }

    public void generateUserReport() {
        reportGenerator.generateUserReport(this.users);
    }

    public void generateTransactionReport() {
        reportGenerator.generateTransactionReport(this.transactions);
    }

    // Общий отчет (как демонстрация)
    public void generateGeneralReport(String reportType) {
        reportGenerator.generateGeneralReport(reportType);
    }
}