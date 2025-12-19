#include "Book.hpp"
#include "User.hpp"
#include "Library.hpp"
#include "FineCalculator.hpp"
#include "SearchEngine.hpp"
#include "ReportGenerator.hpp"
#include "DigitalBook.hpp"
#include "LibraryItem.hpp"
#include <iostream>
#include <vector>

// --- Demo functions ---

// --- Вспомогательная функция для демонстрации клонирования ---
void demonstrateCloning(const LibraryItem* item) {
    std::cout << "\n--- Demonstrating Cloning ---" << std::endl;

    if (!item) return;

    std::cout << "Original Item Info: ";
    item->displayInfo();

    // Глубокое клонирование (через виртуальную функцию)
    LibraryItem* clonedItem = item->clone();
    std::cout << "Cloned Item Info: ";
    clonedItem->displayInfo();

    std::cout << "Cloned item address: " << clonedItem << std::endl;
    std::cout << "Original item address: " << item << std::endl;

    delete clonedItem;
    std::cout << "Cloning demo complete." << std::endl;
}

// --- Виртуальные функции ---
void demonstrateVirtualFunctions() {
    std::cout << "\n--- Demonstrating Virtual Functions (Polymorphism) ---" << std::endl;

    // Создаем статические объекты разных типов
    Book physicalBook(991, "The Martian", "Andy Weir", 5);
    DigitalBook eBook(992, "Dune E-Edition", "Frank Herbert", 10, "http://e.com/dune", 150);

    // Вызов через указатель на базовый класс
    LibraryItem* itemPtr1 = &physicalBook;
    LibraryItem* itemPtr2 = &eBook;

    // Вызов виртуальной функции через указатель на базовый класс
    std::cout << "Calling virtual displayInfo() via LibraryItem*:" << std::endl;
    itemPtr1->displayInfo(); // Вызывается Book::displayInfo
    itemPtr2->displayInfo(); // Вызывается DigitalBook::displayInfo

    std::cout << "\nCalling non-virtual Book::displayExtendedInfo() via Book*:" << std::endl;
    Book* bookPtr = &physicalBook;
    bookPtr->displayExtendedInfo();

    std::cout << "\nCalling non-virtual DigitalBook::displayExtendedInfo() via DigitalBook*:" << std::endl;
    DigitalBook* dBookPtr = &eBook;
    dBookPtr->displayExtendedInfo();

    std::cout << "\nDemonstrate cloning of physical book:" << std::endl;
    demonstrateCloning(&physicalBook);
}

// --- Main Function ---
int main()
{
    std::cout << "--- Library Management System Demonstration ---" << std::endl;

    demonstrateVirtualFunctions();

    // Static initialization of objects
    std::cout << "\n--- Demonstrating Static Initialization ---" << std::endl;
    Book book1(10, "1984", "George Orwell", 15);
    User user1(100, "Alice Smith", "alice.s@example.com", 5);

    book1.displayInfo();
    user1.displayInfo();
    std::cout << "-----------------------------------------" << std::endl;

    // Dynamic initialization of Library class objects
    std::cout << "\n--- Demonstrating Dynamic Initialization of Library ---" << std::endl;

    // Dynamically creating a Library with parameters
    Library* myLibrary = new Library("City Central Library", "123 Main St", 100, 50);

    Book bookA(1, "The Great Novel", "A. Author", 10);
    DigitalBook eBookB(2, "EBook Thriller", "B. Writer", 5, "http://e.com/thriller", 100);
    User userX(50, "Cloner User", "clone@test.com", 5);

    myLibrary->displayLibraryInfo();

    // Creating Book and User objects to add to the library
    // Static Book and User objects
    Book book2(20, "Brave New World", "Aldous Huxley", 12);
    Book book3(30, "Fahrenheit 451", "Ray Bradbury", 10);
    User user2(200, "Bob Johnson", "bob.j@example.com", 4);
    User user3(201, "Charlie Williams", "charlie.w@example.com", 3);

    // Adding books and users to the library (copying objects)
    myLibrary->addBook(book2);
    myLibrary->addBook(book3);
    myLibrary->addUser(user2);
    myLibrary->addUser(user3);

    myLibrary->addUser(userX);
    myLibrary->addBook(bookA);
    myLibrary->addBook(eBookB);

    // Демонстрация работы с клонированием
    Book* foundBook = myLibrary->findBookById(1);
    if (foundBook) {
        demonstrateCloning(foundBook);
    }

    // Демонстрация доступа к protected полю через Book
    if (foundBook) {
        foundBook->checkProtectedAccess();
    }

    // Adding a book created dynamically (passing by value, memory is released after)
    Book* dynamicBookForLib = new Book(40, "The Great Gatsby", "F. Scott Fitzgerald", 8);
    myLibrary->addBook(*dynamicBookForLib);
    delete dynamicBookForLib;

    // Adding a user created dynamically (passed by value, memory is released after)
    User* dynamicUserForLib = new User(202, "Diana Miller", "diana.m@example.com ", 5);
    myLibrary->addUser(*dynamicUserForLib);
    delete dynamicUserForLib;

    myLibrary->displayBooks();
    myLibrary->displayUsers();

    // Demonstration of Library methods using aggregated
    myLibrary->processLending(20, 200); // Give "Brave New World" to Bob
    myLibrary->processLending(30, 201); // Give "Fahrenheit 451" To Charlie
    myLibrary->processLending(10, 100); // Give "1984" to Alice
    myLibrary->processLending(40, 202); // Give "The Great Gatsby" To Diana

    // Trying to take a book when the limit is reached (for user2)
    myLibrary->processLending(20, 200); // Trying to give another book to Bob

    myLibrary->displayBooks();
    myLibrary->displayUsers();

    myLibrary->processReturn(20, 200); // Return "Brave New World" from Bob
    myLibrary->processReturn(30, 201); // Return "Fahrenheit 451" from Charlie

    myLibrary->displayBooks();
    myLibrary->displayUsers();
    myLibrary->displayTransactions();

    myLibrary->performSearch("Huxley"); // Calling the SearchEngine method
    myLibrary->generateLibraryReport(); // Calling the ReportGenerator method

    // Использование перегруженных операторов
    std::cout << "\n--- Using overloaded operators ---" << std::endl;
    std::cout << book1 << std::endl;
    std::cout << user1 << std::endl;
    std::cout << *myLibrary << std::endl; // Используем перегруженный << для Library

    User tempUser(100, "Alice Smith", "alice.s@example.com", 5);
    if (user1 == tempUser) { // Используем перегруженный ==
        std::cout << "User1 and tempUser are the same user (by ID)." << std::endl;
    }
    std::cout << "---" << std::endl;


    // Демонстрация работы с копированием Library
    std::cout << "\n--- Demonstrating Library Copying ---" << std::endl;
    Library* anotherLibrary = new Library("Branch Library", "456 Oak Ave");
    *anotherLibrary = *myLibrary; // Оператор присваивания копированием
    std::cout << "Copied myLibrary to anotherLibrary using assignment operator:" << std::endl;
    anotherLibrary->displayLibraryInfo();
    std::cout << *anotherLibrary << std::endl;

    Library* copiedLibrary = new Library(*myLibrary); // Конструктор копирования
    std::cout << "\nCreated copiedLibrary using copy constructor:" << std::endl;
    copiedLibrary->displayLibraryInfo();
    std::cout << *copiedLibrary << std::endl;

    delete anotherLibrary;
    delete copiedLibrary;
    std::cout << "--- Library Copying Demo Finished ---" << std::endl;

    delete myLibrary;

    std::cout << "\n--- Demonstration Finished ---" << std::endl;

    return 0;
}