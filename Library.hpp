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

    // Private methods for I/O
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

public:
    // constructors and destructor
    Library();
    ~Library();

    // public methods
    void saveAllData();
    
    void addBook(bool is_digital = false);
    void viewMyBooks(int userId) const;
    void addUser();
    void updateBook();

    // Operations
    void borrowBook();
    void returnBook();

    // Display
    void displayAllBooks() const;
    void displayAllUsers() const;
    void displayAllTransactions() const;

    // Authentication methods
    bool registerUser();
    bool login(std::string& currentUsername, Role& currentRole, int& currentUserId);

    void searchMenu();
    void generateReports() const;
};

