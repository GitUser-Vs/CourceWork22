#include "Book.hpp"

// constructors and destructor
Book::Book()
    : LibraryItem(0, "Unknown Title", 0), m_author("Unknown Author"), m_available(0)
{
}

Book::Book(int bookId, const std::string& title, const std::string& author, int quantity)
    : LibraryItem(bookId, title, quantity), // Вызов конструктора базового класса
    m_author(author),
    m_available(quantity)
{
}

// Конструктор копирования
Book::Book(const Book& other)
    : LibraryItem(other.m_itemId, other.m_title, other.m_totalQuantity), // Копируем базовый класс
    m_author(other.m_author),
    m_available(other.m_available)
{
}

// Перегрузка присваивания
Book& Book::operator=(const Book& other)
{
    if (this != &other)
    {
        m_itemId = other.m_itemId;
        m_title = other.m_title;
        m_totalQuantity = other.m_totalQuantity;

        // Присваивание членов производного класса
        m_author = other.m_author;
        m_available = other.m_available;
    }
    return *this;
}

// public methods
// Перегрузка виртуального метода с вызовом базового
void Book::displayInfo() const {
    // Вызов метода базового класса (чтобы показать информацию LibraryItem)
    LibraryItem::displayInfo();
    std::cout << ", Author: " << m_author << ", Available: " << m_available << std::endl;
}

// Перегрузка метода без вызова базового
void Book::displayExtendedInfo() const {
    std::cout << "--- EXTENDED BOOK INFO ---" << std::endl;
    std::cout << "Title: " << m_title << ", Author: " << m_author << std::endl;
    std::cout << "Total Quantity: " << m_totalQuantity << std::endl;
}

// Глубокое клонирование
LibraryItem* Book::clone() const {
    // Создает новую копию, используя конструктор копирования
    return new Book(*this);
}

// Демонстрация доступа к protected
void Book::checkProtectedAccess() const {
    // Доступ к m_totalQuantity
    std::cout << "[Book] Accessing protected quantity: " << m_totalQuantity << std::endl;
}

// Реализация перегруженного оператора << для Book
std::ostream& operator<<(std::ostream& os, const Book& book)
{
    // Используем информацию, которую Book может получить
    os << "Book(ID: " << book.getItemId() // Используем getItemId из LibraryItem
        << ", Title: \"" << book.getTitle() << "\""
        << ", Author: " << book.getAuthor()
        << ", Quantity: " << book.getQuantity()
        << ", Available: " << book.getAvailable() << ")";
    return os;
}

void Book::decreaseAvailable() { if (m_available > 0) m_available--; }
void Book::increaseAvailable() { if (m_available < m_totalQuantity) m_available++; }

// getters
std::string Book::getAuthor() const { return m_author; }
int Book::getAvailable() const { return m_available; }
int Book::getQuantity() const { return m_totalQuantity; }