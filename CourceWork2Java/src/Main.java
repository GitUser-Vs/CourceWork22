import java.time.LocalDate;
import java.time.temporal.ChronoUnit;
import java.util.List;
import java.io.IOException;
import java.util.Scanner;

public class Main {
	
	private static Library library = new Library();
    private static Scanner scanner = new Scanner(System.in);
    
    private static String activeUser = null;
    private static Role activeRole = null;
    private static int activeUserId = 0;
    
    public static void main(String[] args) {
        // Initialization (automatically downloads data)
        
        while (true) {
            if (activeUser == null) {
                authMenu();
            } else {
                mainMenu();
            }
        }
    }

    private static void authMenu() {
        System.out.println("\n--- АВТОРИЗАЦИЯ ---");
        System.out.println("1. Войти");
        System.out.println("2. Зарегистрироваться");
        System.out.println("0. Сохранить и Выход");
        System.out.print("Ваш выбор: ");
        
        try {
            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            switch (choice) {
                case 1:
                    System.out.print("Логин: "); String user = scanner.nextLine();
                    System.out.print("Пароль: "); String pass = scanner.nextLine();
                    if (library.login(user, pass)) {
                        activeUser = library.getActiveUser();
                        activeRole = library.getActiveRole();
                        activeUserId = library.getActiveUserId();
                    }
                    break;
                case 2:
                    library.registerUser();
                    break;
                case 0:
                    library.saveAllData();
                    System.exit(0);
                default:
                    System.out.println("Неверный выбор.");
            }
        } catch (Exception e) {
            System.out.println("Некорректный ввод.");
            scanner.nextLine(); // Clearing the buffer
        }
        
    }
    
    private static void mainMenu() {
    	System.out.println("\n===================================");
        System.out.println("Привет, " + activeUser + " (" + activeRole + ")");
        System.out.println("===================================");
        // If the role is ADMIN
        if (activeRole == Role.ADMIN) {
        	System.out.println("--- МЕНЮ ДЕЙСТВИЙ ---");
            System.out.println("1. Добавить книгу");
            System.out.println("2. Добавить пользователя");
            System.out.println("3. Изменить книгу");
            System.out.println("4. Выдать книгу");
            System.out.println("5. Вернуть книгу");
            System.out.println("6. Поиск книг");
            System.out.println("7. Сгенерировать отчеты");
            System.out.println("8. Показать все книги");
            System.out.println("9. Показать всех пользователей");
            System.out.println("10. Показать историю транзакций");
            System.out.println("11. Добавить цифровую книгу");
            System.out.println("0. Сохранить и Выход");
        } 
        // If the role is USER
        else { 
        	System.out.println("--- МЕНЮ ДЕЙСТВИЙ ---");
            System.out.println("1. Выдать книгу (поиск)");
            System.out.println("2. Вернуть книгу");
            System.out.println("3. Поиск книг");
            System.out.println("4. Показать все книги");
            System.out.println("5. Посмотреть и открыть мои выданные книги (ЧТЕНИЕ)");
            System.out.println("0. Сохранить и Выход");
        }
        
        System.out.print("Ваш выбор: ");

        try {
            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            if (activeRole == Role.ADMIN) {
                switch (choice) {
                    case 1: library.addBook(false); break;
                    case 2: library.addUser(); break;
                    case 3: library.updateBook(); break;
                    case 4: library.borrowBook(); break;
                    case 5: library.returnBook(); break;
                    case 6: library.searchMenu(); break;
                    case 7: library.generateReports(); break;
                    case 8: library.displayAllBooks(); break;
                    case 9: library.displayAllUsers(); break;
                    case 10: library.displayAllTransactions(); break;
                    case 11: library.addBook(true); break; // Adding a digital book
                    case 0: library.saveAllData(); System.exit(0);
                    default: System.out.println("Неверный пункт меню.");
                }
            } else {
                switch (choice) {
                    case 1: library.borrowBook(); break;
                    case 2: library.returnBook(); break;
                    case 3: library.searchMenu(); break;
                    case 4: library.displayAllBooks(); break;
                    case 5: library.viewMyBooks(); break;
                    case 0: library.saveAllData(); System.exit(0);
                    default: System.out.println("Неверный пункт меню.");
                }
            }
        } catch (Exception e) {
            System.out.println("Некорректный ввод данных.");
            scanner.nextLine(); // Clearing the buffer
        }
        
        //Screen delay
        try {
        	System.in.read();
      	} catch(Exception e) {}
    }
}