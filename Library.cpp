#define _CRT_SECURE_NO_WARNINGS
#include "Library.hpp"
#include "Book.hpp"
#include "User.hpp"
#include "Transaction.hpp"
#include "FineCalculator.hpp"
#include "SearchEngine.hpp"
#include "ReportGenerator.hpp"
#include <fstream>
#include <algorithm>

using namespace std;

// constructors and destructor
Library::Library() : nextBookId(1), nextUserId(1), nextTransactionId(1) {
    loadBooks();
    loadUsers();
    loadTransactions();
    loadAccounts();
}

Library::~Library() {
    saveAllData();
}

// --- I/O implementations ---
void Library::saveBooks() {
    ofstream ofs(BOOK_FILE);
    for (const auto& book : books) { ofs << book.serialize() << endl; }
    ofs.close();
}

void Library::loadBooks() {
    ifstream ifs(BOOK_FILE);
    string line;
    books.clear();
    int maxId = 0;
    while (getline(ifs, line)) {
        Book book;
        book.deserialize(line);
        books.push_back(book);
        if (book.getId() > maxId) maxId = book.getId();
    }
    nextBookId = maxId + 1;
    ifs.close();
}

void Library::saveUsers() {
    ofstream ofs(USER_FILE);
    for (const auto& user : users) { ofs << user.serialize() << endl; }
    ofs.close();
}

void Library::loadUsers() {
    ifstream ifs(USER_FILE);
    string line;
    users.clear();
    int maxId = 0;
    while (getline(ifs, line)) {
        User user;
        user.deserialize(line);
        users.push_back(user);
        if (user.getId() > maxId) maxId = user.getId();
    }
    nextUserId = maxId + 1;
    ifs.close();
}

void Library::saveTransactions() {
    ofstream ofs(TRANSACTION_FILE);
    for (const auto& t : transactions) { ofs << t.serialize() << endl; }
    ofs.close();
}

void Library::loadTransactions() {
    ifstream ifs(TRANSACTION_FILE);
    string line;
    transactions.clear();
    int maxId = 0;
    while (getline(ifs, line)) {
        Transaction t;
        t.deserialize(line);
        transactions.push_back(t);
        if (t.getTransactionId() > maxId) maxId = t.getTransactionId();
    }
    nextTransactionId = maxId + 1;
    ifs.close();
}

void Library::saveAccounts() {
    ofstream ofs(ACCOUNT_FILE);
    for (const auto& acc : accounts) { ofs << acc.serialize() << endl; }
    ofs.close();
}

void Library::loadAccounts() {
    ifstream ifs(ACCOUNT_FILE);
    string line;
    accounts.clear();
    while (getline(ifs, line)) {
        Account acc;
        acc.deserialize(line);
        accounts.push_back(acc);
    }
    ifs.close();
}

void Library::saveAllData() {
    saveBooks();
    saveUsers();
    saveTransactions();
    saveAccounts();
    cout << "\n[СИСТЕМА] Данные сохранены." << endl;
}

// --- Вспомогательные функции ---
Book* Library::findBook(int id) {
    for (auto& book : books) {
        if (book.getId() == id) return &book;
    }
    return nullptr;
}

User* Library::findUser(int id) {
    for (auto& user : users) {
        if (user.getId() == id) return &user;
    }
    return nullptr;
}

Account* Library::findAccount(const std::string& username) {
    for (auto& acc : accounts) {
        if (acc.getUsername() == username) return &acc;
    }
    return nullptr;
}

// --- Methods for working with books ---
void Library::addBook(bool is_digital)
{
    string title, author, isbn;
    cout << "Введите название: "; getline(cin, title);
    cout << "Введите автора: "; getline(cin, author);
    cout << "Введите ISBN: "; getline(cin, isbn);

    string path = "N/A";
    if (is_digital) {
        cout << "Введите полный путь к файлу книги (например, C:\\books\\Name_book.pdf): ";
        getline(cin, path);
    }

    books.emplace_back(nextBookId++, title, author, isbn);
    books.back().setFilePath(path); // Setting the path
    cout << "Книга добавлена с ID: " << books.back().getId() << endl;
}

void Library::viewMyBooks(int userId) const {
    cout << "\n--- МОИ ВЫДАННЫЕ КНИГИ ---" << endl;
    bool found = false;

    for (const auto& t : transactions) {
        if (t.getUserId() == userId && t.isActiveStatus()) {
            found = true;
            const Book* book = nullptr;
            for (const auto& b : books) {
                if (b.getId() == t.getBookId()) {
                    book = &b;
                    break;
                }
            }

            if (book) {
                cout << "[" << book->getId() << "] " << book->getTitle()
                    << " (Срок: " << t.getDueDate() << ")";

                if (book->getFilePath() != "N/A") {
                    cout << " [ЦЕНЗУРИРОВАНО - ДОСТУПНО ЧТЕНИЕ]";
                }
                cout << endl;
            }
        }
    }
    if (!found) {
        cout << "У вас нет активных выданных книг." << endl;
        return;
    }

    int choiceId;
    cout << "\nВведите ID книги, которую хотите прочитать (или 0 для выхода): ";
    cin >> choiceId;
    cin.ignore();

    if (choiceId != 0) {
        const Book* targetBook = nullptr;
        for (const auto& b : books) {
            if (b.getId() == choiceId && b.getFilePath() != "N/A") {
                targetBook = &b;
                break;
            }
        }

        if (targetBook) {
            // use an auxiliary class to open the file.
            SystemHelper::openFile(targetBook->getFilePath());
        }
        else {
            cout << "Книга не найдена или цифровая копия недоступна." << endl;
        }
    }
}

void Library::displayAllBooks() const
{
    cout << "\n--- СПИСОК КНИГ ---" << endl;
    if (books.empty()) { cout << "Библиотека пуста." << endl; return; }
    for (const auto& book : books) { book.display(); }
}

void Library::updateBook() {
    int id;
    cout << "Введите ID книги для изменения: ";
    cin >> id;
    cin.ignore();

    Book* book = findBook(id);
    if (!book) {
        cout << "Книга не найдена." << endl;
        return;
    }

    cout << "Текущая книга: "; book->display();

    string newTitle, newAuthor, newIsbn;
    cout << "Новое название (Enter для пропуска): "; getline(cin, newTitle);
    if (!newTitle.empty()) book->title = newTitle;

    cout << "Новый автор (Enter для пропуска): "; getline(cin, newAuthor);
    if (!newAuthor.empty()) book->author = newAuthor;

    cout << "Новый ISBN (Enter для пропуска): "; getline(cin, newIsbn);
    if (!newIsbn.empty()) book->isbn = newIsbn;

    cout << "Книга обновлена." << endl;
}

void Library::borrowBook() {
    int uId, bId;
    cout << "Введите ID пользователя: "; cin >> uId;
    cout << "Введите ID книги для выдачи: "; cin >> bId;
    cin.ignore();

    User* user = findUser(uId);
    Book* book = findBook(bId);

    if (!user) { cout << "Ошибка: Пользователь не найден." << endl; return; }
    if (!book) { cout << "Ошибка: Книга не найдена." << endl; return; }
    if (!book->getAvailability()) { cout << "Ошибка: Книга уже выдана." << endl; return; }

    transactions.emplace_back(nextTransactionId++, bId, uId);
    book->setAvailability(false);

    cout << "Книга '" << book->getTitle() << "' выдана пользователю "
        << user->getName() << ". Срок: " << transactions.back().getDueDate() << endl;
}

void Library::returnBook() {
    int bId;
    cout << "Введите ID книги, которую возвращают: "; cin >> bId;
    cin.ignore();

    Book* book = findBook(bId);
    if (!book) { cout << "Ошибка: Книга не найдена." << endl; return; }

    Transaction* activeT = nullptr;
    for (auto& t : transactions) {
        if (t.getBookId() == bId && t.isActiveStatus()) {
            activeT = &t;
            break;
        }
    }

    if (!activeT) { cout << "Ошибка: Активная запись о выдаче для этой книги не найдена." << endl; return; }

    book->setAvailability(true);
    activeT->completeTransaction();

    double fine = fineCalculator.calculateFine(*activeT);
    cout << "Книга '" << book->getTitle() << "' успешно возвращена." << endl;
    if (fine > 0) {
        cout << "!!! Начислен штраф: " << fine << " у.е. за просрочку." << endl;
    }
}

// --- Methods for working with users ---
void Library::addUser()
{
    string name, contact;
    cout << "Введите имя пользователя: "; getline(cin, name);
    cout << "Введите контакт (телефон/email): "; getline(cin, contact);

    users.emplace_back(nextUserId++, name, contact);
    cout << "Пользователь добавлен с ID: " << users.back().getId() << endl;
}

void Library::displayAllUsers() const
{
    cout << "\n--- СПИСОК ПОЛЬЗОВАТЕЛЕЙ ---" << endl;
    if (users.empty()) { cout << "Нет зарегистрированных пользователей." << endl; return; }
    for (const auto& user : users) { user.display(); }
}

void Library::displayAllTransactions() const
{
    cout << "\n--- ИСТОРИЯ ТРАНЗАКЦИЙ ---" << endl;
    if (transactions.empty()) { cout << "Транзакций нет." << endl; return; }
    for (const auto& t : transactions) { t.display(); }
}

// --- Authentication ---
bool Library::registerUser() {
    string username, password;
    cout << "--- РЕГИСТРАЦИЯ (Роль по умолчанию: USER) ---" << endl;
    cout << "Введите желаемый логин: "; getline(cin, username);

    if (findAccount(username)) {
        cout << "Ошибка: Логин уже занят." << endl;
        return false;
    }

    cout << "Введите пароль: "; getline(cin, password);

    // registering a new user in the user list
    users.emplace_back(nextUserId++, username, "N/A"); // Contact initially "N/A"
    int newUserId = users.back().getId();

    // Registering an account with the USER role associated with the new ID
    accounts.emplace_back(username, password, Role::USER, newUserId);

    cout << "Регистрация успешна! Ваш User ID: " << newUserId << endl;
    return true;
}

bool Library::login(std::string& currentUsername, Role& currentRole, int& currentUserId) {
    string username, password;
    cout << "--- ВХОД В СИСТЕМУ ---" << endl;
    cout << "Логин: "; getline(cin, username);
    cout << "Пароль: "; getline(cin, password);

    Account* acc = findAccount(username);

    if (!acc) {
        cout << "Ошибка: Логин или пароль неверны." << endl;
        return false;
    }

    if (acc->getPassword() == password) {
        currentUsername = acc->getUsername();
        currentRole = acc->getRole();
        currentUserId = acc->getAssociatedId();
        cout << "Вход успешен. Роль: " << (currentRole == Role::ADMIN ? "АДМИНИСТРАТОР" : "ПОЛЬЗОВАТЕЛЬ") << endl;
        return true;
    }
    else {
        cout << "Ошибка: Логин или пароль неверны." << endl;
        return false;
    }
}


// --- Specialized ---
void Library::generateReports() const
{
    int choice;
    cout << "\n[ОТЧЕТЫ] 1. Активные выдачи | 2. Штрафы (только для активных): ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        reportGenerator.generateActiveLoansReport(transactions, users, books);
    }
    else if (choice == 2) {
        cout << "\n--- ОТЧЕТ О ПОТЕНЦИАЛЬНЫХ ШТРАФАХ ---" << endl;
        bool foundFine = false;
        for (const auto& t : transactions) {
            if (t.isActiveStatus()) {
                double fine = fineCalculator.calculateFine(t);
                if (fine > 0) {
                    foundFine = true;
                    cout << "Транзакция ID: " << t.getTransactionId() << " | Штраф: " << fine << " у.е." << endl;
                }
            }
        }
        if (!foundFine) cout << "Активных просроченных книг нет." << endl;
    }
    else {
        cout << "Неверный выбор." << endl;
    }
}

void Library::searchMenu()
{
    int choice;
    string query;
    cout << "\n[ПОИСК] 1. По названию | 2. По автору: ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        cout << "Введите часть названия: "; getline(cin, query);
        auto results = searchEngine.searchByTitle(books, query);
        if (results.empty()) cout << "Ничего не найдено." << endl;
        for (const auto& b : results) b.display();
    }
    else if (choice == 2) {
        cout << "Введите часть имени автора: "; getline(cin, query);
        auto results = searchEngine.searchByAuthor(books, query);
        if (results.empty()) cout << "Ничего не найдено." << endl;
        for (const auto& b : results) b.display();
    }
    else {
        cout << "Неверный выбор." << endl;
    }
}