import java.time.LocalDate;
import java.time.temporal.ChronoUnit;
import java.util.List;

public class Main {

	// Демонстрация перегрузки (Overloading)
    public static void demonstrateOverloading(StudentUser student, FacultyUser faculty) {
        System.out.println("\n--- Demonstrating Method Overloading ---");
        // 1. Вызов перегруженного метода, который вызывает метод родителя
        student.printDetails("Student Call");
        // 2. Вызов перегруженного метода, который НЕ вызывает метод родителя явно
        student.printDetails("Student Call", "High Priority");
        
        // FacultyUser просто наследует метод родителя, если не переопределял printDetails(String prefix)
        faculty.printDetails("Faculty Call"); // Использует метод User(String prefix)
        System.out.println("---");
    }

    // Демонстрация полиморфизма (Виртуальные методы)
    public static void demonstratePolymorphism(Library library, User u1, User u2) {
        System.out.println("\n--- Demonstrating Polymorphism (Virtual Methods) ---");
        
        // 1. Вызов через ссылку базового класса (u1 и u2 имеют тип User)
        u1.displayInfo(); // Вызовется метод StudentUser::displayInfo (динамический тип)
        u2.displayInfo(); // Вызовется метод FacultyUser::displayInfo (динамический тип)

        // 2. Демонстрация вызова через НЕВИРТУАЛЬНЫЙ метод базового класса
        // Поскольку в User нет не-виртуальной функции, которая вызывает displayInfo(), 
        // мы создадим временную заглушку в Main, чтобы показать, как статически связанный вызов отличается.
        
        System.out.println("\n--- Static Binding Demo (If displayInfo was NOT virtual/overridden) ---");
        // Если бы displayInfo() не был переопределен, оба вызова выглядели бы как ниже:
        System.out.print("Static Call (Base Type): ");
        // Вызов, который всегда вызывает User::displayInfo (если бы не было @Override)
        System.out.println("[Base User] ID: " + u1.getUserId() + ", Name: " + u1.getName()); 
        System.out.println("Note: In Java, overridden methods are virtual by default.");
    }
    
    // Демонстрация Клонирования
    public static void demonstrateCloning(Book originalBook) {
        System.out.println("\n--- Demonstrating Cloning ---");
        originalBook.displayInfo();
        
        // 5a) Поверхностное клонирование (Shallow Copy)
        Book shallowCopy = (Book) originalBook.clone();
        
        // 5b) Глубокое клонирование (Deep Copy)
        Book deepCopy = originalBook.deepClone();
        
        // Модифицируем доступность в оригинале
        originalBook.decreaseAvailable();
        
        System.out.println("\nAfter modifying original availability:");
        System.out.print("Original: "); originalBook.displayInfo();
        
        // В Java String неизменяем, поэтому shallowCopy будет выглядеть корректно,
        // но если бы в Book было поле-объект, shallowCopy бы его изменил.
        System.out.print("Shallow Copy (Should look different in complex objects): "); 
        shallowCopy.displayInfo(); 
        
        System.out.print("Deep Copy (Should always look independent): "); 
        deepCopy.displayInfo(); 

        // Для демонстрации разницы в глубоком/поверхностном копировании 
        // мы можем искусственно изменить поле, которое не было бы клонировано глубоко
        // (В текущей структуре Book, deepClone и clone будут вести себя одинаково, 
        // т.к. нет ссылочных полей, кроме String).
    }
	
	
    // Demonstration of working with links
    public static void demonstrateReferences() {
        System.out.println("\n--- Demonstrating References (Java's equivalent of pointers/references) ---");
        Book staticBook = new Book(1, "1984", "George Orwell", 10);
        User staticUser = new User(1, "John Doe", "john.doe@example.com", 4);

        Book bookRef1 = staticBook; // bookRef1 refers to the same object as staticBook
        User userRef1 = staticUser; // userRef1 refers to the same object as staticUser

        System.out.println("Using bookRef1:");
        bookRef1.displayInfo();
        System.out.println("Using userRef1:");
        userRef1.displayInfo();

        bookRef1.decreaseAvailable();
        userRef1.borrowBook();
        System.out.println("After modifications:");
        staticBook.displayInfo();
        staticUser.displayInfo();
        System.out.println("------------------------------------------------------------");
    }

    // Demonstration of working with an array of objects (an array of links)
    public static void demonstrateArrayOfObjects() {
        System.out.println("\n--- Demonstrating Array of Objects (Array of References) ---");
        int arraySize = 3;
        Book[] bookArray = new Book[arraySize]; // An array of links to the Book. Null elements by default.

        // Explicitly create objects and assign references to the array
        bookArray[0] = new Book(101, "The Hitchhiker's Guide to the Galaxy", "Douglas Adams", 5);
        bookArray[1] = new Book(102, "The Restaurant at the End of the Universe", "Douglas Adams", 3);
        bookArray[2] = new Book(103, "Life, the Universe and Everything", "Douglas Adams", 7);

        System.out.println("Created array of Book objects:");
        for (int i = 0; i < arraySize; ++i) {
            bookArray[i].displayInfo();
        }

        bookArray = null;
        System.out.println("Array of Book objects (references) cleared.");
        System.out.println("----------------------------------------------------------");
    }

    // Demonstration of working with an array of dynamic objects
    public static void demonstrateArrayOfDynamicObjects() {
        System.out.println("\n--- Demonstrating Array of Dynamic Objects ---");
        int arraySize = 2;
        User[] usersArray = new User[arraySize]; // Array of links to User

        usersArray[0] = new User(301, "Bob Smith", "bob@example.com", 5);
        usersArray[1] = new User(302, "Charlie Brown", "charlie@example.com", 2);

        System.out.println("Created array of User objects:");
        for (int i = 0; i < arraySize; ++i) {
            usersArray[i].displayInfo();
        }

        usersArray = null;
        System.out.println("Array of User objects cleared.");
        System.out.println("----------------------------------------------");
    }
    
// Main
    public static void main(String[] args) {
        System.out.println("--- Library Management System Demonstration (Java) ---");

        // Initialization of objects
        System.out.println("\n--- Demonstrating Initialization ---");
        Book book1 = new Book(10, "1984", "George Orwell", 15);
        User user1 = new User(100, "Alice Smith", "alice.s@example.com", 5);
        
        Book bookA = new Book(Book.getNextBookId(), "The Hobbit", "J.R.R. Tolkien", 5);
        StudentUser student1 = new StudentUser("Jane Doe", "jane@uni.edu", 3, "S1001");
        FacultyUser faculty1 = new FacultyUser("Dr. Smith", "smith@uni.edu", 10, "Physics");
        User genericUser = new User(User.getNextUserId(), "Generic Bob", "bob@lib.org", 2);
        book1.displayInfo();
        user1.displayInfo();
     // Демонстрация наследования и protected
        student1.checkProtectedId();
        System.out.println("------------------------------------");

     // Демонстрация перегрузки
        demonstrateOverloading(student1, faculty1);
        demonstrateReferences();
        demonstrateArrayOfObjects();
        demonstrateArrayOfDynamicObjects();

        // Dynamic initialization of Library class objects
        System.out.println("\n--- Demonstrating Dynamic Initialization of Library ---");
        Library myLibrary = new Library("City Central Library", "123 Main St");
        myLibrary.displayLibraryInfo();

        // Adding books and users
        User polyUser1 = student1; // Полиморфная ссылка на Student
        User polyUser2 = faculty1; // Полиморфная ссылка на Faculty
        Book book2 = new Book(20, "Brave New World", "Aldous Huxley", 12);
        Book book3 = new Book(30, "Fahrenheit 451", "Ray Bradbury", 10);
        User user2 = new User(200, "Bob Johnson", "bob.j@example.com", 4);
        User user3 = new User(201, "Charlie Williams", "charlie.w@example.com", 3);

        myLibrary.addUser(student1);
        myLibrary.addUser(faculty1);
        myLibrary.addUser(genericUser);
        
        myLibrary.addBook(bookA);
        myLibrary.addBook(new Book(Book.getNextBookId(), "Dune", "Frank Herbert", 4));
        
        myLibrary.addBook(book2);
        myLibrary.addBook(book3);
        myLibrary.addUser(user2);
        myLibrary.addUser(user3);
        
        System.out.println("\n--- Demonstrating Error Handling ---");
        myLibrary.addBook(null); // Вызовет исключение IllegalArgumentException
        
     // Пример добавления существующей книги (требует equals/hashCode)
        Book book1Copy = new Book(book1.getBookId(), book1.getTitle(), book1.getAuthor(), book1.getQuantity());
        myLibrary.addBook(book1Copy); // Вызовет IllegalArgumentException, если ID совпадает
        
     // Демонстрация, как исключение обрабатывается в processLending
        System.out.println("\nDemonstrating exception handling in processLending:");
        User user4 = new User(User.getNextUserId(), "Test User", "test@example.com", 0); // Пользователь с лимитом 0 книг
        myLibrary.addUser(user4);
        myLibrary.processLending(book1.getBookId(), user4.getUserId()); // Должно бросить IllegalStateException из User.borrowBook()

        System.out.println("\n--- Demonstrating try-catch-finally ---");
        try {
            System.out.println("Entering try block...");
            int result = 10 / 2;
            System.out.println("Result of division: " + result);
            // int errorResult = 10 / 0; // Раскомментировать для демонстрации ArithmeticException
        } catch (ArithmeticException e) {
            System.err.println("Caught ArithmeticException: Cannot divide by zero.");
        } finally {
            System.out.println("Executing finally block.");
        }

        Book dynamicBookForLib = new Book(40, "The Great Gatsby", "F. Scott Fitzgerald", 8);
        myLibrary.addBook(dynamicBookForLib);

        User dynamicUserForLib = new User(202, "Diana Miller", "diana.m@example.com", 5);
        myLibrary.addUser(dynamicUserForLib);

        myLibrary.displayBooks();
        myLibrary.displayUsers();

        // Demonstration of the Lending and Return operations that now create/update transactions
        myLibrary.processLending(20, 200); // Issue "Brave New World" to Bob (creates a transaction)
        myLibrary.processLending(30, 201); // Issue "Fahrenheit 451" to Charlie (will create a transaction)
        myLibrary.processLending(10, 100); // Give "1984" to Alice (creates a transaction)
        myLibrary.processLending(40, 202); // Give "The Great Gatsby" to Diana (will create a transaction)

        myLibrary.displayBooks();
        myLibrary.displayUsers();

        // We try to take a book when the limit is reached (for user2)
        myLibrary.processLending(20, 200); // An attempt to give another book to Bob should be unsuccessful
        myLibrary.processLending(bookA.getBookId(), student1.getUserId());
        myLibrary.processLending(bookA.getBookId(), faculty1.getUserId());
        
        // Refund demonstration
        myLibrary.processReturn(20, 200); // Return "Brave New World" from Bob (will update the transaction)
        myLibrary.processReturn(30, 201); // Return "Fahrenheit 451" from Charlie (will update the transaction)

      	myLibrary.displayBooks();
        myLibrary.displayUsers();

        // Showing all transactions, including updated ones
        myLibrary.displayTransactions();

        // Demonstration of search and reporting
        List<Book> foundBooks = myLibrary.searchBooks("bradbury");
        System.out.println("Found books: " + foundBooks.size());

        List<User> foundUsers = myLibrary.searchUsers("john");
        System.out.println("Found users: " + foundUsers.size());
        
        myLibrary.generateBookReport();
        myLibrary.generateUserReport();
        myLibrary.generateTransactionReport();
        myLibrary.generateGeneralReport("Summary");

        System.out.println("\n--- Demonstration Finished ---");
        
        // Screen delay
        try {
        	System.in.read();
     	} catch(Exception e) {}
    }
    
}