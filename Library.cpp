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

// --- Реализации ввода-вывода ---
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

// ... (Аналогично для users и transactions) ...
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

// --- Операции ---

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
    books.back().setFilePath(path); // Устанавливаем путь
    cout << "Книга добавлена с ID: " << books.back().getId() << endl;
}


// Новый метод для пользователя
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
            // Используем вспомогательный класс для открытия файла
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

//LibraryItem* Library::findBookById(int itemId) {
//    auto it = std::find_if(m_items.begin(), m_items.end(),
//        [itemId](const std::unique_ptr<LibraryItem>& item) {
//            return item->getItemId() == itemId;
//        });
//
//    if (it != m_items.end()) {
//        return it->get();
//    }
//    return nullptr; // Книга не найдена
//}

//// Сортировка с использованием std::sort
//void Library::sortItemsByTitle() {
//    std::sort(m_items.begin(), m_items.end(),
//        [](const std::unique_ptr<LibraryItem>& a, const std::unique_ptr<LibraryItem>& b) {
//            // Сортируем по заголовку
//            return a->getTitle() < b->getTitle();
//        });
//}
//
//void Library::displayAllItems() const {
//    std::cout << "\n--- Library Contents ---\n";
//    for (const auto& itemPtr : m_items) {
//        // Вызов полиморфного метода displayInfo()
//        itemPtr->displayInfo();
//        std::cout << " | Qty: " << itemPtr->getQuantity() << "\n";
//    }
//}


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

//User* Library::findUserById(int UserID)
//{
//    // Проходим по вектору m_users
//    for (auto& user : m_users) {
//        if (user.getUserID() == UserID) {
//            return &user; // Возвращаем адрес найденного объекта User
//        }
//    }
//    return nullptr; // Пользователь не найден
//}
//
//// --- Методы для работы с транзакциями ---
//void Library::addTransaction(const Transaction& transaction)
//{
//    m_transactions.push_back(transaction); // Копирование объекта
//    std::cout << "Added transaction to library system." << std::endl;
//}

void Library::displayAllTransactions() const
{
    cout << "\n--- ИСТОРИЯ ТРАНЗАКЦИЙ ---" << endl;
    if (transactions.empty()) { cout << "Транзакций нет." << endl; return; }
    for (const auto& t : transactions) { t.display(); }
}

//Transaction* Library::findTransactionById(int transactionId)
//{
//    for (auto& t : m_transactions) {
//        if (t.getTransactionId() == transactionId) {
//            return &t;
//        }
//    }
//    return nullptr; // Транзакция не найдена
//}
//
//// Поиск последней активной транзакции для данной книги и пользователя
//Transaction* Library::findTransactionByBookUser(int bookId, int userId)
//{
//    Transaction* lastActiveTransaction = nullptr;
//    for (auto& t : m_transactions) {
//        if (t.getBookId() == bookId &&
//            t.getUserId() == userId &&
//            !t.isReturned())
//        {
//            // Сохраняем указатель невозвращенной транзакции
//            lastActiveTransaction = &t;
//        }
//    }
//    return lastActiveTransaction;
//}
//
//// --- Methods using aggregated objects ---
//void Library::processLending(int BookID, int UserID)
//{
//    std::cout << "\nProcessing lending for Book ID " << BookID << " to User ID " << UserID << "..." << std::endl;
//    LibraryItem* itemPtr = findBookById(BookID);
//    Book* book = dynamic_cast<Book*>(itemPtr);
//    //Book* book = findBookById(BookID);
//    User* user = findUserById(UserID);
//
//    // Проверка на отсутствие книги или пользователя
//    if (!book) {
//        std::cout << "Lending failed. Book with ID " << BookID << " not found." << std::endl;
//        return;
//    }
//    if (!user) {
//        std::cout << "Lending failed. User with ID " << UserID << " not found." << std::endl;
//        return;
//    }
//
//    // Проверяем, есть ли у пользователя место для взятия новой книги
//    if (user->borrowBook(BookID)) {
//        book->decreaseAvailable();
//        std::cout << "Lending successful. Book '" << book->getTitle() << "' lent to '" << user->getName() << "'." << std::endl;
//
//        // Создаем новую транзакцию
//        std::tm issueDate = getCurrentTm();
//        std::tm dueDate = addDaysToTm(issueDate, 14);
//
//        // Создаем транзакцию с уникальным ID
//        Transaction newTransaction(static_cast<int>(m_transactions.size()) + 1, BookID, UserID, issueDate, dueDate);
//        addTransaction(newTransaction);
//    }
//}
//
//void Library::processReturn(int BookID, int UserID)
//{
//    std::cout << "\nProcessing return for Book ID " << BookID << " by User ID " << UserID << "..." << std::endl;
//    LibraryItem* itemPtr = findBookById(BookID);
//    Book* book = dynamic_cast<Book*>(itemPtr);
//    //Book* book = findBookById(BookID);
//    User* user = findUserById(UserID);
//
//    if (!book) {
//        std::cout << "Return failed. Book with ID " << BookID << " not found." << std::endl;
//        return;
//    }
//
//    if (!user) {
//        std::cout << "Return failed. User with ID " << UserID << " not found." << std::endl;
//        return;
//    }
//
//    Transaction* activeTransaction = findTransactionByBookUser(BookID, UserID);
//    if (!activeTransaction) {
//        std::cout << "Return failed. No active lending transaction found for Book ID " << BookID << " and User ID " << UserID << "." << std::endl;
//        return;
//    }
//
//    std::tm returnDate = getCurrentTm();
//    double fine = 0.0;
//
//    std::time_t returnTime = std::mktime(const_cast<std::tm*>(&returnDate));
//    std::time_t dueTime = std::mktime(const_cast<std::tm*>(&activeTransaction->getDueDate()));
//
//    if (returnTime > dueTime) {
//        int daysOverdue = static_cast<int>((returnTime - dueTime) / (60 * 60 * 24));
//        fine = m_fineCalculator->calculateFine(daysOverdue);
//    }
//
//    activeTransaction->markAsReturned(returnDate, fine);
//
//    if (user->returnBook(BookID)) {
//        book->increaseAvailable();
//        std::cout << "Return successful. Book '" << book->getTitle() << "' returned by '" << user->getName() << "'." << std::endl;
//        if (fine > 0) {
//            std::cout << "  Fine incurred: $" << fine << std::endl;
//        }
//    }
//    else {
//        std::cout << "Return warning: User '" << user->getName() << "' count mismatch after return." << std::endl;
//    }
//}
//
//void Library::performSearch(const std::string& query)
//{
//    std::cout << "\nPerforming search in Library..." << std::endl;
//    m_searchEngine->searchBooks(query);
//    m_searchEngine->searchUsers(query); 
//}

// --- Аутентификация ---
bool Library::registerUser() {
    string username, password;
    cout << "--- РЕГИСТРАЦИЯ (Роль по умолчанию: USER) ---" << endl;
    cout << "Введите желаемый логин: "; getline(cin, username);

    if (findAccount(username)) {
        cout << "Ошибка: Логин уже занят." << endl;
        return false;
    }

    cout << "Введите пароль: "; getline(cin, password);

    // Сначала регистрируем нового пользователя в списке пользователей
    users.emplace_back(nextUserId++, username, "N/A"); // Контакт изначально "N/A"
    int newUserId = users.back().getId();

    // Регистрируем аккаунт с ролью USER, связанный с новым ID
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
        currentUserId = acc->getAssociatedId(); // User ID, если роль USER
        cout << "Вход успешен. Роль: " << (currentRole == Role::ADMIN ? "АДМИНИСТРАТОР" : "ПОЛЬЗОВАТЕЛЬ") << endl;
        return true;
    }
    else {
        cout << "Ошибка: Логин или пароль неверны." << endl;
        return false;
    }
}


// --- Специализированные ---
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