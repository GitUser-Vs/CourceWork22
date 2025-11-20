
public class Main {

    // Demonstration of working with links (Java's equivalent of pointers/references)
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

    public static void main(String[] args) {
        System.out.println("--- Library Management System Demonstration (Java) ---");

        // Initialization of objects (analogous to static initialization)
        System.out.println("\n--- Demonstrating Initialization ---");
        Book book1 = new Book(10, "1984", "George Orwell", 15);
        User user1 = new User(100, "Alice Smith", "alice.s@example.com", 5);
        book1.displayInfo();
        user1.displayInfo();
        System.out.println("------------------------------------");

        demonstrateReferences();
        demonstrateArrayOfObjects();
        demonstrateArrayOfDynamicObjects();

        // Dynamic initialization of Library class objects
        System.out.println("\n--- Demonstrating Dynamic Initialization of Library ---");
        Library myLibrary = new Library("City Central Library", "123 Main St");
        myLibrary.displayLibraryInfo();

        // Adding books and users
        Book book2 = new Book(20, "Brave New World", "Aldous Huxley", 12);
        Book book3 = new Book(30, "Fahrenheit 451", "Ray Bradbury", 10);
        User user2 = new User(200, "Bob Johnson", "bob.j@example.com", 4);
        User user3 = new User(201, "Charlie Williams", "charlie.w@example.com", 3);

        myLibrary.addBook(book2);
        myLibrary.addBook(book3);
        myLibrary.addUser(user2);
        myLibrary.addUser(user3);

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

        // Refund demonstration
        myLibrary.processReturn(20, 200); // Return "Brave New World" from Bob (will update the transaction)
        myLibrary.processReturn(30, 201); // Return "Fahrenheit 451" from Charlie (will update the transaction)

      	myLibrary.displayBooks();
        myLibrary.displayUsers();

        // Showing all transactions, including updated ones
        myLibrary.displayTransactions();

        // Demonstration of search and reporting
        myLibrary.performSearch("Huxley");
        myLibrary.generateLibraryReport();

        System.out.println("\n--- Demonstration Finished ---");
        // There is no explicit delete MyLibrary; the garbage collector takes care of it.
        
        // Задержка экрана
        try {
        	System.in.read();
     	} catch(Exception e) {}
    }
    
}