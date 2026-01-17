#pragma once

#include "FineCalculator.hpp"
#include "SearchEngine.hpp"
#include "ReportGenerator.hpp"
#include "Transaction.hpp"
#include "LibraryItem.hpp"
#include "Book.hpp"
#include "Account.hpp"
#include "SystemHelper.hpp"
#include <string>
#include <iostream>
#include <vector>

class Library
{

private:
    // private variables

    // Использование std::vector для хранения объектов
    std::vector<Book> books;
    std::vector<User> users;
    std::vector<Transaction> transactions;
    std::vector<Account> accounts;

    SearchEngine searchEngine;
    ReportGenerator reportGenerator;
    FineCalculator fineCalculator;

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
    ~Library();

    // public methods
    void saveAllData();
    
    void addBook(bool is_digital = false);
    void viewMyBooks(int userId) const; // Новая функция для пользователя
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
};

