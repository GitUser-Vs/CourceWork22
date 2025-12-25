#define _CRT_SECURE_NO_WARNINGS
#include "Library.hpp"
#include "Book.hpp"
#include "User.hpp"
#include "Transaction.hpp"
#include "FineCalculator.hpp"
#include "SearchEngine.hpp"
#include "ReportGenerator.hpp"
#include <ctime>


// --- Вспомогательные функции для работы с датами ---
std::tm getCurrentTm() {
    std::time_t now = std::time(0);
    std::tm* tm_local = std::localtime(&now);
    std::tm currentDate = *tm_local;
    return currentDate;
}

// Функция для добавления дней к std::tm
std::tm addDaysToTm(std::tm date, int days) {
    date.tm_mday += days;
    std::mktime(&date); // Нормализуем дату (обработает переходы месяцев/лет)
    return date;
}

// --- Дружественная функция ---
void printAllBookTitles(const Library& lib)
{
    std::cout << "\n--- All Book Titles in " << lib.m_name << " ---" << std::endl;
    if (lib.m_books.empty()) {
        std::cout << "No books in the library." << std::endl;
        return;
    }
    for (const auto& book : lib.m_books) {
        // Доступ к приватным членам через дружественную функцию
        std::cout << "- " << book.getTitle() << " by " << book.getAuthor() << std::endl;
    }
    std::cout << "------------------------------------" << std::endl;
}

// --- Перегрузка оператора << ---
std::ostream& operator<<(std::ostream& os, const Library& library)
{
    os << "Library(Name: \"" << library.m_name
        << "\", Address: \"" << library.m_address
        << "\", Books: " << library.m_books.size()
        << ", Users: " << library.m_users.size()
        << ", Transactions: " << library.m_transactions.size() << ")";
    return os;
}

// constructors and destructor
Library::Library()
    : m_name("Unknown Library"), m_address("Unknown Address"),
    m_maxBooksCapacity(1000), m_maxUsersCapacity(500), m_maxTransactionsCapacity(10000), // Значения по умолчанию
    m_fineCalculator(std::make_unique<FineCalculator>()),
    m_searchEngine(std::make_unique<SearchEngine>()),
    m_reportGenerator(std::make_unique<ReportGenerator>())
{
}

// Конструктор с параметрами
Library::Library(const std::string& name, const std::string& address, size_t maxBooks, size_t maxUsers, size_t maxTransactions)
    : m_name(name), m_address(address),
    m_maxBooksCapacity(maxBooks), m_maxUsersCapacity(maxUsers), m_maxTransactionsCapacity(maxTransactions),
    m_fineCalculator(std::make_unique<FineCalculator>(0.75)),
    m_searchEngine(std::make_unique<SearchEngine>()),
    m_reportGenerator(std::make_unique<ReportGenerator>())
{
}

// Конструктор копирования
Library::Library(const Library& other)
    : m_name(other.m_name),
    m_address(other.m_address),
    m_books(other.m_books),
    m_users(other.m_users),
    m_transactions(other.m_transactions),
    m_maxBooksCapacity(other.m_maxBooksCapacity),
    m_maxUsersCapacity(other.m_maxUsersCapacity),
    m_maxTransactionsCapacity(other.m_maxTransactionsCapacity),
    // Создаем новые объекты для unique_ptr
    m_fineCalculator(std::make_unique<FineCalculator>(*other.m_fineCalculator)),
    m_searchEngine(std::make_unique<SearchEngine>(*other.m_searchEngine)),
    m_reportGenerator(std::make_unique<ReportGenerator>(*other.m_reportGenerator))
{
}

// Перегрузка оператора присваивания копированием
Library& Library::operator=(const Library& other)
{
    if (this != &other) // Защита от самоприсваивания
    {
        m_name = other.m_name;
        m_address = other.m_address;
        m_books = other.m_books;
        m_users = other.m_users;
        m_transactions = other.m_transactions;
        m_maxBooksCapacity = other.m_maxBooksCapacity;
        m_maxUsersCapacity = other.m_maxUsersCapacity;
        m_maxTransactionsCapacity = other.m_maxTransactionsCapacity;

        // Копируем агрегированные объекты, используя их конструкторы копирования
        *m_fineCalculator = *other.m_fineCalculator;
        *m_searchEngine = *other.m_searchEngine;
        *m_reportGenerator = *other.m_reportGenerator;
    }
    return *this;
}

// --- Methods for working with books ---
void Library::addItemPtr(std::unique_ptr<LibraryItem> item) {
    if (item) {
        m_items.push_back(std::move(item));
    }
}

void Library::addBook(const std::string& title, const std::string& author, int quantity) 
{
    // Создаем новый объект
    m_items.push_back(std::make_unique<Book>(m_nextId++, title, author, quantity));
}

void Library::displayBooks() const
{
    std::cout << "\n--- Books in Library ---" << std::endl;
    if (m_books.empty()) {
        std::cout << "No books in the library yet." << std::endl;
        return;
    }
    for (const auto& book : m_books) {
        std::cout << book << std::endl;
    }
    std::cout << "------------------------" << std::endl;
}

LibraryItem* Library::findBookById(int itemId) {
    auto it = std::find_if(m_items.begin(), m_items.end(),
        [itemId](const std::unique_ptr<LibraryItem>& item) {
            return item->getItemId() == itemId;
        });

    if (it != m_items.end()) {
        return it->get();
    }
    return nullptr; // Книга не найдена
}

// Сортировка с использованием std::sort
void Library::sortItemsByTitle() {
    std::sort(m_items.begin(), m_items.end(),
        [](const std::unique_ptr<LibraryItem>& a, const std::unique_ptr<LibraryItem>& b) {
            // Сортируем по заголовку
            return a->getTitle() < b->getTitle();
        });
}

void Library::displayAllItems() const {
    std::cout << "\n--- Library Contents ---\n";
    for (const auto& itemPtr : m_items) {
        // Вызов полиморфного метода displayInfo()
        itemPtr->displayInfo();
        std::cout << " | Qty: " << itemPtr->getQuantity() << "\n";
    }
}
// --- Methods for working with users ---
void Library::addUser(const User& user)
{
    m_users.push_back(user); // Копирование объекта
    std::cout << "Added user to library: '" << user.getName() << "'" << std::endl;
}

void Library::displayUsers() const
{
    std::cout << "\n--- Users in Library ---" << std::endl;
    if (m_users.empty()) {
        std::cout << "No users in the library yet." << std::endl;
        return;
    }
    for (const auto& user : m_users) {
        std::cout << user << std::endl; // Используем перегруженный оператор
    }
    std::cout << "------------------------" << std::endl;
}

User* Library::findUserById(int UserID)
{
    // Проходим по вектору m_users
    for (auto& user : m_users) {
        if (user.getUserID() == UserID) {
            return &user; // Возвращаем адрес найденного объекта User
        }
    }
    return nullptr; // Пользователь не найден
}

// --- Методы для работы с транзакциями ---
void Library::addTransaction(const Transaction& transaction)
{
    m_transactions.push_back(transaction); // Копирование объекта
    std::cout << "Added transaction to library system." << std::endl;
}

void Library::displayTransactions() const
{
    std::cout << "\n--- Transactions in Library ---" << std::endl;
    if (m_transactions.empty()) {
        std::cout << "No transactions recorded yet." << std::endl;
        return;
    }
    for (const auto& t : m_transactions) {
        std::cout << t << std::endl; // Используем перегруженный оператор
    }
    std::cout << "-------------------------------" << std::endl;
}

Transaction* Library::findTransactionById(int transactionId)
{
    for (auto& t : m_transactions) {
        if (t.getTransactionId() == transactionId) {
            return &t;
        }
    }
    return nullptr; // Транзакция не найдена
}

// Поиск последней активной транзакции для данной книги и пользователя
Transaction* Library::findTransactionByBookUser(int bookId, int userId)
{
    Transaction* lastActiveTransaction = nullptr;
    for (auto& t : m_transactions) {
        if (t.getBookId() == bookId &&
            t.getUserId() == userId &&
            !t.isReturned())
        {
            // Сохраняем указатель невозвращенной транзакции
            lastActiveTransaction = &t;
        }
    }
    return lastActiveTransaction;
}

// --- Methods using aggregated objects ---
void Library::processLending(int BookID, int UserID)
{
    std::cout << "\nProcessing lending for Book ID " << BookID << " to User ID " << UserID << "..." << std::endl;
    LibraryItem* itemPtr = findBookById(BookID);
    Book* book = dynamic_cast<Book*>(itemPtr);
    //Book* book = findBookById(BookID);
    User* user = findUserById(UserID);

    // Проверка на отсутствие книги или пользователя
    if (!book) {
        std::cout << "Lending failed. Book with ID " << BookID << " not found." << std::endl;
        return;
    }
    if (!user) {
        std::cout << "Lending failed. User with ID " << UserID << " not found." << std::endl;
        return;
    }

    // Проверяем, есть ли у пользователя место для взятия новой книги
    if (user->borrowBook(BookID)) {
        book->decreaseAvailable();
        std::cout << "Lending successful. Book '" << book->getTitle() << "' lent to '" << user->getName() << "'." << std::endl;

        // Создаем новую транзакцию
        std::tm issueDate = getCurrentTm();
        std::tm dueDate = addDaysToTm(issueDate, 14);

        // Создаем транзакцию с уникальным ID
        Transaction newTransaction(static_cast<int>(m_transactions.size()) + 1, BookID, UserID, issueDate, dueDate);
        addTransaction(newTransaction);
    }
}

void Library::processReturn(int BookID, int UserID)
{
    std::cout << "\nProcessing return for Book ID " << BookID << " by User ID " << UserID << "..." << std::endl;
    LibraryItem* itemPtr = findBookById(BookID);
    Book* book = dynamic_cast<Book*>(itemPtr);
    //Book* book = findBookById(BookID);
    User* user = findUserById(UserID);

    if (!book) {
        std::cout << "Return failed. Book with ID " << BookID << " not found." << std::endl;
        return;
    }

    if (!user) {
        std::cout << "Return failed. User with ID " << UserID << " not found." << std::endl;
        return;
    }

    Transaction* activeTransaction = findTransactionByBookUser(BookID, UserID);
    if (!activeTransaction) {
        std::cout << "Return failed. No active lending transaction found for Book ID " << BookID << " and User ID " << UserID << "." << std::endl;
        return;
    }

    std::tm returnDate = getCurrentTm();
    double fine = 0.0;

    std::time_t returnTime = std::mktime(const_cast<std::tm*>(&returnDate));
    std::time_t dueTime = std::mktime(const_cast<std::tm*>(&activeTransaction->getDueDate()));

    if (returnTime > dueTime) {
        int daysOverdue = static_cast<int>((returnTime - dueTime) / (60 * 60 * 24));
        fine = m_fineCalculator->calculateFine(daysOverdue);
    }

    activeTransaction->markAsReturned(returnDate, fine);

    if (user->returnBook(BookID)) {
        book->increaseAvailable();
        std::cout << "Return successful. Book '" << book->getTitle() << "' returned by '" << user->getName() << "'." << std::endl;
        if (fine > 0) {
            std::cout << "  Fine incurred: $" << fine << std::endl;
        }
    }
    else {
        std::cout << "Return warning: User '" << user->getName() << "' count mismatch after return." << std::endl;
    }
}

void Library::performSearch(const std::string& query)
{
    std::cout << "\nPerforming search in Library..." << std::endl;
    m_searchEngine->searchBooks(query);
    m_searchEngine->searchUsers(query); 
}

void Library::generateLibraryReport()
{
    std::cout << "\nGenerating report for Library..." << std::endl;
    // Пример использования дружественной функции
    printAllBookTitles(*this); // Вызываем дружественную функцию
    m_reportGenerator->generate("Library Overview"); // Используем агрегированный ReportGenerator
}

void Library::displayLibraryInfo() const
{
    std::cout << "Library Name: " << m_name
        << ", Address: " << m_address << std::endl;
    std::cout << "Books: " << m_books.size() << "/" << m_maxBooksCapacity << std::endl;
    std::cout << "Users: " << m_users.size() << "/" << m_maxUsersCapacity << std::endl;
    std::cout << "Transactions: " << m_transactions.size() << "/" << m_maxTransactionsCapacity << std::endl;
}