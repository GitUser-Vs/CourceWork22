#pragma once

#include "FineCalculator.hpp"
#include "SearchEngine.hpp"
#include "ReportGenerator.hpp"
#include "Transaction.hpp"
#include "LibraryItem.hpp"
#include "Book.hpp"
#include "Account.hpp"
#include <string>
#include <iostream>
#include <vector>

class Library
{

private:
    // private variables
    /*std::string m_name;
    std::string m_address;*/

    // Использование std::vector для хранения объектов
    std::vector<Book> books;
    std::vector<User> users;
    std::vector<Transaction> transactions;
    std::vector<Account> accounts;

    /*size_t m_maxBooksCapacity;
    size_t m_maxUsersCapacity;
    size_t m_maxTransactionsCapacity;*/

    SearchEngine searchEngine;
    ReportGenerator reportGenerator;
    FineCalculator fineCalculator;

    // Использование std::unique_ptr для управления агрегированными объектами
    std::unique_ptr<FineCalculator> m_fineCalculator;
    std::unique_ptr<SearchEngine> m_searchEngine;
    std::unique_ptr<ReportGenerator> m_reportGenerator;

    const std::string BOOK_FILE = "books.txt";
    const std::string USER_FILE = "users.txt";
    const std::string TRANSACTION_FILE = "transactions.txt";
    const std::string ACCOUNT_FILE = "accounts.txt";

    int nextBookId;
    int nextUserId;
    int nextTransactionId;

    // Приватные методы для I/O
    void saveBooks();
    void loadBooks();

    void saveUsers();
    void loadUsers();

    void saveTransactions();
    void loadTransactions();

    void saveAccounts();
    void loadAccounts();

    // Вспомогательные
    Book* findBook(int id);
    User* findUser(int id);
    Account* findAccount(const std::string& username);
    //Transaction* findTransaction(int id);

public:
    // constructors and destructor
    Library();
    //Library(const std::string& name, const std::string& address,
    //    size_t maxBooks = 1000, size_t maxUsers = 500, size_t maxTransactions = 10000); // Добавлены параметры для вместимости
    //Library(const Library& other); // Конструктор копирования
    ~Library();

    // Перегрузка оператора присваивания копированием
    //Library& operator=(const Library& other);

    // public methods
    //void displayLibraryInfo() const;
    void saveAllData();
    
    void addBook();
    void addUser();
    void updateBook();

    // Операции
    void borrowBook();
    void returnBook();

    // Отображение
    void displayAllBooks() const;
    void displayAllUsers() const;
    void displayAllTransactions() const;
    //Book* findBookById(int BookID);

    // Методы аутентификации
    bool registerUser();
    bool login(std::string& currentUsername, Role& currentRole, int& currentUserId);

    void searchMenu();
    void generateReports() const;

    //// Демонстрация поиска
    //LibraryItem* findBookById(int itemId);

    //// Демонстрация сортировки
    //void sortItemsByTitle();

    //void displayAllItems() const;

    //// Методы для работы с транзакциями
    //void addTransaction(const Transaction& transaction);
    //void displayTransactions() const;
    //Transaction* findTransactionById(int transactionId);
    //Transaction* findTransactionByBookUser(int bookId, int userId);

    //// methods using aggregated objects
    //void processLending(int BookID, int UserID);
    //void processReturn(int BookID, int UserID);
    //void performSearch(const std::string& query);
    //void generateLibraryReport();
};

