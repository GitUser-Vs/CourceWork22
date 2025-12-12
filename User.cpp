#include "User.hpp"

// constructors and destructor
User::User() : m_userId(0), m_name("Unknown User"), m_email(""), m_maxBorrowedCount(0)
{
}

User::User(int userId, const std::string& name, const std::string& email, int maxBorrowedCount)
    : m_userId(userId), m_name(name), m_email(email), m_maxBorrowedCount(maxBorrowedCount)
{
}

// --- Конструктор копирования ---
User::User(const User& other)
    : m_userId(other.m_userId),
    m_name(other.m_name),
    m_email(other.m_email),
    m_borrowedBookIds(other.m_borrowedBookIds),
    m_maxBorrowedCount(other.m_maxBorrowedCount)
{
}

// --- Operator overload ---

// Overloading the assignment operator by copying
User& User::operator=(const User& other)
{
    if (this != &other)
    {
        m_userId = other.m_userId;
        m_name = other.m_name;
        m_email = other.m_email;
        m_borrowedBookIds = other.m_borrowedBookIds;
        m_maxBorrowedCount = other.m_maxBorrowedCount;
    }
    return *this;
}

// public methods
void User::displayInfo() const
{
    std::cout << "User ID: " << m_userId
        << ", Name: " << m_name
        << ", Email: " << m_email
        << ", Borrowed: " << m_borrowedBookIds.size() << "/" << m_maxBorrowedCount << std::endl;
}

bool User::borrowBook(int bookId)
{
    // Проверяем, не превышен ли лимит и не взят ли уже этот ID книги
    if (m_borrowedBookIds.size() < m_maxBorrowedCount) {
        // Проверяем, есть ли уже такая книга в списке взятых
        bool alreadyBorrowed = false;
        for (int id : m_borrowedBookIds) {
            if (id == bookId) {
                alreadyBorrowed = true;
                break;
            }
        }
        if (!alreadyBorrowed) {
            m_borrowedBookIds.push_back(bookId);
            return true;
        }
        else {
            std::cout << "User " << m_userId << " already has book ID " << bookId << "." << std::endl;
            return false;
        }
    }
    std::cout << "User " << m_userId << " has reached maximum borrowed books." << std::endl;
    return false; // Невозможно взять больше книг
}

bool User::returnBook(int bookId)
{
    auto it = std::find(m_borrowedBookIds.begin(), m_borrowedBookIds.end(), bookId);
    if (it != m_borrowedBookIds.end()) {
        m_borrowedBookIds.erase(it); // Удаляем книгу из списка
        return true;
    }
    std::cout << "User " << m_userId << " does not have book ID " << bookId << " borrowed." << std::endl;
    return false; // Нечего возвращать
}

//getters
int User::getUserID() const { return m_userId; }
const std::string& User::getName() const { return m_name; }
const std::string& User::getEmail() const { return m_email; }
size_t User::getBorrowedCount() const { return m_borrowedBookIds.size(); }
int User::getMaxBorrowedCount() const { return m_maxBorrowedCount; }

// --- Перегрузка оператора ---
bool User::operator==(const User& other) const
{
    return m_userId == other.m_userId;
}

// --- Перегрузка оператора ---
std::ostream& operator<<(std::ostream& os, const User& user)
{
    os << "User(ID: " << user.m_userId
        << ", Name: \"" << user.m_name << "\""
        << ", Email: " << user.m_email
        << ", Borrowed: " << user.m_borrowedBookIds.size() << "/" << user.m_maxBorrowedCount << ")";
    return os;
}