#include "Book.hpp"

// constructors and destructor
Book::Book() : m_BookID(0), m_title("Unknown Title"), m_author("Unknown Author"), m_quantity(0), m_available(0)
{

}

Book::Book(int BookID, const std::string& title, const std::string& author, int quantity)
    : m_BookID(BookID), m_title(title), m_author(author), m_quantity(quantity), m_available(quantity)
{

}

// Конструктор копирования
Book::Book(const Book& other)
    : m_BookID(other.m_BookID),
    m_title(other.m_title),
    m_author(other.m_author),
    m_quantity(other.m_quantity),
    m_available(other.m_available)
{

}

// --- Перегрузка операторов ---

// Перегрузка оператора присваивания копированием
Book& Book::operator<<=(const Book& other)
{
    if (this != &other) // Проверка на самоприсваивание
    {
        m_BookID = other.m_BookID;
        m_title = other.m_title;
        m_author = other.m_author;
        m_quantity = other.m_quantity;
        m_available = other.m_available;
        
    }
    return *this; // Возвращаем ссылку на текущий объект
}

// Перегрузка оператора
bool Book::operator==(const Book& other) const
{
    // Сравниваем по ID, как самый уникальный идентификатор
    return m_BookID == other.m_BookID;
}

// Дружественная функция для перегрузки оператора
std::ostream& operator<<(std::ostream& os, const Book& book)
{
    os << "Book ID: " << book.m_BookID
        << ", Title: \"" << book.m_title << "\""
        << ", Author: " << book.m_author
        << ", Quantity: " << book.m_quantity
        << ", Available: " << book.m_available;
    return os;
}


// public methods
void Book::displayInfo() const
{
    // используем перегруженный оператор <<
    std::cout << *this << std::endl;
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
int Book::getBookID() const { return m_BookID; }
std::string Book::getTitle() const { return m_title; }
std::string Book::getAuthor() const { return m_author; }
int Book::getQuantity() const { return m_quantity; }
int Book::getAvailable() const { return m_available; }