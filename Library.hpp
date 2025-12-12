#pragma once

#include "FineCalculator.hpp"
#include "SearchEngine.hpp"
#include "ReportGenerator.hpp"
#include "Transaction.hpp"
#include <string>
#include <iostream>
#include <vector>

class Library
{

private:
    // private variables
    std::string m_name;
    std::string m_address;

    // Использование std::vector для хранения объектов
    std::vector<Book> m_books;
    std::vector<User> m_users;
    std::vector<Transaction> m_transactions;

    size_t m_maxBooksCapacity;
    size_t m_maxUsersCapacity;
    size_t m_maxTransactionsCapacity;

    // Использование std::unique_ptr для управления агрегированными объектами
    std::unique_ptr<FineCalculator> m_fineCalculator;
    std::unique_ptr<SearchEngine> m_searchEngine;
    std::unique_ptr<ReportGenerator> m_reportGenerator;

public:
    // constructors and destructor
    Library();
    Library(const std::string& name, const std::string& address,
        size_t maxBooks = 1000, size_t maxUsers = 500, size_t maxTransactions = 10000); // Добавлены параметры для вместимости
    Library(const Library& other); // Конструктор копирования
    ~Library() = default;

    // Перегрузка оператора присваивания копированием
    Library& operator=(const Library& other);

    // public methods
    void displayLibraryInfo() const;

    // methods for working with books
    void addBook(const Book& book);
    void displayBooks() const;
    Book* findBookById(int BookID);

    // methods for working with users
    void addUser(const User& user);
    void displayUsers() const;
    User* findUserById(int UserID); // Returns a pointer to the user

     // Методы для работы с транзакциями
    void addTransaction(const Transaction& transaction);
    void displayTransactions() const;
    Transaction* findTransactionById(int transactionId);
    Transaction* findTransactionByBookUser(int bookId, int userId);

    // methods using aggregated objects
    void processLending(int BookID, int UserID);
    void processReturn(int BookID, int UserID);
    void performSearch(const std::string& query);
    void generateLibraryReport();

    // Пример дружественной функции для доступа к приватным данным (например, к вектору книг)
    friend void printAllBookTitles(const Library& lib);

    // Перегрузка оператора для вывода объекта Library
    friend std::ostream& operator<<(std::ostream& os, const Library& library);
};

