import java.time.LocalDate;
import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
//import java.util.Comparator;
//import java.util.HashMap;
import java.util.List;
import java.util.Optional;
import java.util.Scanner;

public class Library {
	private List<Book> books = new ArrayList<>();
    private List<User> users = new ArrayList<>();
    private List<Transaction> transactions = new ArrayList<>();
    private List<Account> accounts = new ArrayList<>();
    
    private SearchEngine searchEngine = new SearchEngine();
    private ReportGenerator reportGenerator = new ReportGenerator();
    private FineCalculator fineCalculator = new FineCalculator();
    
    private Scanner scanner;
    
    private int nextBookId = 1;
    private int nextUserId = 1;
    private int nextTransactionId = 1;

    private static final String BOOK_FILE = "books.txt";
    private static final String USER_FILE = "users.txt";
    private static final String TRANSACTION_FILE = "transactions.txt";
    private static final String ACCOUNT_FILE = "accounts.txt";

    // --- Session Management ---
    private String activeUser = null;
    private Role activeRole = null;
    private int activeUserId = 0;

    public Library() {
    	this.scanner = new Scanner(System.in);
        loadAllData();
    }
    
    private <T extends Serializable> List<T> loadData(String filename) {
        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(filename))) {
            return (List<T>) ois.readObject();
        } catch (FileNotFoundException e) {
            System.out.println("Файл данных " + filename + " не найден. Начинаем с нуля.");
            return new ArrayList<>();
        } catch (IOException | ClassNotFoundException e) {
            System.err.println("Ошибка при загрузке данных из " + filename + ": " + e.getMessage());
            return new ArrayList<>();
        }
    }

    private void saveData(String filename, List<?> data) {
        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(filename))) {
            oos.writeObject(data);
        } catch (IOException e) {
            System.err.println("Ошибка при сохранении данных в " + filename + ": " + e.getMessage());
        }
    }
    
    private void loadAllData() {
        this.books = loadData(BOOK_FILE);
        this.users = loadData(USER_FILE);
        this.transactions = loadData(TRANSACTION_FILE);
        this.accounts = loadData(ACCOUNT_FILE);
        
        // Инициализация следующих ID (упрощено: берем max + 1)
        // В реальной системе это должно быть надежнее
        if (!books.isEmpty()) nextBookId = books.stream().mapToInt(Book::getId).max().getAsInt() + 1;
        if (!users.isEmpty()) nextUserId = users.stream().mapToInt(User::getId).max().getAsInt() + 1;
        if (!transactions.isEmpty()) nextTransactionId = transactions.stream().mapToInt(Transaction::getId).max().getAsInt() + 1;
    }
    
    public void saveAllData() {
        saveData(BOOK_FILE, books);
        saveData(USER_FILE, users);
        saveData(TRANSACTION_FILE, transactions);
        saveData(ACCOUNT_FILE, accounts);
        System.out.println("\n[СИСТЕМА] Данные сохранены.");
    }

    // Public methods
//    public void displayLibraryInfo() {
//        System.out.println("Library Name: " + name +
//                           ", Address: " + address);
//        System.out.println("Current books: " + books.size());
//        System.out.println("Current users: " + users.size());
//        System.out.println("Current transactions: " + transactions.size());
//    }

    // Methods for working with books
 // --- Вспомогательные методы поиска ---
    private Book findBook(int id) {
        return books.stream().filter(b -> b.getId() == id).findFirst().orElse(null);
    }
    private User findUser(int id) {
        return users.stream().filter(u -> u.getId() == id).findFirst().orElse(null);
    }
    private Account findAccount(String username) {
        return accounts.stream().filter(a -> a.getUsername().equals(username)).findFirst().orElse(null);
    }
    
    // --- Аутентификация ---

    public boolean registerUser() {
        System.out.println("--- РЕГИСТРАЦИЯ (Роль по умолчанию: USER) ---");
        System.out.print("Введите желаемый логин: "); 
        String username = scanner.nextLine();
        
        if (findAccount(username) != null) {
            System.out.println("Ошибка: Логин уже занят.");
            return false;
        }

        System.out.print("Введите пароль: "); 
        String password = scanner.nextLine();

        users.add(new User(nextUserId++, username, "N/A"));
        int newUserId = users.get(users.size() - 1).getId();

        accounts.add(new Account(username, password, Role.USER, newUserId));
        
        System.out.println("Регистрация успешна! Ваш User ID: " + newUserId);
        return true;
    }
    
    public boolean login(String username, String password) {
        Account acc = findAccount(username);

        if (acc == null || !acc.getPassword().equals(password)) {
            System.out.println("Ошибка: Логин или пароль неверны.");
            return false;
        }

        this.activeUser = acc.getUsername();
        this.activeRole = acc.getRole();
        this.activeUserId = acc.getAssociatedId();
        
        System.out.println("Вход успешен. Роль: " + this.activeRole);
        return true;
    }
    
    // Геттеры для сессии
    public Role getActiveRole() { return activeRole; }
    public String getActiveUser() { return activeUser; }
    public int getActiveUserId() { return activeUserId; }

    // --- CRUD / Операции ---

    public void addBook(boolean isDigital) {
    	System.out.println("\n--- ДОБАВЛЕНИЕ НОВОЙ КНИГИ ---");
        System.out.print("Введите название: "); String title = scanner.nextLine();
        System.out.print("Введите автора: "); String author = scanner.nextLine();
        System.out.print("Введите ISBN: "); String isbn = scanner.nextLine();
        
        String path = "N/A";
        if (isDigital) {
            System.out.print("Введите полный путь к файлу книги (например, C:\\\\eBooks\\\\book.pdf): "); 
            path = scanner.nextLine();
        }

        books.add(new Book(nextBookId++, title, author, isbn, path));
        System.out.println("Книга добавлена с ID: " + books.get(books.size() - 1).getId());
    }
    
    public void addUser() {
        System.out.println("\n--- ДОБАВЛЕНИЕ НОВОГО ПОЛЬЗОВАТЕЛЯ ---");
        System.out.print("Введите имя пользователя: ");
        String name = scanner.nextLine();
        
        // Контакт задается вручную или "N/A"
        System.out.print("Введите контактную информацию (email/телефон, или Enter для пропуска): ");
        String contact = scanner.nextLine();
        if (contact.trim().isEmpty()) {
            contact = "N/A";
        }

        users.add(new User(nextUserId++, name, contact));
        System.out.println("Пользователь успешно добавлен. User ID: " + users.get(users.size() - 1).getId());
    }
    
    public void updateBook() {
        System.out.println("\n--- ОБНОВЛЕНИЕ ИНФОРМАЦИИ О КНИГЕ ---");
        System.out.print("Введите ID книги для обновления: ");
        
        try {
            int id = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            Book bookToUpdate = findBook(id);
            if (bookToUpdate == null) {
                System.out.println("Ошибка: Книга с ID " + id + " не найдена.");
                return;
            }

            System.out.println("Текущее название: " + bookToUpdate.getTitle());
            System.out.print("Новое название (Enter для пропуска): "); 
            String newTitle = scanner.nextLine();
            if (!newTitle.isEmpty()) {
                System.out.println("Название обновлено.");
            }
            
            System.out.println("Текущий автор: " + bookToUpdate.getAuthor());
            System.out.print("Новый автор (Enter для пропуска): "); 
            String newAuthor = scanner.nextLine();
            if (!newAuthor.isEmpty()) {
                // bookToUpdate.setAuthor(newAuthor);
                System.out.println("Автор обновлен.");
            }
            
            System.out.println("Текущий ISBN: " + bookToUpdate.getIsbn());
            System.out.print("Новый ISBN (Enter для пропуска): "); 
            String newIsbn = scanner.nextLine();
            if (!newIsbn.isEmpty()) {
                // bookToUpdate.setIsbn(newIsbn);
                System.out.println("ISBN обновлен.");
            }

            System.out.println("Информация о книге ID " + id + " обновлена.");

        } catch (Exception e) {
            System.out.println("Некорректный ввод ID.");
            scanner.nextLine();
        }
    }
    
    public void borrowBook() {
        System.out.print("Введите ID пользователя: "); int uId = scanner.nextInt(); scanner.nextLine();
        System.out.print("Введите ID книги для выдачи: "); int bId = scanner.nextInt(); scanner.nextLine();
        
        User user = findUser(uId);
        Book book = findBook(bId);

        if (user == null) { System.out.println("Ошибка: Пользователь не найден."); return; }
        if (book == null || !book.getAvailable()) { System.out.println("Ошибка: Книга не найдена или выдана."); return; }

        transactions.add(new Transaction(nextTransactionId++, bId, uId));
        book.setAvailability(false);
        System.out.println("Книга '" + book.getTitle() + "' выдана.");
    }

    public void returnBook() {
        System.out.print("Введите ID книги, которую возвращают: "); int bId = scanner.nextInt(); scanner.nextLine();

        Book book = findBook(bId);
        if (book == null) { System.out.println("Ошибка: Книга не найдена."); return; }
        
        Transaction activeT = transactions.stream()
            .filter(t -> t.getBookId() == bId && t.isActiveStatus())
            .findFirst().orElse(null);

        if (activeT == null) { System.out.println("Ошибка: Активная запись о выдаче не найдена."); return; }

        book.setAvailability(true);
        activeT.completeTransaction();
        
        double fine = fineCalculator.calculateFine(activeT);
        System.out.println("Книга '" + book.getTitle() + "' успешно возвращена.");
        if (fine > 0) {
            System.out.println("!!! Начислен штраф: " + fine + " у.е. за просрочку.");
        }
    }

    public void viewMyBooks() {
        System.out.println("\n--- МОИ ВЫДАННЫЕ КНИГИ ---");
        boolean found = false;
        
        for (Transaction t : transactions) {
            if (t.getUserId() == activeUserId && t.isActiveStatus()) {
                found = true;
                Book book = findBook(t.getBookId());
                
                if (book != null) {
                    System.out.print("[" + book.getId() + "] " + book.getTitle() 
                         + " (Срок: " + t.getDueDate() + ")");
                    
                    if (!book.getFilePath().equals("N/A")) {
                        System.out.print(" [ДОСТУПНО ЧТЕНИЕ]");
                    }
                    System.out.println();
                }
            }
        }
        if (!found) {
            System.out.println("У вас нет активных выданных книг.");
            return;
        }

        System.out.print("\nВведите ID книги, которую хотите прочитать (или 0 для выхода): "); 
        int choiceId = scanner.nextInt(); scanner.nextLine();

        if (choiceId != 0) {
            Book targetBook = findBook(choiceId);
            if (targetBook != null && !targetBook.getFilePath().equals("N/A")) {
                // Эмуляция открытия файла
                SystemHelper.openFile(targetBook.getFilePath());
            } else {
                System.out.println("Книга не найдена или цифровая копия недоступна.");
            }
        }
    }
    
    public void displayAllBooks() {
        System.out.println("\n--- СПИСОК ВСЕХ КНИГ ---");
        if (books.isEmpty()) {
            System.out.println("В библиотеке нет книг.");
            return;
        }
        books.forEach(Book::display);
    }
    
    public void displayAllUsers() {
        System.out.println("\n--- СПИСОК ВСЕХ ПОЛЬЗОВАТЕЛЕЙ ---");
        if (users.isEmpty()) {
            System.out.println("Пользователи не зарегистрированы.");
            return;
        }
        users.forEach(User::display);
    }
    
    public void displayAllTransactions() {
        System.out.println("\n--- ВСЕ ТРАНЗАКЦИИ ---");
        if (transactions.isEmpty()) {
            System.out.println("Транзакции отсутствуют.");
            return;
        }
        transactions.forEach(Transaction::displayInfo);
    }
    
    public void searchMenu() {
        System.out.println("\n--- МЕНЮ ПОИСКА ---");
        System.out.println("1. Поиск по названию");
        System.out.println("2. Поиск по автору");
        System.out.print("Ваш выбор: ");
        
        try {
            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline
            
            System.out.print("Введите поисковый запрос: ");
            String query = scanner.nextLine();
            
            List<Book> results = new ArrayList<>();

            switch (choice) {
                case 1:
                    results = searchEngine.searchByTitle(books, query);
                    break;
                case 2:
                    results = searchEngine.searchByAuthor(books, query);
                    break;
                default:
                    System.out.println("Неверный выбор.");
                    return;
            }
            
            System.out.println("\n--- РЕЗУЛЬТАТЫ ПОИСКА (" + results.size() + ") ---");
            if (results.isEmpty()) {
                System.out.println("Ничего не найдено.");
            } else {
                results.forEach(Book::display);
            }

        } catch (Exception e) {
            System.out.println("Некорректный ввод.");
            scanner.nextLine(); 
        }
    }
    
    public void generateReports() {
        System.out.println("\n--- ГЕНЕРАЦИЯ ОТЧЕТОВ ---");
        System.out.println("1. Отчет об активных выдачах");
        System.out.println("2. Отчет о штрафах (по активным выданным)");
        System.out.print("Ваш выбор: ");

        try {
            int choice = scanner.nextInt();
            scanner.nextLine(); 

            switch (choice) {
                case 1:
                    reportGenerator.generateActiveLoansReport(transactions, users, books);
                    break;
                case 2:
                    generateFineReport();
                    break;
                default:
                    System.out.println("Неверный выбор.");
            }
        } catch (Exception e) {
            System.out.println("Некорректный ввод.");
            scanner.nextLine(); 
        }
    }

    private void generateFineReport() {
        System.out.println("\n--- ОТЧЕТ О ШТРАФАХ ---");
        boolean foundFine = false;
        
        for (Transaction t : transactions) {
            if (t.isActiveStatus()) {
                double fine = fineCalculator.calculateFine(t);
                if (fine > 0) {
                    foundFine = true;
                    
                    User u = findUser(t.getUserId());
                    Book b = findBook(t.getBookId());
                    
                    String userName = (u != null) ? u.getName() : "ID " + t.getUserId() + " (Не найден)";
                    String bookTitle = (b != null) ? b.getTitle() : "ID " + t.getBookId() + " (Не найден)";
                    
                    System.out.printf("Пользователь: %s | Книга: %s | Штраф: %.2f\n", userName, bookTitle, fine);
                }
            }
        }
        
        if (!foundFine) {
            System.out.println("На данный момент штрафов нет.");
        }
    }
}