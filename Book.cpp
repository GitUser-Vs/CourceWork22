#include "Book.hpp"

// --- Дружественная функция ---
void displayBookDetails(const Book& book)
{
    std::cout << "[Details] Book ID: " << book.m_bookId
        << ", Title: \"" << book.m_title << "\""
        << ", Author: " << book.m_author
        << ", Total: " << book.m_quantity
        << ", Available: " << book.m_available;
}

// --- Перегрузка оператора ---
std::ostream& operator<<(std::ostream& os, const Book& book)
{
    os << "Book(ID: " << book.m_bookId
        << ", Title: \"" << book.m_title << "\""
        << ", Author: " << book.m_author
        << ", Qty: " << book.m_quantity
        << ", Avail: " << book.m_available << ")";
    return os;
}

// constructors and destructor
Book::Book() : m_bookId(0), m_title("Unknown Title"), m_author("Unknown Author"), m_quantity(0), m_available(0)
{
}

Book::Book(int bookId, const std::string& title, const std::string& author, int quantity)
    : m_bookId(bookId), m_title(title), m_author(author), m_quantity(quantity), m_available(quantity)
{
}

// Copy constructor
Book::Book(const Book& other)
    : m_bookId(other.m_bookId),
    m_title(other.m_title),
    m_author(other.m_author),
    m_quantity(other.m_quantity),
    m_available(other.m_available)
{
}

// --- Оператор присваивания копированием ---
Book& Book::operator=(const Book& other)
{
    if (this != &other) // Защита от самоприсваивания
    {
        m_bookId = other.m_bookId;
        m_title = other.m_title;
        m_author = other.m_author;
        m_quantity = other.m_quantity;
        m_available = other.m_available;
    }
    return *this;
}

// public methods
void Book::displayInfo() const
{
    displayBookDetails(*this);
    std::cout << std::endl; // Добавляем перевод строки
}

void Book::decreaseAvailable()
{
    if (m_available > 0) {
        m_available--;
    }
}

void Book::increaseAvailable()
{
    if (m_available < m_quantity) {
        m_available++;
    }
}

// getters
int Book::getBookID() const { return m_bookId; }
std::string Book::getTitle() const { return m_title; }
std::string Book::getAuthor() const { return m_author; }
int Book::getQuantity() const { return m_quantity; }
int Book::getAvailable() const { return m_available; }