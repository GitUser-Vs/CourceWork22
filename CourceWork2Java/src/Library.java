import java.time.LocalDate;
import java.time.temporal.ChronoUnit;
import java.util.ArrayList;

public class Library {
    private String name;
    private String address;

    private ArrayList<Book> books;
    private ArrayList<User> users;
    private ArrayList<Transaction> transactions; // New list for transactions

    // Aggregated objects
    private FineCalculator fineCalculator;
    private SearchEngine searchEngine;
    private ReportGenerator reportGenerator;

    // Constructors
    public Library() {
        this.name = "Unknown Library";
        this.address = "Unknown Address";
        this.books = new ArrayList<>();
        this.users = new ArrayList<>();
        this.transactions = new ArrayList<>();

        this.fineCalculator = new FineCalculator();
        this.searchEngine = new SearchEngine();
        this.reportGenerator = new ReportGenerator();
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
        books.add(book); // Adding a link to the object
        System.out.println("Added book to library: '" + book.getTitle() + "'");
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
        users.add(user); // Adding a link to the object
        System.out.println("Added user to library: '" + user.getName() + "'");
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
    private int nextTransactionId = 1; // A simple ID generator for transactions

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

        if (book != null && user != null) {
            if (user.borrowBook()) {
                book.decreaseAvailable();
                System.out.println("Lending successful. Book '" + book.getTitle() + "' lent to '" + user.getName() + "'.");

                // Creating a new transaction for this issue
                LocalDate issueDate = LocalDate.now();
                LocalDate dueDate = issueDate.plusDays(14); // Calculation of the DueDate (for example, +14 days)

                Transaction newTransaction = new Transaction(nextTransactionId++, bookId, userId, issueDate, dueDate);
                addTransaction(newTransaction); // Adding a transaction to the system
            } else {
                System.out.println("Lending failed. User '" + user.getName() + "' has reached maximum borrowed books.");
            }
        } else {
            if (book == null) System.out.println("Lending failed. Book with ID " + bookId + " not found.");
            if (user == null) System.out.println("Lending failed. User with ID " + userId + " not found.");
        }
    }

    public void processReturn(int bookId, int userId) {
        System.out.println("\nProcessing return for Book ID " + bookId + " by User ID " + userId + "...");
        Book book = findBookById(bookId);
        User user = findUserById(userId);

        if (book != null && user != null) {
            Transaction activeTransaction = findActiveTransactionByBookUser(bookId, userId); // We find an active transaction

            if (activeTransaction != null) {
                LocalDate returnDate = LocalDate.now();
                double fine = 0.0;

                // Calculation of the fine if there is a delay
                if (returnDate.isAfter(activeTransaction.getDueDate())) {
                    long daysOverdue = ChronoUnit.DAYS.between(activeTransaction.getDueDate(), returnDate);
                    fine = fineCalculator.calculateFine((int) daysOverdue);
                }

                activeTransaction.markAsReturned(returnDate, fine); // Updating the transaction
                book.increaseAvailable();
                System.out.println("Return successful. Book '" + book.getTitle() + "' returned by '" + user.getName() + "'.");
                if (fine > 0) {
                    System.out.println("  Fine incurred: $" + String.format("%.2f", fine));
                }
                user.returnBook(); // Updating the tag in User
            } else {
                System.out.println("Return failed. No active lending transaction found for Book ID " + bookId + " and User ID " + userId + ".");
            }
        } else {
            if (book == null) System.out.println("Return failed. Book with ID " + bookId + " not found.");
            if (user == null) System.out.println("Return failed. User with ID " + userId + " not found.");
        }
    }

    public void performSearch(String query) {
        System.out.println("\nPerforming search in Library...");
        // Delegating the call to the aggregated SearchEngine object
        searchEngine.searchBooks(query);
        searchEngine.searchUsers(query);
    }

    public void generateLibraryReport() {
        System.out.println("\nGenerating report for Library...");
        // Delegating the call to the aggregated ReportGenerator object
        reportGenerator.generate("Library Overview");
    }
}