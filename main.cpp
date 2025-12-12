#include "Book.hpp"
#include "User.hpp"
#include "Library.hpp"
#include "FineCalculator.hpp"
#include "SearchEngine.hpp"
#include "ReportGenerator.hpp"
#include <iostream>
#include <vector>

// --- Demo functions ---

void demonstrateDynamicAllocation() {
    std::cout << "\n--- Demonstrating Dynamic Allocation (new/delete) ---" << std::endl;
    Book* dynamicBook = new Book(101, "The Hitchhiker's Guide to the Galaxy", "Douglas Adams", 5);
    dynamicBook->displayInfo();
    dynamicBook->decreaseAvailable();
    dynamicBook->displayInfo();
    delete dynamicBook; // Freeing up memory

    User* dynamicUser = new User(201, "Alice Wonderland", "alice@example.com", 3);
    dynamicUser->displayInfo();
    dynamicUser->borrowBook(101);
    dynamicUser->displayInfo();
    delete dynamicUser; // Freeing up memory
    std::cout << "----------------------------------------------------" << std::endl;
}

void demonstratePointersAndReferences() {
    std::cout << "\n--- Demonstrating Pointers and References ---" << std::endl;
    Book staticBook(1, "1984", "George Orwell", 10);
    User staticUser(1, "John Doe", "john.doe@example.com", 4);

    Book* bookPtr = &staticBook;
    std::cout << "Using pointer to Book: ";
    bookPtr->displayInfo();

    User& userRef = staticUser;
    std::cout << "Using reference to User: ";
    userRef.displayInfo();

    bookPtr->decreaseAvailable();
    userRef.borrowBook(1);
    std::cout << "After modifications:" << std::endl;
    staticBook.displayInfo();
    staticUser.displayInfo();
    std::cout << "-------------------------------------------" << std::endl;
}

void demonstrateDynamicArray() {
    std::cout << "\n--- Demonstrating Dynamic Array of Objects ---" << std::endl;
    int arraySize = 3;
    Book* bookArr = new Book[arraySize]; // Creates arraySize Book objects

    std::cout << "Created dynamic array of " << arraySize << " Books (default constructor called for each)." << std::endl;

    for (int i = 0; i < arraySize; ++i) {
        std::cout << "Book in array at index " << i << ":";
        bookArr[i].displayInfo(); // Displaying information
    }
    delete[] bookArr;
    std::cout << "Dynamic array of Books deleted." << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
}

void demonstrateArrayOfDynamicObjects() {
    std::cout << "\n--- Demonstrating Array of Dynamic Objects ---" << std::endl;
    int arraySize = 2;
    User** usersPtrArray = new User * [arraySize];

    usersPtrArray[0] = new User(301, "Bob Smith", "bob@example.com", 5);
    usersPtrArray[1] = new User(302, "Charlie Brown", "charlie@example.com", 2);

    std::cout << "Created array of pointers to User objects:" << std::endl;
    for (int i = 0; i < arraySize; ++i) {
        usersPtrArray[i]->displayInfo();
    }

    for (int i = 0; i < arraySize; ++i) {
        delete usersPtrArray[i]; // Deleting each object
    }
    delete[] usersPtrArray; // Deleting the array of pointers
    std::cout << "Array of dynamic User objects deleted." << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;
}

// --- Main Function main ---
int main()
{
    std::cout << "--- Library Management System Demonstration ---" << std::endl;

    // 1. Static initialization of objects
    std::cout << "\n--- Demonstrating Static Initialization ---" << std::endl;
    Book book1(10, "1984", "George Orwell", 15);
    User user1(100, "Alice Smith", "alice.s@example.com", 5);

    book1.displayInfo();
    user1.displayInfo();
    std::cout << "-----------------------------------------" << std::endl;

    demonstratePointersAndReferences();
    demonstrateDynamicAllocation();
    demonstrateDynamicArray();
    demonstrateArrayOfDynamicObjects();

    // 2. Dynamic initialization of Library class objects
    std::cout << "\n--- Demonstrating Dynamic Initialization of Library ---" << std::endl;
    // Dynamically creating a Library with parameters
    Library* myLibrary = new Library("City Central Library", "123 Main St", 100, 50);
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